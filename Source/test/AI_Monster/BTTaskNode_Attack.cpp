#include "BTTaskNode_Attack.h"
#include "AI_Character.h"
#include "CAIController.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    AAI_Character* ai = Cast<AAI_Character>(controller->GetPawn());

    ai->Attack();

    TotalTime = 0.0f;
    controller->StopMovement();

    return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTaskNode_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::AbortTask(OwnerComp, NodeMemory);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    AAI_Character* ai = Cast<AAI_Character>(controller->GetPawn());

    ai->EndAttack();

    return EBTNodeResult::Succeeded;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    AAI_Character* ai = Cast<AAI_Character>(controller->GetPawn());

    TotalTime += DeltaSeconds;

    if (!ai->GetIsAttack() && TotalTime > Delay)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
