
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sharpshooter.generated.h"

UCLASS()
class TEST_API ASharpshooter : public AActor
{
	GENERATED_BODY()
	
public:	
	ASharpshooter();

protected:
	virtual void BeginPlay() override;


};
