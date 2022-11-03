#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shotgun_Stance.generated.h"

UCLASS()
class TEST_API AShotgun_Stance : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket_Shotgun = "Hand_Shotgun";

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* GrabMontage;
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* General_Attack_Montage;
private:
	class ACharacter* Owner;

public:	
	AShotgun_Stance();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
public:
	static AShotgun_Stance* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	void Shotgun_Stance();
	void Destroy_Stance();
	void General_Attack();
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* FlashParticle;
	UFUNCTION(BlueprintCallable)
		void PlayMuzzleFlash();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGeneral_Attack;
};
