// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Enemy.h"
#include "PlayerTankController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "NavMesh/NavMeshBoundsVolume.h"

ATanksGameMode::ATanksGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    PlayerController = Cast<APlayerTankController>(UGameplayStatics::GetPlayerController(this, 0));
    if(PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerTankController::SetPlayerEnabledState, true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);

        //UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    }

}

void ATanksGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TargetEnemies = GetNumberOfEnemies();
    if(TargetEnemies <= 0)
    {
        EndGame(true);
    }
    if(!GetIsPlayerAliveStatus())
    {
        EndGame(false);
    }
}

int ATanksGameMode::GetNumberOfEnemies()
{
    UGameplayStatics::GetAllActorsOfClass(this, AEnemy::StaticClass(), EnemyArray);

    return EnemyArray.Num();
}

void ATanksGameMode::RemoveEnemyFromArray(AActor* EnemyToRemove)
{
    if(EnemyArray.Contains(EnemyToRemove))
    {
        EnemyArray.Remove(EnemyToRemove);
    }
    TargetEnemies--;
}

void ATanksGameMode::EndGame(bool bIsWinner)
{
    UWidgetLayoutLibrary::RemoveAllWidgets(this);
    if(bIsWinner)
    {
        PlayerController->SetPlayerEnabledState(false);
        UUserWidget* WinScreen = CreateWidget(PlayerController, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(PlayerController, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
}



void ATanksGameMode::SetIsPlayerAliveStatus(bool bStatus)
{
    bIsPlayerAlive = bStatus;
}

bool ATanksGameMode::GetIsPlayerAliveStatus()
{
    return bIsPlayerAlive;
}
