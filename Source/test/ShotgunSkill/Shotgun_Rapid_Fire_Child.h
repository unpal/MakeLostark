// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shotgun_Rapid_Fire.h"
#include "Shotgun_Rapid_Fire_Child.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AShotgun_Rapid_Fire_Child : public AShotgun_Rapid_Fire
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;


public:
	AShotgun_Rapid_Fire_Child();

protected:
	virtual void BeginPlay() override;
};
