// Copyright Epic Games, Inc. All Rights Reserved.

#include "testCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "DashNotifyState/DashWidget.h"
#include "testPlayerController.h"
#include "WeaponStance/Handgun_Stance.h"
#include "WeaponStance/Shotgun_Stance.h"
#include "WeaponStance/Rifle_Stance.h"


AtestCharacter::AtestCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	ConstructorHelpers::FClassFinder<UDashWidget> widgetclass(L"WidgetBlueprint'/Game/Skill/Widget/BP_DashWidget.BP_DashWidget_C'");
	if (widgetclass.Succeeded()) DashCoolDownClass = widgetclass.Class;
	HandgunStance = true; // 핸드건 스탠스인지
	ShotgunStance = false; // 샷건   스탠스인지
	RifleStance   = false;   // 라이플 스탠스인지

	ConstructorHelpers::FClassFinder<UAnimInstance> anim(L"AnimBlueprint'/Game/Stance/StanceAnim.StanceAnim_C'");
	if (anim.Succeeded()) GetMesh()->SetAnimClass(anim.Class);
}

void AtestCharacter::BeginPlay()
{
	Super::BeginPlay();
	DashCoolDown = CreateWidget<UDashWidget, AtestPlayerController>(GetController<AtestPlayerController>(), DashCoolDownClass);
	DashCoolDown->AddToViewport();
	Handgun_R = AHandgun_Stance::Spawn(GetWorld(), this);
	Handgun_R->Handgun_Stance_R();
	Handgun_L = AHandgun_Stance::Spawn(GetWorld(), this);
	Handgun_L->Handgun_Stance_L();
}

void AtestCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AtestCharacter::VisibleDashCoolDown()
{
	DashCoolDown->DashCooldown();
}

void AtestCharacter::Change_Stance_Left()
{
	if(HandgunStance)
	{
		HandgunStance = false;
		ShotgunStance = true;
		RifleStance = false;
		Shotgun = AShotgun_Stance::Spawn(GetWorld(), this);
		Shotgun->Shotgun_Stance();
		Handgun_R->Destroy_Stance();
		Handgun_L->Destroy_Stance();

	}
	else if (ShotgunStance)
	{
		HandgunStance = false;
		ShotgunStance = false;
		RifleStance = true;
		Rifle = ARifle_Stance::Spawn(GetWorld(), this);
		Rifle->Rifle_Stance();
		Shotgun->Destroy_Stance();
	}
	else if (RifleStance)
	{
		HandgunStance = true;
		ShotgunStance = false;
		RifleStance = false;
		Handgun_R = AHandgun_Stance::Spawn(GetWorld(), this);
		Handgun_R->Handgun_Stance_R();
		Handgun_L = AHandgun_Stance::Spawn(GetWorld(), this);
		Handgun_L->Handgun_Stance_L();

		Rifle->Destroy_Stance();
	}
}

void AtestCharacter::Change_Stance_Right()
{
	if (HandgunStance)
	{
		HandgunStance = false;
		ShotgunStance = false;
		RifleStance = true;
		Rifle = ARifle_Stance::Spawn(GetWorld(), this);
		Rifle->Rifle_Stance();
		Handgun_R->Destroy_Stance();
		Handgun_L->Destroy_Stance();

	}
	else if (ShotgunStance)
	{
		HandgunStance = true;
		ShotgunStance = false;
		RifleStance = false;
		Handgun_R = AHandgun_Stance::Spawn(GetWorld(), this);
		Handgun_R->Handgun_Stance_R();
		Handgun_L = AHandgun_Stance::Spawn(GetWorld(), this);
		Handgun_L->Handgun_Stance_L();
		Shotgun->Destroy_Stance();
	}
	else if (RifleStance)
	{
		HandgunStance = false;
		ShotgunStance = true;
		RifleStance = false;
		Shotgun = AShotgun_Stance::Spawn(GetWorld(), this);
		Shotgun->Shotgun_Stance();
		Rifle->Destroy_Stance();
	}
}

void AtestCharacter::General_Attack()
{
	if(HandgunStance)
	Handgun_L->General_Attack();
	if (ShotgunStance)
		Shotgun->General_Attack();
}
