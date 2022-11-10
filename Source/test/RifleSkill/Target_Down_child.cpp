// Fill out your copyright notice in the Description page of Project Settings.


#include "Target_Down_child.h"
#include "particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "../AI_Monster/AI_Character.h"
ATarget_Down_child::ATarget_Down_child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
    Particle->SetupAttachment(Root);
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	Sphere->SetCollisionProfileName("BlockAllDynamic");
}

void ATarget_Down_child::BeginPlay()
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
	Sphere->OnComponentHit.AddDynamic(this, &ATarget_Down_child::OnHit);
}
void ATarget_Down_child::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuluse, const FHitResult& Hit)
{
	FDamageEvent e;
	if (Cast<AAI_Character>(OtherActor))
	{
		OtherActor->TakeDamage(20.0f, e, GetWorld()->GetFirstPlayerController(), this);
	}
}
