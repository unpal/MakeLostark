#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shotgun_Stance.generated.h"

UCLASS()
class TEST_API AShotgun_Stance : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket_Shotgun = "Hand_Shotgun";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket_Shotgun_L = "Hand_HandGun_L";
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
	UFUNCTION(BlueprintCallable)
	void Shotgun_Stance();
	void Destroy_Stance();
	void General_Attack();
	UFUNCTION(BlueprintCallable)
	void Shotgun_Stnace_L();
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* FlashParticle;
	UFUNCTION(BlueprintCallable)
		void PlayMuzzleFlash();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGeneral_Attack;
};
