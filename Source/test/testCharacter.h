// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "testCharacter.generated.h"

UCLASS(Blueprintable)
class AtestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AtestCharacter();
	virtual void BeginPlay() override;
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	
	class UDashWidget* DashCoolDown;
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UDashWidget> DashCoolDownClass;
public:
	void VisibleDashCoolDown();
	void Change_Stance_Left();
	void Change_Stance_Right();

	public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AHandgun_Stance* Handgun_R;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AHandgun_Stance* Handgun_L;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AShotgun_Stance* Shotgun;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ARifle_Stance* Rifle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HandgunStance; // �ڵ�� ���Ľ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ShotgunStance; // ����   ���Ľ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool RifleStance;   // ������ ���Ľ�����
	void General_Attack();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkillComponent* Skill;
	void Q_Skill();
	void W_Skill_Start();
	void W_Skill_End();
	void E_Skill();
	FORCEINLINE bool GetHandgunStance(){ return HandgunStance; }
	FORCEINLINE bool GetShotgunStance(){ return ShotgunStance; }
	FORCEINLINE bool GetRifleStance(){ return RifleStance; }
};