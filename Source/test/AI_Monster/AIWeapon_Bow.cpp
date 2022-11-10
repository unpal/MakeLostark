#include "AIWeapon_Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "AIWeapon_Arrow.h"

AAIWeapon_Bow::AAIWeapon_Bow()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Skeleton_archer/mesh/weapon/SK_bow.SK_bow'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FClassFinder<AAIWeapon_Arrow> aiArrow(L"Blueprint'/Game/Monster/BP_Bow.BP_Bow_C'");
	if (aiArrow.Succeeded()) ArrowClass = aiArrow.Class;
}

void AAIWeapon_Bow::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), L"WeaponSocket");
}

AAIWeapon_Bow* AAIWeapon_Bow::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<AAIWeapon_Bow>(params);
}

void AAIWeapon_Bow::Begin_Fire()
{
	if (ArrowClass)
	{
		FVector arrowLocation = Mesh->GetSocketLocation("Fire");
		FVector spawnLocation = arrowLocation + Owner->GetActorForwardVector();
		FRotator spawnRotation = Owner->GetActorRotation() + FRotator(0, 180, 0);
		AAIWeapon_Arrow* arrow = GetWorld()->SpawnActor<AAIWeapon_Arrow>(ArrowClass, arrowLocation, spawnRotation);
		arrow->Shoot(Owner->GetActorForwardVector());
	}
}

void AAIWeapon_Bow::End_Fire()
{
}



