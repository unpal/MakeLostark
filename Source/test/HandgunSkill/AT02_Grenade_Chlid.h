// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AT02_Grenade.h"
#include "AT02_Grenade_Chlid.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AAT02_Grenade_Chlid : public AAT02_Grenade
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;

public:
	AAT02_Grenade_Chlid();
protected:
	virtual void BeginPlay() override;
};
