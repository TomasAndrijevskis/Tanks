// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot_IncreaseBullets.h"
#include "PlayerTank.h"
#include "Components/SphereComponent.h"

void ALoot_IncreaseBullets::BeginPlay()
{
    Super::BeginPlay();

	LootCollision->OnComponentBeginOverlap.AddDynamic(this, &ALoot_IncreaseBullets::BeginOverlap);
}

void ALoot_IncreaseBullets::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(APlayerTank* PlayerPawn = Cast<APlayerTank>(OtherActor))
	{
		PlayerPawn->IncreaseBullets(BulletsToAdd, BombsToAdd);
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Not"));
	}
}
