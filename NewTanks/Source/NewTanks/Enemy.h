// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Loot_Armor.h"
#include "Loot_DamageBooster.h"
#include "Loot_IncreaseBullets.h"
#include "Loot_IncreaseHealth.h"
#include "Enemy.generated.h"

UCLASS()
class NEWTANKS_API AEnemy : public ABasePawn
{
	GENERATED_BODY()
	
public:

	AEnemy();
	virtual void Tick(float DeltaTime) override;
	void SpawnRandomLootAfterDeath();
	void HandleDeath();

protected:

	virtual void BeginPlay() override;
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();

private:

	UPROPERTY(EditDefaultsOnly)
	class UFloatingPawnMovement* FloatingPawnMovementComponent;
	class AEnemyAIController* EnemyAI;

	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	bool bIsPrimaryAttack = false;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float FireRange = 600;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float StopChasingPlayerRange = 300;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float VisibilityRange = 2000;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float Speed = 250;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float FireRate = 1.f;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float TimeToWait = 1.f;
	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	bool bIsTurret;

	FVector StartLocation;
	class APlayerTank* PlayerTank;
	FTimerHandle FireRateTimerHandle;
	FTimerHandle MoveBackTimerHandle;

	FHitResult HitResult;
    FVector EnemyLocation;
    FVector PlayerLocation;
	FVector LastKnownPlayerLocation;
	bool bChasingPlayer = false;


	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class ALoot_DamageBooster> DamageBooster;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class ALoot_IncreaseBullets> BulletsSpawner;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class ALoot_IncreaseHealth> HealthIncreaser;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class ALoot_Armor> Armor;

	void CheckFireCondition();
	bool bIsInFireRange();
	bool bIsInRange();
	int GetRandomNumber();
	void GoToStartLocation();
	void Move(FVector LocationToMove, float Range);
};

