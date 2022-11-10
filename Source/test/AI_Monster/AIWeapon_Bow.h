#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIWeapon_Bow.generated.h"

UCLASS()
class TEST_API AAIWeapon_Bow : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class AAIWeapon_Arrow> ArrowClass;

private:
	class ACharacter* Owner;
	
public:	
	AAIWeapon_Bow();

protected:
	virtual void BeginPlay() override;

public:
	static AAIWeapon_Bow* Spawn(UWorld* InWorld, ACharacter* InOwner);

public:
	void Begin_Fire();
	void   End_Fire();
};
