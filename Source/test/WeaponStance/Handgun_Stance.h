#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Handgun_Stance.generated.h"

UCLASS()
class TEST_API AHandgun_Stance : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket_Handgun_L = "Hand_HandGun_L";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket_Handgun_R = "Hand_HandGun_R";

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* GrabMontage;

private:
	class ACharacter* Owner;

public:	
	AHandgun_Stance();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	static AHandgun_Stance* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	void Handgun_Stance_R();
	void Handgun_Stance_L();
	void Destroy_Stance();
};
