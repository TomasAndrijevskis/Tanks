// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerTankController.h"
#include "PlayerTank.h"
#include "TanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEWTANKS_API ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ATanksGameMode();
	UFUNCTION(BlueprintCallable)
	int GetNumberOfEnemies();

	UFUNCTION()
	void RemoveEnemyFromArray(AActor* EnemyToRemove);

	UFUNCTION()
	void SetIsPlayerAliveStatus(bool bStatus);
	UFUNCTION(BlueprintCallable)
	bool GetIsPlayerAliveStatus();

	UFUNCTION()
	void EndGame(bool bIsWinner);


protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	TArray<AActor*> EnemyArray;

	APlayerTank* PlayerTank;

	bool bIsPlayerAlive = true;

	APlayerTankController* PlayerController;

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class UUserWidget> WinScreenClass;

	float StartDelay = 1.f;

	UPROPERTY()
	TSubclassOf<class AEnemy> EnemyClass;

	int TargetEnemies = 0;
};
