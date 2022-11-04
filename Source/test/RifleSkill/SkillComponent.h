
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Focused_Shot_Montage;
	void On_Focused_Shot();
private:
	class ACharacter* Owner;

		
};
