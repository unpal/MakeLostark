// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "testPlayerController.generated.h"

UCLASS()
class AtestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AtestPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
public:
	void Dash();
	void MoveLookCursor();
	void EndDash();
	void SecondDash();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DashCount;
	bool bSecondDash;
	bool IsDashing;
	FTimerHandle DashTimerHandle;
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* FirstDashMontage;
	UAnimMontage* SecondDashMontage;
	void Change_Stance_Left();
	void Change_Stance_Right();
	void General_Attack();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMove;
	void Q_Skill();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Is_Q_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Focused_Shot_Combo_Count;
	void W_Skill_Start();
	void W_Skill_End();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_W_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool b_Perfect_Shot;
	void E_Skill();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_E_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Target_Down_Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_R_Skill;
	UPROPERTY(EditAnywhere)
		FHitResult Hit;
	void R_Skill();
	void R_Skill_End();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Combo_Q;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PeaceKeeper_Combo_Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PeaceKeeper_Input_Count;
	void A_Skill();
	void S_Skill();
	void D_Skill();
	void F_Skill();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_A_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_S_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_D_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_F_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int S_Skill_Combo;
};


