// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerTank.generated.h"

/**
 * 
 */
UCLASS()
class NEWTANKS_API APlayerTank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	APlayerTank();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION() 
	void IncreaseBullets(int BulletsToAdd, int BombsToAdd);
	UFUNCTION(BlueprintCallable) 
	bool bIsDamageIncreased();
	UFUNCTION(BlueprintCallable) 
	int GetBulletAmount();
	UFUNCTION(BlueprintCallable) 
	int GetBombsAmount();
	UFUNCTION(BlueprintCallable) 
	bool bIsBombReloading();
	UFUNCTION(BlueprintCallable) 
	bool bGetIsArmorSet();

	UFUNCTION() 
	float GetDamageIncreasePercentage();
	UFUNCTION() 
	void IncreaseDamage(bool bValue, float Percentage, float BoostDurationValue);
	UFUNCTION() 
	void SetArmor(bool bValue, float Percentage, float BoostDurationValue);
	UFUNCTION() 
	void HandleDeath();
	UFUNCTION() 
	float GetArmorPercentage();

protected:

	virtual void BeginPlay() override;
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();

private:

	UPROPERTY(VisibleAnywhere) 
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere) 
	class USpringArmComponent* SpringArm;

	APlayerController* PlayerTankController;

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables") 
	int BulletsAmount = 20;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables") 
	int BombsAmount = 8;


	FTimerHandle DamageBoosterTimerHandle;
	FTimerHandle ArmorBoosterTimerHandle;
	FTimerHandle ReloadTimerHandle;

	bool bIncreaseDamage;
	float DamageIncreasePercentage;
	float DamageBoostDuration;

	bool bIncreaseArmor;
	float ArmorPercentage;
	float ArmorBoostDuration;

	float ReloadDuration = 1;
	bool bIsReloading;
	float Speed = 750;

	UFUNCTION() 
	void DamageBoostTimer();
	UFUNCTION() 
	void ArmorBoostTimer();
	UFUNCTION() 
	void ReloadTimer();
};

