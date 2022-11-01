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
	bool HandgunStanceAnim; // �ڵ�� ���Ľ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool ShotgunStanceAnim; // ����   ���Ľ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool RifleStanceAnim;   // ������ ���Ľ�����

private:
	class ACharacter* Owner;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DelatSeconds) override;
};
