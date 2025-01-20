// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"
//#include "Loot_DamageBooster.h"
//#include "Loot_IncreaseBullets.h"
//#include "Loot_IncreaseHealth.h"
//#include "Loot_Armor.h"
#include "TanksGameMode.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Wall.h"

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

    

}

void AEnemy::Tick(float DeltaTime)
{
    //3 = moving
    //0 = idle
    Super::Tick(DeltaTime);

    //DrawDebugSphere(GetWorld(), GetActorLocation(), StopChasingPlayerRange, 100 ,FColor::Black, false, 0.1f);
    //DrawDebugSphere(GetWorld(), GetActorLocation(), FireRange, 100 ,FColor::Red, false, 0.1f);
    //DrawDebugSphere(GetWorld(), GetActorLocation(), VisibilityRange, 100 ,FColor::Green, false, 0.1f);
    
    //переменная не меняется в Tick, поэтому если игрок умирает, то в этой переменной ничего не меняется
    if(PlayerTank != nullptr)
    {
        if(EnemyAI)
        {
            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(this);

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if(PlayerController != nullptr)
            {
                APawn* PlayerPawn = PlayerController->GetPawn();
                if(PlayerPawn != nullptr)
                {
                    PlayerLocation = PlayerPawn->GetActorLocation();
                    EnemyLocation = GetActorLocation();
                    // работает в любом случае, ему не важно это игрок, стена или пуля, все равно срабатывает
                    GetWorld()->LineTraceSingleByChannel(HitResult, EnemyLocation, PlayerLocation, ECC_Visibility, CollisionParams, FCollisionResponseParams());
                    
                    //DrawDebugLine(GetWorld(), EnemyLocation, PlayerLocation, FColor::Red, false, 0.5f);
                    if(Cast<AWall>(HitResult.GetActor()))
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("Wall"));
                        if(bChasingPlayer)
                        {
                            if(EnemyAI->GetMoveStatus() == 3)
                            {
                                Move(LastKnownPlayerLocation, 0);
                                //RotateTank(LastKnownPlayerLocation);
                            }
                            else if(EnemyAI->GetMoveStatus() == 0)
                            {
                                bChasingPlayer = false;
                            }  
                        }
                        else
                        {
                            Move(StartLocation, 0);
                            if(!bIsTurret)RotateTank(StartLocation);
                            else RotateTurret(StartLocation);
                        }
                    }
                    else
                    {
                        if(bIsInRange())
                        {
                            bChasingPlayer = true;
                            LastKnownPlayerLocation = PlayerLocation;
                            Move(PlayerLocation, StopChasingPlayerRange);
                            if(!bIsTurret)RotateTank(PlayerLocation);
                            else RotateTurret(PlayerLocation);
                        }
                        else
                        {
                            bChasingPlayer = false;
                            Move(StartLocation, 0);
                            if(!bIsTurret)RotateTank(StartLocation);
                            else RotateTurret(StartLocation);
                        }
                    }
                }
            }
        }
    }
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    EnemyAI = Cast<AEnemyAIController>(GetController());
    if(EnemyAI)
	{
        GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemy::CheckFireCondition, FireRate, true);
	}
    SetMovementSpeed(Speed);
    FloatingPawnMovementComponent->MaxSpeed = GetMovementSpeed();
    FloatingPawnMovementComponent->Acceleration = GetMovementSpeed();
    FloatingPawnMovementComponent->Deceleration = GetMovementSpeed();
}

void AEnemy::PrimaryAttack()
{
    Super::PrimaryAttack();
}

void AEnemy::SecondaryAttack()
{
    Super::SecondaryAttack();
}

void AEnemy::CheckFireCondition()
{
    if(PlayerTank == nullptr)
    {
        return;
    }
    if(bIsInFireRange())
    {
        if(!Cast<AWall>(HitResult.GetActor()))
        {
            if(bIsPrimaryAttack)
            {
                PrimaryAttack();
            }
            else
            {
                SecondaryAttack();
            }
        }
    }
}

void AEnemy::Move(FVector LocationToMove, float Range)
{
    EnemyAI->MoveToLocation(LocationToMove, Range);
}

bool AEnemy::bIsInFireRange()
{
    if(PlayerTank)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if(PlayerController)
        {
            APawn* PlayerPawn = PlayerController->GetPawn();
            if(PlayerPawn)
            {
                if(FVector::Distance(EnemyLocation, PlayerLocation) <= FireRange)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool AEnemy::bIsInRange()
{
    if(PlayerTank)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if(PlayerController)
        {
            APawn* PlayerPawn = PlayerController->GetPawn();
            if(PlayerPawn)
            {
                if(FVector::Distance(EnemyLocation, PlayerLocation) <= VisibilityRange)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int AEnemy::GetRandomNumber()
{
    return FMath::RandRange(1, 5);
}

void AEnemy::SpawnRandomLootAfterDeath()
{
    int Number = GetRandomNumber();
    FVector ActorLocation = GetActorLocation();
    FRotator ActorRotation = GetActorRotation();

    switch (Number)
	{
		case 1:
            GetWorld()->SpawnActor<ALoot_DamageBooster>(DamageBooster, ActorLocation, ActorRotation);
			break;
		case 2:
            GetWorld()->SpawnActor<ALoot_IncreaseHealth>(HealthIncreaser, ActorLocation, ActorRotation);
			break;
        case 3:
            GetWorld()->SpawnActor<ALoot_IncreaseBullets>(BulletsSpawner, ActorLocation, ActorRotation);
			break;
		case 4:
            GetWorld()->SpawnActor<ALoot_IncreaseBullets>(BulletsSpawner, ActorLocation, ActorRotation);
			break;
        case 5:
            GetWorld()->SpawnActor<ALoot_Armor>(Armor, ActorLocation, ActorRotation);
			break;
		default: break; 
	}
}

void AEnemy::HandleDeath()
{
    if(DeathEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());
	}
    SpawnRandomLootAfterDeath();
    ATanksGameMode* GameMode = Cast<ATanksGameMode>(GetWorld()->GetAuthGameMode());
    if(GameMode)
    {
        GameMode->RemoveEnemyFromArray(this);
    }
    Destroy();
}


