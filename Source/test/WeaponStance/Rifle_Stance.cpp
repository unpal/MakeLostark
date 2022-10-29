#include "Rifle_Stance.h"

ARifle_Stance::ARifle_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"");
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

