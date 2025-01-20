// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = MeshCapsuleCollision;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(MeshCapsuleCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasePawn::GetMovementSpeed()
{
	return MovementSpeed;
}

void ABasePawn::SetMovementSpeed(float Speed)
{
	MovementSpeed = Speed;
}

void ABasePawn::MoveTank(float Value)
{
	FVector Location = FVector::ZeroVector;
	Location.X = Value * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(Location, true);
}

void ABasePawn::RotateTank(float Value)
{
	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Yaw = Value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(Rotation, true);
}

void ABasePawn::RotateTank(FVector LocationToLook)
{
	FVector TargetLocation = LocationToLook - BaseMesh->GetComponentLocation();
	FRotator TurretRotation = FRotator(0, TargetLocation.Rotation().Yaw, 0);

	BaseMesh->SetWorldRotation
	(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TurretRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 7.f));
}

void ABasePawn::RotateTurret(FVector LocationToLook)
{
	FVector TargetLocation = LocationToLook - TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FRotator(0, TargetLocation.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation
	(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TurretRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 7.f));
	
}

void ABasePawn::PrimaryAttack()
{
	FVector ProjectileLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(PrimaryAttackProjectileClass, ProjectileLocation, ProjectileRotation);
	
	if(Projectile == nullptr)
	{
		return;
	}
	else
	{
		Projectile->SetOwner(this);
	}
}

void ABasePawn::SecondaryAttack()
{
	FVector ProjectileLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(SecondaryAttackProjectileClass, ProjectileLocation, ProjectileRotation);
	
	if(Projectile == nullptr)
	{
		return;
	}
	else
	{
		Projectile->SetOwner(this);
	}
}

