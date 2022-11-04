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
	INT32 DashCount;
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
	void Focused_Shot();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFocused_Shot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Focused_Shot_Combo_Count;
};


