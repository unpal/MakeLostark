// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Catastrophe.h"
#include "Catastrophe_Child.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ACatastrophe_Child : public ACatastrophe
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;

public:
	ACatastrophe_Child();
protected:
	virtual void BeginPlay() override;
};
