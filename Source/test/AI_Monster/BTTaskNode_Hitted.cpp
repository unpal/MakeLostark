#include "BTTaskNode_Hitted.h"
#include "AI_Character.h"
#include "CAIController.h"

UBTTaskNode_Hitted::UBTTaskNode_Hitted()
{
    bNotifyTick = true;
    NodeName = "Hitted";
}

EBTNodeResult::Type UBTTaskNode_Hitted::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    AAI_Character* ai = Cast<AAI_Character>(controller->GetPawn());

    controller->StopMovement();

    return EBTNodeResult::InProgress;
}

void UBTTaskNode_Hitted::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    AAI_Character* ai = Cast<AAI_Character>(controller->GetPawn());

    if (!ai->GetIsHitted())
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
