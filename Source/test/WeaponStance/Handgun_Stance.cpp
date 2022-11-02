#include "Handgun_Stance.h"
#include "Gameframework/Character.h"

AHandgun_Stance::AHandgun_Stance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabMontage(L"AnimMontage'/Game/Stance/Handgun_Stance_Montage.Handgun_Stance_Montage'");
	if (grabMontage.Succeeded()) GrabMontage = grabMontage.Object;

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

