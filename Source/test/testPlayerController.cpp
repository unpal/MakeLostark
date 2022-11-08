// Copyright Epic Games, Inc. All Rights Reserved.

#include "testPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "testCharacter.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
AtestPlayerController::AtestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	ConstructorHelpers::FObjectFinder<UAnimMontage>montage(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Evade.Frank_RPG_Gunslinger_Evade'");
	if (montage.Succeeded())FirstDashMontage = montage.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage>montage2(L"AnimMontage'/Game/Montage/Frangk_RPG_Gunslinger_Jump.Frangk_RPG_Gunslinger_Jump'");
	if (montage.Succeeded())SecondDashMontage = montage2.Object;
	bMove = true;
	Is_Q_Skill = false;
}

void AtestPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	if(b_Perfect_Shot)
		MoveLookCursor();
}

void AtestPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AtestPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AtestPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AtestPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AtestPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AtestPlayerController::OnResetVR);
	InputComponent->BindAction("dash", IE_Pressed, this, &AtestPlayerController::Dash);
	InputComponent->BindAction("ChangeStanceLeft", IE_Pressed, this, &AtestPlayerController::Change_Stance_Left);
	InputComponent->BindAction("ChangeStanceRight", IE_Pressed, this, &AtestPlayerController::Change_Stance_Right);
	InputComponent->BindAction("General_Attack", IE_Pressed, this, &AtestPlayerController::General_Attack);
	InputComponent->BindAction("Q_Skill", IE_Pressed, this, &AtestPlayerController::Q_Skill);
	InputComponent->BindAction("W_Skill", IE_Pressed, this, &AtestPlayerController::W_Skill_Start);
	InputComponent->BindAction("W_Skill", IE_Released, this, &AtestPlayerController::W_Skill_End);
	InputComponent->BindAction("E_Skill", IE_Pressed, this, &AtestPlayerController::E_Skill);
	InputComponent->BindAction("R_Skill", IE_Pressed, this, &AtestPlayerController::R_Skill);
	InputComponent->BindAction("R_Skill", IE_Released, this, &AtestPlayerController::R_Skill_End);

}

void AtestPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AtestPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AtestCharacter* MyPawn = Cast<AtestCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AtestPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AtestPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn&&bMove&&!IsDashing&&!Is_Q_Skill&&!Is_W_Skill&&!Is_E_Skill&&!Is_R_Skill)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AtestPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AtestPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AtestPlayerController::Dash()
{
	DashCount++;
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn())) {
		if (!IsDashing||!Is_Q_Skill ||! Is_W_Skill || !Is_E_Skill || !Is_R_Skill) {
			MoveLookCursor();
			character->VisibleDashCoolDown();
			character->GetCharacterMovement()->StopMovementImmediately();
			R_Skill_End();
			IsDashing = true;
			FVector forward = character->GetActorForwardVector() * 12000;

			character->PlayAnimMontage(FirstDashMontage,1);
			character->GetCharacterMovement()->AddImpulse(forward, true);
			GetWorldTimerManager().SetTimer(DashTimerHandle, this, &AtestPlayerController::EndDash, 0.25f, false);
		}
	}
}

void AtestPlayerController::MoveLookCursor()
{
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Visibility, false, hit);
	if(hit.bBlockingHit)
	{
		APawn* const MyPawn = GetPawn();
		if(MyPawn)
		{
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(),
				FVector(hit.Location.X, hit.Location.Y, hit.Location.Z));

			FRotator rotator;

			rotator.Yaw   = LookRotation.Yaw;
			rotator.Roll  = MyPawn->GetActorRotation().Roll;
			rotator.Pitch = MyPawn->GetActorRotation().Pitch;


			MyPawn->SetActorRotation(rotator);
		}
	}
	
}

void AtestPlayerController::EndDash()
{
	if (DashCount > 1 && bSecondDash)
	{
		SecondDash();
		return;
	}
	IsDashing = false;
	bSecondDash = true;
	DashCount = 0;
	bMove = true;
}

void AtestPlayerController::SecondDash()
{
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		MoveLookCursor();
		bSecondDash = false;
		character->GetCharacterMovement()->StopMovementImmediately();

		character->PlayAnimMontage(SecondDashMontage, 1.5f);

		GetWorldTimerManager().SetTimer(DashTimerHandle, this, &AtestPlayerController::EndDash, 0.25f, false);
	}
}

void AtestPlayerController::Change_Stance_Left()
{
	if (!bMove|| Is_Q_Skill || Is_W_Skill || Is_E_Skill || Is_R_Skill) return;
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
		character->Change_Stance_Left();
}

void AtestPlayerController::Change_Stance_Right()
{
	if (!bMove|| Is_Q_Skill || Is_W_Skill || Is_E_Skill || Is_R_Skill) return;
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
		character->Change_Stance_Right();
}

void AtestPlayerController::General_Attack()
{
	if (IsDashing|| Is_Q_Skill|| Is_W_Skill||Is_E_Skill|| Is_R_Skill) return;
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		if(bMove)
		MoveLookCursor();
		if(Is_E_Skill)
		{
			character->E_Skill();
			Target_Down_Count++;
			if(Target_Down_Count >= 3)
			{
				Target_Down_Count = 0;
				Is_E_Skill = false;
			}
			return;
		}
		character->GetCharacterMovement()->StopMovementImmediately();
		character->General_Attack();
		bMove = false;
	}
	
}

void AtestPlayerController::Q_Skill()
{
	if (Is_Q_Skill) return;
	if (Is_W_Skill) return;
	if (Is_E_Skill) return;
	if (Is_R_Skill) return;
	MoveLookCursor();
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{

			Is_Q_Skill = true;
			character->GetCharacterMovement()->StopMovementImmediately();
			character->Q_Skill();
	}
}

void AtestPlayerController::W_Skill_Start()
{

	if (Is_Q_Skill) return;
	if (IsDashing) return;
	if (Is_E_Skill) return;
	if (Is_R_Skill) return;
	MoveLookCursor();
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		if (character->GetRifleStance())
			b_Perfect_Shot = true;
			Is_W_Skill = true;
			character->GetCharacterMovement()->StopMovementImmediately();
			character->W_Skill_Start();
	}
}

void AtestPlayerController::W_Skill_End()
{
	if (IsDashing) return;

	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		if (character->GetRifleStance())
		{
		Is_W_Skill = false;
		b_Perfect_Shot = false;
		character->W_Skill_End();
		}
	}
}

void AtestPlayerController::E_Skill()
{
	if (Is_Q_Skill) return;
	if (Is_W_Skill) return;
	if (Is_R_Skill) return;
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		if (character->GetRifleStance())
		{
			if (!Is_E_Skill)
			{
				character->GetCharacterMovement()->StopMovementImmediately();
				Is_E_Skill = true;
				return;
			}
			MoveLookCursor();
			character->E_Skill();
			Target_Down_Count++;
			if (Target_Down_Count >= 3)
			{
				Target_Down_Count = 0;
				Is_E_Skill = false;
			}
		}
	}
}

void AtestPlayerController::R_Skill()
{
	if (Is_Q_Skill) return;
	if (Is_W_Skill) return;
	if (Is_E_Skill) return;
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		Is_R_Skill = true;
		character->GetCharacterMovement()->StopMovementImmediately();
		MoveLookCursor();
		character->R_Skill();
	}
}

void AtestPlayerController::R_Skill_End()
{
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		if (character->GetRifleStance())
		{
			character->R_Skill_End();
			Is_R_Skill = false;

		}
	}
}


