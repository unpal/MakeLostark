// Fill out your copyright notice in the Description page of Project Settings.


#include "Target_Down_Notify.h"
#include "SkillComponent.h"
#include "GameFramework/Character.h"
FString UTarget_Down_Notify::GetNotifyName_Implementation() const
{
	return "Target_Down_Notify";
}

void UTarget_Down_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp) return;
	if (!MeshComp->GetOwner()) return;

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	if (!character) return;

	TArray<USkillComponent*> components;
	character->GetComponents<USkillComponent>(components);

	for (USkillComponent* component : components)
	{
		if (component->GetName() == "Skill")
		{
			component->Begin_Target_Down();
			return;
		}
	}
}
