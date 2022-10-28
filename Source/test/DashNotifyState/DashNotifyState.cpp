// Fill out your copyright notice in the Description page of Project Settings.


#include "DashNotifyState.h"
#include "../testCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../testPlayerController.h"
void UDashNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) 
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (AtestCharacter* character = Cast<AtestCharacter>(MeshComp->GetOwner())) 
	{
		FVector forward = character->GetActorForwardVector() * 100;


		character->GetCharacterMovement()->AddImpulse(forward, true);
	}
}
void UDashNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AtestCharacter* character = Cast<AtestCharacter>(MeshComp->GetOwner()))
	{
		AtestPlayerController* controller = Cast<AtestPlayerController>(character->GetController());
		controller->EndDash();
	}
}
