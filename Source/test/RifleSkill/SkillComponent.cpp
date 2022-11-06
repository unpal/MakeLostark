

#include "SkillComponent.h"
#include "../testCharacter.h"
#include "../testPlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "Target_Down.h"
#include "Gameframework/Character.h"
#include "particles/ParticleSystem.h"
#include "Kismet/GamePlayStatics.h"
USkillComponent::USkillComponent()
{
	Perfect_Shot_Casting = false;
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AtestCharacter>(GetOwner());
	PlayerContorller = Cast<AtestPlayerController>(Owner->GetController());
}

void USkillComponent::On_Focused_Shot()
{
	Owner->PlayAnimMontage(Focused_Shot_Montage, 1);
}

void USkillComponent::On_Perfect_Shot()
{
	Owner->PlayAnimMontage(Perfect_Shot_Start_Montage,0);
	Perfect_Shot_Casting = true;
	Owner->GetWorldTimerManager().SetTimer(Perfect_Shot_TimerHandle, this, &USkillComponent::End_Perfect_Shot, 2.4f, false);
}

void USkillComponent::End_Perfect_Shot()
{
	if (Perfect_Shot_Casting)
	{
		Owner->PlayAnimMontage(Perfect_Shot_End_Montage, 1);
		Perfect_Shot_Casting = false;
	}	
}

void USkillComponent::On_Target_Down()
{
	Owner->PlayAnimMontage(Target_Down_Montage, 1);
}

void USkillComponent::Begin_Target_Down()
{
	FTransform transform = Owner->GetTransform();
	ATarget_Down* target_down = Owner->GetWorld()->SpawnActorDeferred<ATarget_Down>(Target_Down_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(target_down, transform);
}



