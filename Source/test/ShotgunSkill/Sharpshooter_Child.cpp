// Fill out your copyright notice in the Description page of Project Settings.


#include "Sharpshooter_Child.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "../AI_Monster/AI_Character.h"
ASharpshooter_Child::ASharpshooter_Child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetCollisionProfileName("BlockAllDynamic");
}

void ASharpshooter_Child::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(0.3f);
	FTransform transform = ActionEffectTransform;
	FVector location = GetActorLocation();
	location += GetActorRotation().RotateVector(transform.GetLocation());
	transform.SetLocation(location);
	SetActorLocation(location);

	FRotator rotation = GetActorRotation();
	rotation += FRotator(transform.GetRotation());
	transform.SetRotation(FQuat(rotation));
	SetActorRotation(FQuat(rotation));
	Capsule->OnComponentHit.AddDynamic(this, &ASharpshooter_Child::OnHit);
}

void ASharpshooter_Child::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	FDamageEvent e;
	if (Cast<AAI_Character>(OtherActor))
	{
		OtherActor->TakeDamage(5.0f, e, GetWorld()->GetFirstPlayerController(), this);
	}
}
