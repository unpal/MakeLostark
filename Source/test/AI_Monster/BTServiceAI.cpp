#include "BTServiceAI.h"
#include "test/testCharacter.h"
#include "AI_Character.h"
#include "CAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTServiceAI::UBTServiceAI()
{ NodeName = "AI"; }

void UBTServiceAI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    AAI_Character* ai = Cast<AAI_Character>(controller->GetPawn());

    if (ai->GetIsHitted())
    {
        controller->ChangeType(EBehaviorType::Hitted);
        return;
    }

    AtestCharacter* player = controller->GetTargetPlayer();

    if (!player)
    {
        controller->ChangeType(EBehaviorType::Wait);
        return;
    }

    float distance = ai->GetDistanceTo(player);

    if (distance < AttackRange)
    {
        FRotator rot = UKismetMathLibrary::FindLookAtRotation(ai->GetActorLocation(), player->GetActorLocation());
        ai->SetActorRotation(rot);
        controller->ChangeType(EBehaviorType::Attack);
        return;
    }

    controller->ChangeType(EBehaviorType::Approach);
}
