// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Wall.h"
#include "PlayerTank.h"
#include "Enemy.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0)
	{
		return;
	}

	if(APlayerTank* PlayerTank = Cast<APlayerTank>(DamagedActor))
	{
		if(PlayerTank->bGetIsArmorSet())
		{
			Health -= (Damage - (Damage * PlayerTank->GetArmorPercentage()));
		}
		else
		{
			Health -= Damage;
		}
	}
	else
	{
		Health -= Damage;
	}

	if(AWall* Wall = Cast<AWall>(DamagedActor))
	{
		Wall->ChangeWallMesh(Health, MaxHealth);
	}
	if(Health <= 0)
	{
		if(APlayerTank* PlayerTank = Cast<APlayerTank>(DamagedActor))
		{
			PlayerTank->HandleDeath();
		}
		if(AEnemy* Enemy = Cast<AEnemy>(DamagedActor))
		{
			Enemy->HandleDeath();
		}
		if(AWall* Wall = Cast<AWall>(DamagedActor))
		{
			Wall->HandleDistraction();
		}
	}
}

void UHealthComponent::AddHealth(float HealthToAdd) 
{
	Health += (MaxHealth * HealthToAdd);
	if(Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UHealthComponent::GetHealthAsRatio()
{
	return Health / MaxHealth;
}


