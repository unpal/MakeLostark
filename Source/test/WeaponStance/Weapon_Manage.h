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
	void AfterStance(float axis); // zŰ�� �Է�������
	void BeforeStance(float axis); // xŰ�� �Է�������

private:
	bool HandgunStance; // �ڵ�� ���Ľ�����
	bool ShotgunStance; // ����   ���Ľ�����
	bool RifleStance;   // ������ ���Ľ�����
};
