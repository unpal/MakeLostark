// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Last_Request.generated.h"

UCLASS()
class TEST_API ALast_Request : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALast_Request();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* ActionEffect;
	UPROPERTY(EditAnywhere)
		FTransform ActionEffectTransform;
	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* HitEffect;
	UPROPERTY(EditAnywhere)
		FTransform HitEffectTransform;
	void ActionPlayEffect(class UWorld* Inworld, class ACharacter* InOwner);
	void ActionPlayEffect(class USkeletalMeshComponent* mesh, FName InSocketName = NAME_None);
	void HitPlayEffect(class UWorld* Inworld, class ACharacter* InOwner);
	void HitPlayEffect(class USkeletalMeshComponent* mesh, FName InSocketName = NAME_None);
};
