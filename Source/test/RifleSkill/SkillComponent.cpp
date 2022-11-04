

#include "SkillComponent.h"
#include "GameFrameWork/Character.h"
USkillComponent::USkillComponent()
{

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



