// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot_Armor.h"
#include "Components/SphereComponent.h"
#include "PlayerTank.h"


void ALoot_Armor::BeginPlay()
{
    Super::BeginPlay();

	LootCollision->OnComponentBeginOverlap.AddDynamic(this, &ALoot_Armor::BeginOverlap);
}

void ALoot_Armor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(APlayerTank* PlayerPawn = Cast<APlayerTank>(OtherActor))
	{
		PlayerPawn->SetArmor(true, BoostPercentage, BoostDurationValue);
		Destroy();
	}
}
