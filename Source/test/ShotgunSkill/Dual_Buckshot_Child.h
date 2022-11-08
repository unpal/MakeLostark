
#pragma once

#include "CoreMinimal.h"
#include "Dual_Buckshot.h"
#include "Dual_Buckshot_Child.generated.h"

UCLASS()
class TEST_API ADual_Buckshot_Child : public ADual_Buckshot
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;


public:
	ADual_Buckshot_Child();

protected:
	virtual void BeginPlay() override;
};
