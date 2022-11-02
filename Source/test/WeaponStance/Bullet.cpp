#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");

	Capsule->SetRelativeRotation(FRotator(90, 0, 0));
	Capsule->SetCapsuleHalfHeight(50);
	Capsule->SetCapsuleRadius(2);
	Capsule->SetCollisionProfileName("BlockAllDynamic");


	ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(L"StaticMesh'/Game/Shape_Mesh/SM_Sphere.SM_Sphere'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>material(L"MaterialInstanceConstant'/Game/Bullet/M_Bullet_Inst.M_Bullet_Inst'");
	if (material.Succeeded()) Mesh->SetMaterial(0, material.Object);
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeScale3D(FVector(1, 0.025f, 0.025f));
	Mesh->SetRelativeRotation(FRotator(90, 0, 0));

	Projectile->InitialSpeed = 2e+4f;
	Projectile->MaxSpeed = 2e+4f;
	Projectile->ProjectileGravityScale = 0;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}


void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
}

void ABullet::Shoot(const FVector& InDirection)
{
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
	GetWorldTimerManager().SetTimer(BulletDostroyTimerHandle,
		this, &ABullet::DestroyBullet, 0.5f, false);
}

void ABullet::DestroyBullet()
{
	Destroy();
}
