#include "Shotgun_Stance.h"
#include "Gameframework/Character.h"

AShotgun_Stance::AShotgun_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Shotgun_A.Shotgun_A'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

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
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void AShotgun_Stance::Destroy_Stance()
{
	Destroy();
}

