// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loot_Template.h"
#include "Loot_IncreaseBullets.generated.h"

/**
 * 
 */
UCLASS()
class NEWTANKS_API ALoot_IncreaseBullets : public ALoot_Template
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	int BulletsToAdd = 20;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	int BombsToAdd = 4;
};