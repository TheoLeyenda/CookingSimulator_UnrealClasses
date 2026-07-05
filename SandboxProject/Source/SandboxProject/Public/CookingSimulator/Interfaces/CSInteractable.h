#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CSInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UCSInteractable : public UInterface
{
	GENERATED_BODY()
};

class SANDBOXPROJECT_API ICSInteractable
{
	GENERATED_BODY()
public:
	virtual bool TryGrab(AActor* Interactor) { return true; }
	virtual void GrabAndDrop(AActor* Interactor){}
	virtual void Interact(AActor* Interactor){}
	virtual void StopInteraction(AActor* Interactor){}
};
