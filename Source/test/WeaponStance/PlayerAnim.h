#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UCLASS()
class TEST_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool HandgunStanceAnim; // 핸드건 스탠스인지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool ShotgunStanceAnim; // 샷건   스탠스인지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool RifleStanceAnim;   // 라이플 스탠스인지

private:
	class ACharacter* Owner;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DelatSeconds) override;
};
