// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target_Down.h"
#include "../testCharacter.h"
#include "Target_Down_child.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATarget_Down_child : public ATarget_Down
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
	 	class UParticleSystemComponent* Particle;


public:
	ATarget_Down_child();

protected:
	virtual void BeginPlay() override;
};
