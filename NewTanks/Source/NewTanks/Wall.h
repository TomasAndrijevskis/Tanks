#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Wall.generated.h"

UCLASS()
class NEWTANKS_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AWall();

	virtual void Tick(float DeltaTime) override;

	void ChangeWallMesh(float Health, float MaxHealth);
	void HandleDistraction();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxMeshCollision;

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	UMaterial* Material_UnbreakableWall;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	UMaterial* Material_FirstPhase;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	UMaterial* Material_SecondPhase;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	UMaterial* Material_ThirdPhase;
	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	UMaterial* Material_FourthPhase;

	UPROPERTY(EditDefaultsOnly, Category = "CustomVariables")
	bool bBreakableWall;

	void SetWallMaterial(UMaterial* Material);
	

};
