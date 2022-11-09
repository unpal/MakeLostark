
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AT02_Grenade_Boom.generated.h"

UCLASS()
class TEST_API AAT02_Grenade_Boom : public AActor
{
	GENERATED_BODY()
	
public:	
	AAT02_Grenade_Boom();

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(visibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(visibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(visibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;
	void Throw_Boom(FVector Start, FVector Target, float arcValue, FVector outVelocity);
	UPROPERTY(EditAnywhere)
		class AAT02_Grenade* AT02_Grenade;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AAT02_Grenade> AT02_Grenade_Class;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpuluse,
			const FHitResult& Hit);
};
