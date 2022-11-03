#include "Shotgun_Stance.h"
#include "Gameframework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GamePlayStatics.h"
AShotgun_Stance::AShotgun_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Shotgun_A.Shotgun_A'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabMontage(L"AnimMontage'/Game/Stance/Shotgun_Stance_Montage.Shotgun_Stance_Montage'");
	if (grabMontage.Succeeded()) GrabMontage = grabMontage.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> general_attack_montage(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Attack01_Montage.Frank_RPG_Gunslinger_Attack01_Montage'");
	if (general_attack_montage.Succeeded()) General_Attack_Montage = general_attack_montage.Object;
	ConstructorHelpers::FObjectFinder<UParticleSystem>flashparticle(L"ParticleSystem'/Game/MilitaryWeapSilver/FX/P_Shotgun_MuzzleFlash_01.P_Shotgun_MuzzleFlash_01'");
	if (flashparticle.Succeeded()) FlashParticle = flashparticle.Object;
	bGeneral_Attack = true;
}

void AShotgun_Stance::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShotgun_Stance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AShotgun_Stance* AShotgun_Stance::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<AShotgun_Stance>(params);
}

void AShotgun_Stance::Shotgun_Stance()
{
	Owner = Cast<ACharacter>(GetOwner());
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket_Shotgun);
}

void AShotgun_Stance::Destroy_Stance()
{
	Destroy();

}

void AShotgun_Stance::General_Attack()
{
	if (!bGeneral_Attack) return;
	Owner = Cast<ACharacter>(GetOwner());
	Owner->PlayAnimMontage(General_Attack_Montage, 1);
	bGeneral_Attack = false;
}

void AShotgun_Stance::PlayMuzzleFlash()
{
	if (FlashParticle)
		UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
}

