
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
		class ATarget_Down* Target_Down;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Focused_Shot_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Perfect_Shot_Start_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Perfect_Shot_End_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Target_Down_Montage;
	void On_Focused_Shot();
	void On_Perfect_Shot();
	void End_Perfect_Shot();
	void On_Target_Down();
	UFUNCTION(BlueprintCallable)
	void Begin_Target_Down();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Perfect_Shot_Casting;
	UPROPERTY(EditAnywhere)
		FTimerHandle Perfect_Shot_TimerHandle;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATarget_Down> Target_Down_Class;
private:
	class AtestCharacter* Owner;
	class AtestPlayerController* PlayerContorller;

		
};
