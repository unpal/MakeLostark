// Fill out your copyright notice in the Description page of Project Settings.


#include "Last_Request_Child.h"
#include "particles/ParticleSystemComponent.h"

ALast_Request_Child::ALast_Request_Child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
}

void ALast_Request_Child::BeginPlay()
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
