

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
		FPredictProjectilePathParams predictParams(20.0f, Start, outVelocity, 15.0f);   // 20: tracing ������ ������Ÿ�� ũ��, 15: �ù����̼ǵǴ� Max �ð�(��)
		predictParams.DrawDebugTime = 15.0f;     //����� ���� �������� �ð� (��)
		predictParams.DrawDebugType = EDrawDebugTrace::Type::ForDuration;  // DrawDebugTime �� �����ϸ� EDrawDebugTrace::Type::ForDuration �ʿ�.
		predictParams.OverrideGravityZ = GetWorld()->GetGravityZ();
		FPredictProjectilePathResult result;
		UGameplayStatics::PredictProjectilePath(this, predictParams, result);

		CharacterMovement->AddImpulse(outVelocity); // objectToSend�� �߻�ü
	}
}


