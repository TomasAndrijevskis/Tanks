// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class NEWTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:

	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetMovementSpeed();
	void SetMovementSpeed(float Speed);

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	class UParticleSystem* DeathEffect;
	
protected:

	virtual void BeginPlay() override;
	void MoveTank(float Value);
	void RotateTank(float Value);
	void RotateTank(FVector LocationToLook);
	void RotateTurret(FVector LocationToLook);
	void PrimaryAttack();
	void SecondaryAttack();

private:

	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* MeshCapsuleCollision;
	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class AProjectile> PrimaryAttackProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	TSubclassOf<class AProjectile> SecondaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 150;

};
