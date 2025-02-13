// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wall.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetHealthAsRatio();
	
	UFUNCTION() 
	void AddHealth(float HealthToAdd);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
private:

	UPROPERTY(EditAnywhere, Category = "CustomVariables")
	float MaxHealth = 100;
	float Health = 0;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);
};

