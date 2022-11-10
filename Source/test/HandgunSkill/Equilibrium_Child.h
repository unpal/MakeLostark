// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equilibrium.h"
#include "Equilibrium_Child.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AEquilibrium_Child : public AEquilibrium
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
	AEquilibrium_Child();
protected:
	virtual void BeginPlay() override;
public:
	void DestroyParticle();
	FTimerHandle DestoryTimerHandle;
};
