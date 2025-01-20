// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void APlayerTankController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void APlayerTankController::SetPlayerEnabledState(bool bIsPlayerEnabled)
{
    bPlayerEnabled = bIsPlayerEnabled;
    if(bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}

bool APlayerTankController::IsPlayerEnabled()
{
    return bPlayerEnabled;
}

