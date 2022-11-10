// Fill out your copyright notice in the Description page of Project Settings.


#include "Equilibrium_Child.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "../AI_Monster/AI_Character.h"

AEquilibrium_Child::AEquilibrium_Child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	Sphere->SetCollisionProfileName("BlockAllDynamic");
}

void AEquilibrium_Child::BeginPlay()
{
	Super::BeginPlay();
	FTransform transform = ActionEffectTransform;
	FVector location = GetActorLocation();
	location += GetActorRotation().RotateVector(transform.GetLocation());
	transform.SetLocation(location);
	SetActorLocation(location);

	FRotator rotation = GetActorRotation();
	rotation += FRotator(transform.GetRotation());
	transform.SetRotation(FQuat(rotation));
	SetActorRotation(FQuat(rotation));
	SetLifeSpan(0.3);
	Sphere->OnComponentHit.AddDynamic(this, &AEquilibrium_Child::OnHit);
}

void AEquilibrium_Child::DestroyParticle()
{
	Destroy();
}

void AEquilibrium_Child::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	FDamageEvent e;
	if (Cast<AAI_Character>(OtherActor))
	{
		OtherActor->TakeDamage(20.0f, e, GetWorld()->GetFirstPlayerController(), this);
	}
}
