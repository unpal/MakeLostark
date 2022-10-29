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
		FName HandSocket = "Hand_HandGun_R";
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
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

};
