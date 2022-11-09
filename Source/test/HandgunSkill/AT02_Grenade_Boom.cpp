

#include "AT02_Grenade_Boom.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/GamePlayStatics.h"
#include "particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "AT02_Grenade.h"
AAT02_Grenade_Boom::AAT02_Grenade_Boom()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(L"StaticMesh'/Game/Shape_Mesh/SM_Sphere.SM_Sphere'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>material(L"MaterialInstanceConstant'/Game/Bullet/M_Bullet_Inst.M_Bullet_Inst'");
	if (material.Succeeded()) Mesh->SetMaterial(0, material.Object);
	Mesh->SetupAttachment(Sphere);
}

void AAT02_Grenade_Boom::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentHit.AddDynamic(this, &AAT02_Grenade_Boom::OnHit);
}

void AAT02_Grenade_Boom::Throw_Boom(FVector Start, FVector Target, float arcValue, FVector outVelocity)
{
	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, Start, Target, GetWorld()->GetGravityZ(), arcValue))
	{
		Projectile->Velocity = outVelocity;
	}
}

void AAT02_Grenade_Boom::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, L"OnHit¹ß»ý");
	FTransform transform = GetTransform();
	AT02_Grenade = GetWorld()->SpawnActor<AAT02_Grenade>(AT02_Grenade_Class,GetActorLocation(),GetActorRotation());
	Destroy();
}


