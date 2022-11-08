
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shotgun_Rapid_Fire.generated.h"

UCLASS()
class TEST_API AShotgun_Rapid_Fire : public AActor
{
	GENERATED_BODY()
	
public:	
	AShotgun_Rapid_Fire();

protected:
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
