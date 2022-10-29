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
		FName HandSocket = "Hand_HandGun_R";
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
private:
	class ACharacter* Owner;
public:	
	ARifle_Stance();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	static ARifle_Stance* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	void Rifle_Stance();
	void Destroy_Stance();
};
