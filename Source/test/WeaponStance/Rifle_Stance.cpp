#include "Rifle_Stance.h"
#include "Gameframework/Character.h"
#include "Bullet.h"
ARifle_Stance::ARifle_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Sniper_Rifle_A.Sniper_Rifle_A'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabMontage(L"AnimMontage'/Game/Stance/Rifle_Stance_Montage.Rifle_Stance_Montage'");
	if (grabMontage.Succeeded()) GrabMontage = grabMontage.Object;
	ConstructorHelpers::FObjectFinder<UAnimMontage> general_attack_montage(L"AnimMontage'/Game/Montage/Frank_RPG_Gunslinger_Attack03_Montage.Frank_RPG_Gunslinger_Attack03_Montage'");
	if (general_attack_montage.Succeeded()) General_Attack_Montage = general_attack_montage.Object;
	ConstructorHelpers::FClassFinder<ABullet>bullet(L"Blueprint'/Game/Bullet/BP_Bullet.BP_Bullet_C'");
	if (bullet.Succeeded())BulletClass = bullet.Class;
}

void ARifle_Stance::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARifle_Stance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ARifle_Stance* ARifle_Stance::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<ARifle_Stance>(params);
}

void ARifle_Stance::Rifle_Stance()
{
	Owner = Cast<ACharacter>(GetOwner());
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket_Rifle);
}

void ARifle_Stance::Destroy_Stance()
{
	Destroy();
}

void ARifle_Stance::General_Attack()
{
	Owner->PlayAnimMontage(General_Attack_Montage, 1);
}
void ARifle_Stance::General_Attack_Bullet_Shoot()
{
	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");
	FVector direction = GetOwner()->GetActorForwardVector();
	FVector spawnLocation = muzzleLocation + direction * 100;
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(
		BulletClass, spawnLocation, direction.Rotation());
	bullet->Shoot(direction);
}


