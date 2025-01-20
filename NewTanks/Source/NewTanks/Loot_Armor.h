// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loot_Template.h"
#include "Loot_Armor.generated.h"

/**
 * 
 */
UCLASS()
class NEWTANKS_API ALoot_Armor : public ALoot_Template
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	float BoostPercentage = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	float BoostDurationValue = 10;
};
