

#include "Wall.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxMeshCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxMeshCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxMeshCollision);


	Material_UnbreakableWall = NewObject<UMaterial>();
	Material_FirstPhase = NewObject<UMaterial>();
	Material_SecondPhase = NewObject<UMaterial>();
	Material_ThirdPhase = NewObject<UMaterial>();
	Material_FourthPhase = NewObject<UMaterial>();
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	if(bBreakableWall)
	{
		SetWallMaterial(Material_FirstPhase);
	}
	else
	{
		SetWallMaterial(Material_UnbreakableWall);
	}
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWall::ChangeWallMesh(float Health, float MaxHealth)
{
	if(bBreakableWall)
	{
		if(Health > (MaxHealth * 0.75))
		{
			SetWallMaterial(Material_FirstPhase);
		}
		if((Health > (MaxHealth * 0.5)) && (Health <= (MaxHealth * 0.75)))
		{
			SetWallMaterial(Material_SecondPhase);
		}
		if((Health > (MaxHealth * 0.25)) && (Health <= (MaxHealth * 0.5)))
		{
			SetWallMaterial(Material_ThirdPhase);
		}
		if(Health > 0 && (Health <= (MaxHealth * 0.25)))
		{
			SetWallMaterial(Material_FourthPhase);
		}
	}
}

void AWall::HandleDistraction()
{
	
	Destroy();
}
void AWall::SetWallMaterial(UMaterial* Material)
{
	if (Material && Mesh)
    {
        Mesh->SetMaterial(0, Material);
    }
}

