// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Loot_Template.generated.h"

UCLASS()
class NEWTANKS_API ALoot_Template : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot_Template();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* LootCollision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LootMesh;
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	float RotationSpeed = 75;

};
