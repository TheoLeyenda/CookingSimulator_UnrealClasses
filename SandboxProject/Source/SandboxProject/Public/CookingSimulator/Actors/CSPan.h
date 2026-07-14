#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSCookware.h"
#include "CSPan.generated.h"

UCLASS()
class SANDBOXPROJECT_API ACSPan : public ACSCookware
{
	GENERATED_BODY()

protected:
	virtual void OnCooked() override;
};
