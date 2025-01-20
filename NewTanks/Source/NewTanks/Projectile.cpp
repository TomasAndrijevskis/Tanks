// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerTank.h"
#include "Particles/ParticleSystemComponent.h"
#include "Enemy.h"

// Sets default values
AProjectile::AProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpuls, const FHitResult& HitResult)
{
	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		return;
	}
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if(APlayerTank* PlayerPawn = Cast<APlayerTank>(MyOwner))
	{
		if(PlayerPawn->bIsDamageIncreased())
		{
			Damage = Damage + (Damage * PlayerPawn->GetDamageIncreasePercentage());
		}
	}
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(ExplosionEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), GetActorRotation());
		}
		Destroy();
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetDamage(float DamageValue)
{
	Damage = DamageValue;
}

void AProjectile::SetProjectileSpeed(float Speed)
{
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->InitialSpeed = Speed;
}
