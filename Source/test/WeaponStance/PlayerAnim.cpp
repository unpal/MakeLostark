#include "PlayerAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "test/testCharacter.h"

void UPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<ACharacter>(TryGetPawnOwner());
}

void UPlayerAnim::NativeUpdateAnimation(float DelatSeconds)
{
	Super::NativeUpdateAnimation(DelatSeconds);
	if (!Owner) return;
	Speed = Owner->GetVelocity().Size2D();

	AtestCharacter* player = Cast<AtestCharacter>(Owner);
	
	if (player)
	{
		HandgunStanceAnim = player->HandgunStance;
		RifleStanceAnim = player->RifleStance;
		ShotgunStanceAnim = player->ShotgunStance;
	}
}
