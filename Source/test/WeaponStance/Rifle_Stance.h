#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle_Stance.generated.h"

UCLASS()
class TEST_API ARifle_Stance : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_ShotGun";
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
	
public:	
	ARifle_Stance();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
