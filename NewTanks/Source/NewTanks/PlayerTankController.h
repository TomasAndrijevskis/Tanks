// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class NEWTANKS_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
public:

	void SetPlayerEnabledState(bool bIsPlayerEnabled);
	bool IsPlayerEnabled();

protected:

	virtual void BeginPlay() override;
	bool bPlayerEnabled;

private:

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;
};
