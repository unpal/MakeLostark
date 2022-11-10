#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIWeapon_Arrow.generated.h"

UCLASS()
class TEST_API AAIWeapon_Arrow : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
	
public:	
	AAIWeapon_Arrow();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	void Shoot(const FVector& InDirection);
};
