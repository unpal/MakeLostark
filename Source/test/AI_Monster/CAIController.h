#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Attack, Hitted, Approach, Max,
};

UCLASS()
class TEST_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

public:
	ACAIController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
		void OnPerceptiongUpdated(const TArray<AActor*>& UpdateActors);

public:
	void ChangeType(EBehaviorType InType);

	class AtestCharacter* GetTargetPlayer();

private:
	class AAI_Character* Owner;
	class UAISenseConfig_Sight* SightSense;
};
