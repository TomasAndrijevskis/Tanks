// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot_DamageBooster.h"
#include "PlayerTank.h"
#include "Components/SphereComponent.h"

void ALoot_DamageBooster::BeginPlay()
{
    Super::BeginPlay();

	LootCollision->OnComponentBeginOverlap.AddDynamic(this, &ALoot_DamageBooster::BeginOverlap);
}

void ALoot_DamageBooster::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //Super::BeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
    if(APlayerTank* PlayerPawn = Cast<APlayerTank>(OtherActor))
	{
		PlayerPawn->IncreaseDamage(true, BoostPercentage, BoostDurationValue);
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Not"));
	}
}

