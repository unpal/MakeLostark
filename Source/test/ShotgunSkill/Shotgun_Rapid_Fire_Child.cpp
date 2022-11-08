// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun_Rapid_Fire_Child.h"
#include "particles/ParticleSystemComponent.h"

AShotgun_Rapid_Fire_Child::AShotgun_Rapid_Fire_Child()
{
    Root = CreateDefaultSubobject<USceneComponent>("Root");
    Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
    Particle->SetupAttachment(Root);
}

void AShotgun_Rapid_Fire_Child::BeginPlay()
{
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
