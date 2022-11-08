// Fill out your copyright notice in the Description page of Project Settings.


#include "Target_Down_child.h"
#include "particles/ParticleSystemComponent.h"
ATarget_Down_child::ATarget_Down_child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
    Particle->SetupAttachment(Root);
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

}
