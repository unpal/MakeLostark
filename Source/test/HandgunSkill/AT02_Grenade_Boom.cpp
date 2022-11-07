

#include "AT02_Grenade_Boom.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/GamePlayStatics.h"
#include "particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
AAT02_Grenade_Boom::AAT02_Grenade_Boom()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>("MoveComponent");


	ConstructorHelpers::FObjectFinder<UStaticMesh>mesh(L"StaticMesh'/Game/Shape_Mesh/SM_Sphere.SM_Sphere'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>material(L"MaterialInstanceConstant'/Game/Bullet/M_Bullet_Inst.M_Bullet_Inst'");
	if (material.Succeeded()) Mesh->SetMaterial(0, material.Object);
	Mesh->SetupAttachment(Root);
}

void AAT02_Grenade_Boom::BeginPlay()
{
	Super::BeginPlay();

}

void AAT02_Grenade_Boom::Throw_Boom(FVector Start, FVector Target, float arcValue, FVector outVelocity)
{
	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, Start, Target, GetWorld()->GetGravityZ(), arcValue))
	{
		FPredictProjectilePathParams predictParams(20.0f, Start, outVelocity, 15.0f);   // 20: tracing 보여질 프로젝타일 크기, 15: 시물레이션되는 Max 시간(초)
		predictParams.DrawDebugTime = 15.0f;     //디버그 라인 보여지는 시간 (초)
		predictParams.DrawDebugType = EDrawDebugTrace::Type::ForDuration;  // DrawDebugTime 을 지정하면 EDrawDebugTrace::Type::ForDuration 필요.
		predictParams.OverrideGravityZ = GetWorld()->GetGravityZ();
		FPredictProjectilePathResult result;
		UGameplayStatics::PredictProjectilePath(this, predictParams, result);

		CharacterMovement->AddImpulse(outVelocity); // objectToSend는 발사체
	}
}


