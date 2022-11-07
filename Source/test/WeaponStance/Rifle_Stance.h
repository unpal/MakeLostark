#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle_Stance.generated.h"

UCLASS()
class TEST_API ARifle_Stance : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket_Rifle = "Hand_Rifle";

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		class UAnimMontage* GrabMontage;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* General_Attack_Montage;
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
	void General_Attack();
	UFUNCTION(BlueprintCallable)
	void General_Attack_Bullet_Shoot();
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABullet> BulletClass;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* FlashParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGeneral_Attack;
};
