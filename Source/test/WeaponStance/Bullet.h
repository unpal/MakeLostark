// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TEST_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(visibleDefaultsOnly)
		class UCapsuleComponent* Capsule;
	UPROPERTY(visibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(visibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpuluse,
			const FHitResult& Hit);
public:
	void Shoot(const FVector& InDirection);
	void DestroyBullet();
	FTimerHandle BulletDostroyTimerHandle;
};
