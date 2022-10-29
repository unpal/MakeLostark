#include "Weapon_Manage.h"
#include "Handgun_Stance.h"
#include "Shotgun_Stance.h"
#include "Rifle_Stance.h"



AWeapon_Manage::AWeapon_Manage()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeapon_Manage::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon_Manage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Manage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void AWeapon_Manage::AfterStance(float axis)
{
}

void AWeapon_Manage::BeforeStance(float axis)
{
}

