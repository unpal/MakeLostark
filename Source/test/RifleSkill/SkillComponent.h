
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
	UPROPERTY(VisibleDefaultsOnly)
		class AFocused_Shot* Focused_Shot;
	UPROPERTY(VisibleDefaultsOnly)
		class APerfect_Shot* Perfect_Shot;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Focused_Shot_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Perfect_Shot_Start_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Perfect_Shot_End_Montage;
	void On_Focused_Shot();
	void On_Perfect_Shot();
	void End_Perfect_Shot();
	UPROPERTY(EditAnywhere)
		bool Perfect_Shot_Casting;
	UPROPERTY(EditAnywhere)
		FTimerHandle Perfect_Shot_TimerHandle;
private:
	class ACharacter* Owner;

		
};
