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
}

void AtestPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
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
		FHitResult Hit;
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
	if (MyPawn&&bMove&&!IsDashing)
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
		if (!IsDashing) {
			MoveLookCursor();
			character->VisibleDashCoolDown();
			character->GetCharacterMovement()->StopMovementImmediately();
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
	GetHitResultUnderCursor(ECC_WorldDynamic, false, hit);
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
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
		character->Change_Stance_Left();
}

void AtestPlayerController::Change_Stance_Right()
{
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
		character->Change_Stance_Right();
}

void AtestPlayerController::General_Attack()
{
	MoveLookCursor();
	if (AtestCharacter* character = Cast<AtestCharacter>(GetPawn()))
	{
		character->GetCharacterMovement()->StopMovementImmediately();
		character->General_Attack();
		bMove = false;
	}
	
}

