// Fill out your copyright notice in the Description page of Project Settings.


#include "Equilibrium_Child.h"
#include "Particles/ParticleSystemComponent.h"

AEquilibrium_Child::AEquilibrium_Child()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
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
}

void AEquilibrium_Child::DestroyParticle()
{
	Destroy();
}

