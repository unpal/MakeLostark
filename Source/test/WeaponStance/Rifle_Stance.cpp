#include "Rifle_Stance.h"
#include "Gameframework/Character.h"

ARifle_Stance::ARifle_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Sniper_Rifle_A.Sniper_Rifle_A'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

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
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ARifle_Stance::Destroy_Stance()
{
	Destroy();
}


