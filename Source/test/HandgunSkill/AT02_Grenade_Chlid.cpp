// Fill out your copyright notice in the Description page of Project Settings.


#include "AT02_Grenade_Chlid.h"
#include "particles/ParticleSystemComponent.h"
AAT02_Grenade_Chlid::AAT02_Grenade_Chlid()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Root);
}

void AAT02_Grenade_Chlid::BeginPlay()
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