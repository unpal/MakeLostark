// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sharpshooter.h"
#include "Sharpshooter_Child.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ASharpshooter_Child : public ASharpshooter
{
	GENERATED_BODY()
public:
	ASharpshooter_Child();

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;
};
