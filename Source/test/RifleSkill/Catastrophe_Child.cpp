// Fill out your copyright notice in the Description page of Project Settings.


#include "Catastrophe_Child.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "../AI_Monster/AI_Character.h"
ACatastrophe_Child::ACatastrophe_Child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	Sphere->SetCollisionProfileName("BlockAllDynamic");
}

void ACatastrophe_Child::BeginPlay()
{
	Super::BeginPlay();

    SetLifeSpan(3);
    FTransform transform = ActionEffectTransform;
    FVector location = GetActorLocation();
    location += GetActorRotation().RotateVector(transform.GetLocation());
    transform.SetLocation(location);
    SetActorLocation(location);

    FRotator rotation = GetActorRotation();
    rotation += FRotator(transform.GetRotation());
    transform.SetRotation(FQuat(rotation));
    SetActorRotation(FQuat(rotation));
	Sphere->OnComponentHit.AddDynamic(this, &ACatastrophe_Child::OnHit);
}

void ACatastrophe_Child::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	FDamageEvent e;
	if (Cast<AAI_Character>(OtherActor))
	{
		OtherActor->TakeDamage(20.0f, e, GetWorld()->GetFirstPlayerController(), this);
	}
}