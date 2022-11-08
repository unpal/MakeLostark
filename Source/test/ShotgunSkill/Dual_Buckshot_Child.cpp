// Fill out your copyright notice in the Description page of Project Settings.


#include "Dual_Buckshot_Child.h"
#include "particles/ParticleSystemComponent.h"

ADual_Buckshot_Child::ADual_Buckshot_Child()
{
    Root = CreateDefaultSubobject<USceneComponent>("Root");
    Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
    Particle->SetupAttachment(Root);
}

void ADual_Buckshot_Child::BeginPlay()
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
}
