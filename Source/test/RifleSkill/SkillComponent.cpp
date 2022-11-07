

#include "SkillComponent.h"
#include "../testCharacter.h"
#include "../testPlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "Target_Down.h"
#include "Gameframework/Character.h"
#include "particles/ParticleSystem.h"
#include "Kismet/GamePlayStatics.h"
#include "Catastrophe.h"
#include "Catastrophe_Child.h"
#include "Catastrophe_Boom.h"
#include "../testCharacter.h"
#include "../WeaponStance/Rifle_Stance.h"
#include "../WeaponStance/Handgun_Stance.h"
#include "../HandgunSkill/AT02_Grenade_Boom.h"
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
	FHitResult hit;
	(Cast<AtestPlayerController>(Owner->GetController())->GetHitResultUnderCursor(ECC_Visibility, false, hit));
	FTransform transform = FTransform(hit.ImpactPoint);
	ATarget_Down* target_down = Owner->GetWorld()->SpawnActorDeferred<ATarget_Down>(Target_Down_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(target_down, transform);
}
void USkillComponent::On_Catastrophe()
{
	Catastrophe_Casting = true;
	Owner->PlayAnimMontage(Catastrophe_Montage, 0);
	FVector muzzleLocation = Cast<ARifle_Stance>(Cast<AtestCharacter>(GetOwner())->Rifle)->Mesh->GetSocketLocation("MuzzleFlash");
	FVector direction = GetOwner()->GetActorForwardVector();
	FVector spawnLocation = muzzleLocation + direction * 100;
	Catastrophe_Boom = GetOwner()->GetWorld()->SpawnActor<ACatastrophe_Boom>(
		Catastrophe_Boom_Class, spawnLocation, direction.Rotation());
	Catastrophe_Boom->Shoot(direction);

	Owner->GetWorldTimerManager().SetTimer(Catastrophe_TimerHandle, this, &USkillComponent::Begin_Catastrophe, 2.0f);
}
void USkillComponent::Begin_Catastrophe()
{
	if (!Catastrophe_Casting) return;
	Owner->PlayAnimMontage(Catastrophe_End_Montage, 1);
	FTransform transform = Catastrophe_Boom->GetTransform();
	ACatastrophe* Catastrophe = Owner->GetWorld()->SpawnActorDeferred<ACatastrophe>(Catastrophe_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(Catastrophe, transform);
	Catastrophe_Boom->Destroy_Boom();
	Catastrophe_Casting = false;

}

void USkillComponent::On_AT02_Grenade()
{
	Owner->PlayAnimMontage(AT02_Grenade_Montage, 1);
}

void USkillComponent::Begin_AT02_Grenade()
{
	FHitResult hit;
	(Cast<AtestPlayerController>(Owner->GetController())->GetHitResultUnderCursor(ECC_Visibility, false, hit));
	FVector muzzleLocation = Cast<AHandgun_Stance>(Cast<AtestCharacter>(GetOwner())->Handgun_L)->Mesh->GetSocketLocation("MuzzleFlash");
	FVector direction = GetOwner()->GetActorForwardVector();
	FVector spawnLocation = muzzleLocation + direction * 100;
	AT02_Grenade_Boom = GetOwner()->GetWorld()->SpawnActor<AAT02_Grenade_Boom>(
		AAT02_Grenade_Boom_Class, spawnLocation, direction.Rotation());
	AT02_Grenade_Boom->Throw_Boom(spawnLocation,
		hit.ImpactPoint,
		0.1f,
		FVector::ZeroVector);

}


