// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot_Template.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ALoot_Template::ALoot_Template()
{
	PrimaryActorTick.bCanEverTick = true;

	LootCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = LootCollision;

	LootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	LootMesh->SetupAttachment(LootCollision);
}

// Called when the game starts or when spawned
void ALoot_Template::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ALoot_Template::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Yaw = 1 * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(Rotation, true);
}
