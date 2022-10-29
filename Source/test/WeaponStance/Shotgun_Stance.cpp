#include "Shotgun_Stance.h"

AShotgun_Stance::AShotgun_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"");
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

