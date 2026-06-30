#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CSCookwareInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCSCookwareInterface : public UInterface
{
	GENERATED_BODY()
};

class SANDBOXPROJECT_API ICSCookwareInterface
{
	GENERATED_BODY()

public:
	virtual void Cook(bool bEnable){}
};
