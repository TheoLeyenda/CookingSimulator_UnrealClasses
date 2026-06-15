#pragma once

#include "CoreMinimal.h"
#include "SBInteractableInterfaceExample.h"
#include "GameFramework/Actor.h"
#include "SBDoorExample.generated.h"

UCLASS()
class SANDBOXPROJECT_API ASBDoorExample : public AActor, public ISBInteractableInterfaceExample
{
	GENERATED_BODY()
	
public:	
	ASBDoorExample();

protected:
	virtual void OnInteract(AActor* Interactor) override;
};
