

#include "Sharpshooter.h"
#include "GameFrameWork/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
ASharpshooter::ASharpshooter()
{

}

void ASharpshooter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASharpshooter::ActionPlayEffect(UWorld* Inworld, ACharacter* InOwner)
{
	if (!ActionEffect) return;

	FTransform transform = ActionEffectTransform;

	FVector ownerLocation = InOwner->GetActorLocation();
	ownerLocation += InOwner->GetActorRotation().RotateVector(transform.GetLocation());
	transform.SetLocation(ownerLocation);

	FRotator rotation = InOwner->GetActorRotation();
	rotation += FRotator(transform.GetRotation());
	transform.SetRotation(FQuat(rotation));

	UParticleSystem* particle = Cast<UParticleSystem>(ActionEffect);
	UNiagaraSystem* niagara = Cast<UNiagaraSystem>(ActionEffect);

	if (particle)
		UGameplayStatics::SpawnEmitterAtLocation(Inworld, particle, transform);
	if (niagara)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			Inworld,
			niagara,
			transform.GetLocation(),
			FRotator(transform.GetRotation()),
			transform.GetScale3D());
}

void ASharpshooter::ActionPlayEffect(USkeletalMeshComponent* mesh, FName InSocketName)
{
	if (!ActionEffect) return;

	if (!mesh) return;

	AActor* owner = mesh->GetOwner();
	UWorld* world = owner->GetWorld();

	UParticleSystem* particle = Cast<UParticleSystem>(ActionEffect);
	UNiagaraSystem* niagara = Cast<UNiagaraSystem>(ActionEffect);

	if (particle)
		UGameplayStatics::SpawnEmitterAttached(
			particle,
			mesh,
			InSocketName,
			ActionEffectTransform.GetLocation(),
			FRotator(ActionEffectTransform.GetRotation()),
			ActionEffectTransform.GetScale3D());

	if (niagara)
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			niagara,
			mesh,
			InSocketName,
			ActionEffectTransform.GetLocation(),
			FRotator(ActionEffectTransform.GetRotation()),
			ActionEffectTransform.GetScale3D(),
			EAttachLocation::KeepRelativeOffset,
			true,
			ENCPoolMethod::None);
}

void ASharpshooter::HitPlayEffect(UWorld* Inworld, ACharacter* InOwner)
{
	if (!HitEffect) return;

	FTransform transform = HitEffectTransform;

	FVector ownerLocation = InOwner->GetActorLocation();
	ownerLocation += InOwner->GetActorRotation().RotateVector(transform.GetLocation());
	transform.SetLocation(ownerLocation);

	FRotator rotation = InOwner->GetActorRotation();
	rotation += FRotator(transform.GetRotation());
	transform.SetRotation(FQuat(rotation));

	UParticleSystem* particle = Cast<UParticleSystem>(HitEffect);
	UNiagaraSystem* niagara = Cast<UNiagaraSystem>(HitEffect);

	if (particle)
		UGameplayStatics::SpawnEmitterAtLocation(Inworld, particle, transform);
	if (niagara)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			Inworld,
			niagara,
			transform.GetLocation(),
			FRotator(transform.GetRotation()),
			transform.GetScale3D());
}

void ASharpshooter::HitPlayEffect(USkeletalMeshComponent* mesh, FName InSocketName)
{
	if (!HitEffect) return;

	if (!mesh) return;

	AActor* owner = mesh->GetOwner();
	UWorld* world = owner->GetWorld();

	UParticleSystem* particle = Cast<UParticleSystem>(HitEffect);
	UNiagaraSystem* niagara = Cast<UNiagaraSystem>(HitEffect);

	if (particle)
		UGameplayStatics::SpawnEmitterAttached(
			particle,
			mesh,
			InSocketName,
			HitEffectTransform.GetLocation(),
			FRotator(HitEffectTransform.GetRotation()),
			HitEffectTransform.GetScale3D());

	if (niagara)
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			niagara,
			mesh,
			InSocketName,
			HitEffectTransform.GetLocation(),
			FRotator(HitEffectTransform.GetRotation()),
			HitEffectTransform.GetScale3D(),
			EAttachLocation::KeepRelativeOffset,
			true,
			ENCPoolMethod::None);
}

