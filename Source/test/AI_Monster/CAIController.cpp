#include "CAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "test/testCharacter.h"
#include "AI_Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ACAIController::ACAIController()
{
    Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
    SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

    SightSense->SightRadius = 800;
    SightSense->LoseSightRadius = 1000;
    SightSense->PeripheralVisionAngleDegrees = 45;
    SightSense->SetMaxAge(2);

    SightSense->DetectionByAffiliation.bDetectEnemies = true;
    SightSense->DetectionByAffiliation.bDetectNeutrals = false;
    SightSense->DetectionByAffiliation.bDetectFriendlies = false;

    SightSense->AutoSuccessRangeFromLastSeenLocation = 3;

    Perception->ConfigureSense(*SightSense);
    Perception->SetDominantSense(*SightSense->GetSenseImplementation());
}

void ACAIController::BeginPlay()
{
    Super::BeginPlay();

    Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptiongUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    Owner = Cast<AAI_Character>(InPawn);
    SetGenericTeamId(Owner->GetTeamID());

    UseBlackboard(Owner->GetBehaviorTree()->BlackboardAsset, Blackboard);

    RunBehaviorTree(Owner->GetBehaviorTree());
}

void ACAIController::OnUnPossess()
{
    Super::OnUnPossess();
}

void ACAIController::OnPerceptiongUpdated(const TArray<AActor*>& UpdateActors)
{
    TArray<AActor*> actors;
    Perception->GetCurrentlyPerceivedActors(NULL, actors);

    AtestCharacter* player = nullptr;

    for (AActor* actor : actors)
    {
        player = Cast<AtestCharacter>(actor);
        if (player) break;
    }

    Blackboard->SetValueAsObject("Player", player);
}

void ACAIController::ChangeType(EBehaviorType InType)
{ Blackboard->SetValueAsEnum("Behavior", (uint8)InType); }

AtestCharacter* ACAIController::GetTargetPlayer()
{
    return Cast<AtestCharacter>(Blackboard->GetValueAsObject("Player"));
}
