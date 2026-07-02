#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSTable.h"
#include "CSStove.generated.h"

UCLASS()
class SANDBOXPROJECT_API ACSStove : public ACSTable
{
	GENERATED_BODY()

public:
	virtual void Grab(ACSCharacter* Character) override;
	virtual void Place(ACSCharacter* Character) override;
};
