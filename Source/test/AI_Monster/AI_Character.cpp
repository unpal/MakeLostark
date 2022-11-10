#include "AI_Character.h"
#include "Components/WidgetComponent.h"
#include "AIWidget.h"
#include "AIWeapon_Bow.h"

AAI_Character::AAI_Character()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Skeleton_archer/mesh/SK_Skeleton_archer.SK_Skeleton_archer'");
	GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UAnimInstance> anim(L"AnimBlueprint'/Game/Monster/ABP_Archer.ABP_Archer_C'");
	GetMesh()->SetAnimClass(anim.Class);

	ConstructorHelpers::FClassFinder<UAIWidget> widget(L"WidgetBlueprint'/Game/Monster/BP_AIWidget.BP_AIWidget_C'");
	AIWidget = CreateDefaultSubobject<UWidgetComponent>("AIWigdet");
	AIWidget->SetupAttachment(GetMesh());
	AIWidget->SetWidgetClass(widget.Class);
	AIWidget->SetRelativeLocation(FVector(0, 0, 200));
	AIWidget->SetDrawSize(FVector2D(200, 50));
	AIWidget->SetWidgetSpace(EWidgetSpace::Screen);

}

float AAI_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventIstigator, AActor* DamgeCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventIstigator, DamgeCauser);

	bHitted = true;

	Hp -= DamageAmount;

	Cast<UAIWidget>(AIWidget->GetUserWidgetObject())->UpdateHealth(Hp, MaxHp);

	Hitted();

	return DamageAmount;
}

void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
	Bow = AAIWeapon_Bow::Spawn(GetWorld(), this);
	AIWidget->InitWidget();

	Hp = MaxHp;

	Cast<UAIWidget>(AIWidget->GetUserWidgetObject())->UpdateHealth(Hp, MaxHp);
	Cast<UAIWidget>(AIWidget->GetUserWidgetObject())->UpdateCharacterName(Name);
}

void AAI_Character::Attack()
{
	bAttack = true;
	PlayAnimMontage(Montages[0]);

}

void AAI_Character::Hitted()
{
	if (Hp <= 0)
	{
		PlayAnimMontage(Montages[1]);
		return;
	}
	PlayAnimMontage(Montages[2]);
}

void AAI_Character::ShootArrow()
{
	if (Bow)
		Bow->Begin_Fire();
}



