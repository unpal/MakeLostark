#include "Handgun_Stance.h"
#include "GameFramework/Character.h"
#include "Bullet.h"
#include "../testPlayerController.h"
#include "particles/ParticleSystem.h"
#include "Kismet/GamePlayStatics.h"
AHandgun_Stance::AHandgun_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabMontage(L"AnimMontage'/Game/Stance/Handgun_Stance_Montage.Handgun_Stance_Montage'");
	if (grabMontage.Succeeded()) GrabMontage = grabMontage.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> general_attack_montage1(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Combo03_1_Montage.Frank_RPG_Gunslinger_Combo03_1_Montage'");
	if (grabMontage.Succeeded()) General_Attack_Montage1 = general_attack_montage1.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> general_attack_montage2(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Combo03_2_Montage.Frank_RPG_Gunslinger_Combo03_2_Montage'");
	if (grabMontage.Succeeded()) General_Attack_Montage2 = general_attack_montage2.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> general_attack_montage3(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Combo03_3_Montage.Frank_RPG_Gunslinger_Combo03_3_Montage'");
	if (grabMontage.Succeeded()) General_Attack_Montage3 = general_attack_montage3.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> general_attack_montage4(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Combo03_4_Montage.Frank_RPG_Gunslinger_Combo03_4_Montage'");
	if (grabMontage.Succeeded()) General_Attack_Montage4 = general_attack_montage4.Object;
	ConstructorHelpers::FClassFinder<ABullet>bullet(L"Blueprint'/Game/Bullet/BP_Bullet.BP_Bullet_C'");
	if (bullet.Succeeded())BulletClass = bullet.Class;
	ConstructorHelpers::FObjectFinder<UParticleSystem>flashparticle(L"ParticleSystem'/Game/MilitaryWeapSilver/FX/P_Pistol_MuzzleFlash_01.P_Pistol_MuzzleFlash_01'");
	if (flashparticle.Succeeded())FlashParticle = flashparticle.Object;
	bGeneral_Attack = true;
}

void AHandgun_Stance::BeginPlay()
{
	Super::BeginPlay();

}

void AHandgun_Stance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AHandgun_Stance* AHandgun_Stance::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params1; 
	params1.Owner = InOwner; 

	return InWorld->SpawnActor<AHandgun_Stance>(params1); 
}

void AHandgun_Stance::Handgun_Stance_R()
{
	Owner = Cast<ACharacter>(GetOwner());
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket_Handgun_R);
}

void AHandgun_Stance::Handgun_Stance_L()
{
	Owner = Cast<ACharacter>(GetOwner());
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket_Handgun_L);
}

void AHandgun_Stance::Destroy_Stance()
{
	Destroy();
}
void AHandgun_Stance::General_Attack()
{
	General_Attack_Count++;
	if (!bGeneral_Attack) return;
	Owner->PlayAnimMontage(General_Attack_Montage1, 1);
	bGeneral_Attack = false;
}
void AHandgun_Stance::General_Attack_And()
{
	if (General_Attack_Count > 1 && General_Attack_And_Count < 3) {
		General_Attack_Count = 0;
		if (General_Attack_And_Count == 0)
			Owner->PlayAnimMontage(General_Attack_Montage2, 1);
		if (General_Attack_And_Count == 1)
			Owner->PlayAnimMontage(General_Attack_Montage3, 1);
		if (General_Attack_And_Count == 2)
			Owner->PlayAnimMontage(General_Attack_Montage4, 1);
		General_Attack_And_Count++;
	}
	else {
		General_Attack_Count = 0;
		General_Attack_And_Count = 0;
		bGeneral_Attack = true;
	}
}

void AHandgun_Stance::General_Attack_Bullet_Shoot()
{
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	FVector direction = GetOwner()->GetActorForwardVector();
	FVector spawnLocation = muzzleLocation + direction * 100;
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(
		BulletClass, spawnLocation, direction.Rotation());
	if (FlashParticle)
		UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	bullet->Shoot(direction);
}
