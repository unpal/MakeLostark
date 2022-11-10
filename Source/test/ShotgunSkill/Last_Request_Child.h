// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Last_Request.h"
#include "Last_Request_Child.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ALast_Request_Child : public ALast_Request
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;
	UPROPERTY(visibleDefaultsOnly)
		class USphereComponent* Sphere;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpuluse,
			const FHitResult& Hit);

public:
	ALast_Request_Child();

protected:
	virtual void BeginPlay() override;
};
