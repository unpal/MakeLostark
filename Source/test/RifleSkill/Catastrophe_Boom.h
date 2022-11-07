
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Catastrophe_Boom.generated.h"

UCLASS()
class TEST_API ACatastrophe_Boom : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatastrophe_Boom();

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(visibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(visibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(visibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
public:
	void Shoot(const FVector& InDirection);
	void Destroy_Boom();
};
