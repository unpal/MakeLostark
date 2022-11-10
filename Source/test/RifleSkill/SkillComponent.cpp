

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
#include "../WeaponStance/Shotgun_Stance.h"
#include "../HandgunSkill/AT02_Grenade_Boom.h"
#include "../HandgunSkill/Equilibrium.h"
#include "../ShotgunSkill/Last_Request.h"
#include "../ShotgunSkill/Shotgun_Rapid_Fire.h"
#include "../ShotgunSkill/Dual_Buckshot.h"
#include "../ShotgunSkill/Sharpshooter.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	(Cast<AtestPlayerController>(Owner->GetController())->GetHitResultUnderCursor(ECC_Visibility, false, hit));
}

void USkillComponent::Begin_AT02_Grenade()
{
	FVector muzzleLocation = Cast<AHandgun_Stance>(Cast<AtestCharacter>(GetOwner())->Handgun_L)->Mesh->GetSocketLocation("MuzzleFlash");
	FVector direction = GetOwner()->GetActorForwardVector();
	FVector spawnLocation = muzzleLocation + direction * 100;
	AT02_Grenade_Boom = GetOwner()->GetWorld()->SpawnActor<AAT02_Grenade_Boom>(
		AAT02_Grenade_Boom_Class, spawnLocation, direction.Rotation());
	AT02_Grenade_Boom->Throw_Boom(spawnLocation,
		hit.ImpactPoint,
		0.5f,
		FVector::ZeroVector);

}

void USkillComponent::On_Equilibrium()
{
	Owner->PlayAnimMontage(Equilibrium_Montage, 1);
}

void USkillComponent::Begin_Equilibrium()
{
	FTransform transform_L = Cast<AHandgun_Stance>(Owner->Handgun_L)->Mesh->GetSocketTransform("MuzzleFlash");
	FTransform transform_R = Cast<AHandgun_Stance>(Owner->Handgun_R)->Mesh->GetSocketTransform("MuzzleFlash");
	Equilibrium_L = Owner->GetWorld()->SpawnActorDeferred<AEquilibrium>(Equilibrium_Class, transform_L, Owner);
	Equilibrium_R = Owner->GetWorld()->SpawnActorDeferred<AEquilibrium>(Equilibrium_Class, transform_R, Owner);
	UGameplayStatics::FinishSpawningActor(Equilibrium_L, transform_L);
	UGameplayStatics::FinishSpawningActor(Equilibrium_R, transform_R);
}

void USkillComponent::On_Peacekeeper()
{
	FVector forward = Owner->GetActorForwardVector() * 10000;
	Owner->GetCharacterMovement()->AddImpulse(forward, true);
	Owner->PlayAnimMontage(Peacekeeper_Montage, 1);
}

void USkillComponent::Begin_Peacekeeper()
{
}


void USkillComponent::Quick_Step_Shot()
{
	FVector forward = Owner->GetActorForwardVector() * 10000;
	Owner->GetCharacterMovement()->AddImpulse(forward, true);
	Owner->PlayAnimMontage(Quick_Step_Montage, 1);
}

void USkillComponent::On_Shotgun_Rapid_Fire()
{
	Owner->PlayAnimMontage(Shotgun_Rapid_Fire_Montage, 1);
}

void USkillComponent::Begin_Shotgun_Rapid_Fire()
{
	FTransform transform = Cast<AShotgun_Stance>(Owner->Shotgun)->Mesh->GetSocketTransform("MuzzleFlash");
	Shotgun_Rapid_Fire = Owner->GetWorld()->SpawnActorDeferred<AShotgun_Rapid_Fire>(Shotgun_Rapid_Fire_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(Shotgun_Rapid_Fire, transform);
}

void USkillComponent::On_Last_Request_Fire()
{
	Owner->PlayAnimMontage(Last_Request_Montage, 1);
}

void USkillComponent::Begin_Last_Request_Fire()
{
	FTransform transform = Cast<AShotgun_Stance>(Owner->Shotgun)->Mesh->GetSocketTransform("MuzzleFlash");
	Last_Request = Owner->GetWorld()->SpawnActorDeferred<ALast_Request>(Last_Request_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(Last_Request, transform);
}

void USkillComponent::On_Dual_Buckshot_Fire()
{
	Owner->PlayAnimMontage(Dual_Buckshot_Montage_1, 1);
}

void USkillComponent::Begin_Dual_Buckshot_Fire()
{
	FTransform transform = Cast<AShotgun_Stance>(Owner->Shotgun)->Mesh->GetSocketTransform("MuzzleFlash");
	Dual_Buckshot = Owner->GetWorld()->SpawnActorDeferred<ADual_Buckshot>(Dual_Buckshot_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(Dual_Buckshot, transform);
}

void USkillComponent::On_Sharpshooter()
{
	Owner->PlayAnimMontage(Sharpshooter_Montage, 1);
}

void USkillComponent::Begin_Sharpshooter_R()
{
	FTransform transform = Cast<AShotgun_Stance>(Owner->Shotgun)->Mesh->GetSocketTransform("MuzzleFlash");
	Sharpshooter = Owner->GetWorld()->SpawnActorDeferred<ASharpshooter>(Sharpshooter_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(Sharpshooter, transform);
}
void USkillComponent::Begin_Sharpshooter_L()
{
	FTransform transform = Cast<AShotgun_Stance>(Owner->Shotgun2)->Mesh->GetSocketTransform("MuzzleFlash");
	Sharpshooter = Owner->GetWorld()->SpawnActorDeferred<ASharpshooter>(Sharpshooter_Class, transform, Owner);
	UGameplayStatics::FinishSpawningActor(Sharpshooter, transform);
}


