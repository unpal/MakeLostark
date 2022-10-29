#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Manage.generated.h"

UCLASS()
class TEST_API AWeapon_Manage : public AActor
{
	GENERATED_BODY()


private:
	class AHandgun_Stance* Handgun;
	class AShotgun_Stance* Shotgun;
	class ARifle_Stance* Rifle;

public:	
	AWeapon_Manage();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

private:
	void AfterStance(float axis); // z키를 입력했을떄
	void BeforeStance(float axis); // x키를 입력했을떄

private:
	bool HandgunStance; // 핸드건 스탠스인지
	bool ShotgunStance; // 샷건   스탠스인지
	bool RifleStance;   // 라이플 스탠스인지
};
