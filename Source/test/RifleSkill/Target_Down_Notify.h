// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Target_Down_Notify.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UTarget_Down_Notify : public UAnimNotify
{
	GENERATED_BODY()
private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
