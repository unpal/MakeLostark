

#include "SkillComponent.h"
#include "GameFrameWork/Character.h"
#include "GameFramework/Actor.h"
USkillComponent::USkillComponent()
{
	Perfect_Shot_Casting = false;
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
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



