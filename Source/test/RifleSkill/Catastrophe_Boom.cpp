

#include "Catastrophe_Boom.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/GamePlayStatics.h"
#include "particles/ParticleSystem.h"
ACatastrophe_Boom::ACatastrophe_Boom()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");



	ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(L"StaticMesh'/Game/Shape_Mesh/SM_Sphere.SM_Sphere'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>material(L"MaterialInstanceConstant'/Game/Bullet/M_Bullet_Inst.M_Bullet_Inst'");
	if (material.Succeeded()) Mesh->SetMaterial(0, material.Object);
	Mesh->SetupAttachment(Root);
	Mesh->SetRelativeScale3D(FVector(1, 0.025f, 0.025f));
	Mesh->SetRelativeRotation(FRotator(90, 0, 0));

	Projectile->InitialSpeed = 200;
	Projectile->MaxSpeed = 200;
	Projectile->ProjectileGravityScale = 0;
}

void ACatastrophe_Boom::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACatastrophe_Boom::Shoot(const FVector& InDirection)
{
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;

}

void ACatastrophe_Boom::Destroy_Boom()
{
	Destroy();
}


