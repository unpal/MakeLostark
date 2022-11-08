
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
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Catastrophe_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Catastrophe_End_Montage;
	void On_Focused_Shot();
	void On_Perfect_Shot();
	void End_Perfect_Shot();
	void On_Target_Down();
	void On_Catastrophe();
	UFUNCTION(BlueprintCallable)
	void Begin_Target_Down();
	UFUNCTION(BlueprintCallable)
		void Begin_Catastrophe();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Perfect_Shot_Casting;
	UPROPERTY(EditAnywhere)
		FTimerHandle Perfect_Shot_TimerHandle;
	UPROPERTY(EditAnywhere)
		FTimerHandle Catastrophe_TimerHandle;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATarget_Down> Target_Down_Class;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACatastrophe> Catastrophe_Class;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACatastrophe_Boom> Catastrophe_Boom_Class;
	UPROPERTY(EditAnywhere)
		ACatastrophe_Boom* Catastrophe_Boom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Catastrophe_Casting;
private:
	class AtestCharacter* Owner;
	class AtestPlayerController* PlayerContorller;

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AT02_Grenade_Montage;
	void On_AT02_Grenade();
	UFUNCTION(BlueprintCallable)
	void Begin_AT02_Grenade();
	UPROPERTY(EditAnywhere)
		class AAT02_Grenade_Boom* AT02_Grenade_Boom;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AAT02_Grenade_Boom> AAT02_Grenade_Boom_Class;
public:
	void On_Shotgun_Rapid_Fire();
	void Begin_Shotgun_Rapid_Fire();
	void On_Last_Request_Fire();
	UFUNCTION(BlueprintCallable)
	void Begin_Last_Request_Fire();
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ALast_Request> Last_Request_Class;
	UPROPERTY(EditAnywhere)
		class ALast_Request* Last_Request;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Shotgun_Rapid_Fire_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Last_Request_Montage;
};
