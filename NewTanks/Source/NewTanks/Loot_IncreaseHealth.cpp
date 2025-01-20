// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot_IncreaseHealth.h"
#include "PlayerTank.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"

ALoot_IncreaseHealth::ALoot_IncreaseHealth()
{
    LootSecondMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second Mesh"));
	LootSecondMesh->SetupAttachment(LootMesh);
}

void ALoot_IncreaseHealth::BeginPlay()
{
    Super::BeginPlay();

	LootCollision->OnComponentBeginOverlap.AddDynamic(this, &ALoot_IncreaseHealth::BeginOverlap);
}

void ALoot_IncreaseHealth::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(APlayerTank* PlayerPawn = Cast<APlayerTank>(OtherActor))
	{
        UHealthComponent* HealthComponent = PlayerPawn->FindComponentByClass<UHealthComponent>();
        if(HealthComponent != nullptr)
        {
            HealthComponent->AddHealth(HealthToAdd);
            UE_LOG(LogTemp, Warning, TEXT("Health added"));
        }
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Not"));
	}
}
