// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TanksGameMode.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerTankController.h"
#include "Kismet/GameplayStatics.h"

APlayerTank::APlayerTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    SetMovementSpeed(Speed);
}

void APlayerTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult HitResult;

    if(PlayerTankController)
    {
        PlayerTankController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}

void APlayerTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Move"), this, &APlayerTank::MoveTank);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerTank::RotateTank);
    PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &APlayerTank::PrimaryAttack);
    PlayerInputComponent->BindAction(TEXT("SecondaryAttack"), IE_Pressed, this, &APlayerTank::SecondaryAttack);
}

void APlayerTank::BeginPlay()
{
    Super::BeginPlay();

    PlayerTankController = Cast<APlayerController>(GetController());
}

void APlayerTank::PrimaryAttack()
{
    if(BulletsAmount>0)
    {
        Super::PrimaryAttack();
        BulletsAmount--;
        UE_LOG(LogTemp, Error, TEXT("Bullets: %i"), BulletsAmount);
    }    
}

void APlayerTank::SecondaryAttack()
{
    if(!bIsReloading)
    {
        if(BombsAmount>0)
        {
            GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &APlayerTank::ReloadTimer, 1.0f, true, 0);
            Super::SecondaryAttack();
            BombsAmount--;
            UE_LOG(LogTemp, Error, TEXT("BombsAmount: %i"), BombsAmount);
        }
    }
}

void APlayerTank::ReloadTimer()
{
    bIsReloading = true;
    if(ReloadDuration == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Reload: %f"), ReloadDuration);
        bIsReloading = false;
        ReloadDuration = 2;
        GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
    }
    ReloadDuration--;
}

void APlayerTank::IncreaseBullets(int BulletsToAdd, int BombsToAdd)
{
    BulletsAmount += BulletsToAdd;
    BombsAmount += BombsToAdd;
}

void APlayerTank::IncreaseDamage(bool bValue, float Percentage, float Duration)
{
    DamageIncreasePercentage = Percentage;
    bIncreaseDamage = bValue;
    DamageBoostDuration = Duration;
    GetWorldTimerManager().SetTimer(DamageBoosterTimerHandle, this, &APlayerTank::DamageBoostTimer, 1.0f, true, 0);
}

void APlayerTank::DamageBoostTimer() 
{
    if(DamageBoostDuration == 0)
    {
        bIncreaseDamage = false;
        GetWorldTimerManager().ClearTimer(DamageBoosterTimerHandle);
    }
    DamageBoostDuration--;
}

void APlayerTank::ArmorBoostTimer() 
{
    if(ArmorBoostDuration == 0)
    {
        bIncreaseArmor = false;
        GetWorldTimerManager().ClearTimer(ArmorBoosterTimerHandle);
    }
    ArmorBoostDuration--;
}

void APlayerTank::SetArmor(bool bValue, float Percentage, float Duration)
{
    ArmorPercentage = Percentage;
    bIncreaseArmor = bValue;
    ArmorBoostDuration = Duration;
    GetWorldTimerManager().SetTimer(ArmorBoosterTimerHandle, this, &APlayerTank::ArmorBoostTimer, 1.0f, true, 0);
}



void APlayerTank::HandleDeath()
{
    if(DeathEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());
	}
    ATanksGameMode* GameMode = Cast<ATanksGameMode>(GetWorld()->GetAuthGameMode());
    APlayerTankController* PlayerController = Cast<APlayerTankController>(UGameplayStatics::GetPlayerController(this, 0));
    PlayerController->SetPlayerEnabledState(false);
    GameMode->SetIsPlayerAliveStatus(false);
    Destroy();
}

bool APlayerTank::bIsBombReloading()
{
    return bIsReloading;
}

bool APlayerTank::bIsDamageIncreased()
{
    return bIncreaseDamage;
}

int APlayerTank::GetBulletAmount()
{
    return BulletsAmount;
}

int APlayerTank::GetBombsAmount()
{
    return BombsAmount;
}

float APlayerTank::GetDamageIncreasePercentage()
{
    return DamageIncreasePercentage;
}

bool APlayerTank::bGetIsArmorSet()
{
    return bIncreaseArmor;
}

float APlayerTank::GetArmorPercentage()
{
    return ArmorPercentage;
}
