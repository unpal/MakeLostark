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
		FName HandSocket = "Hand_Rifle";
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
	
public:	
	AShotgun_Stance();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
