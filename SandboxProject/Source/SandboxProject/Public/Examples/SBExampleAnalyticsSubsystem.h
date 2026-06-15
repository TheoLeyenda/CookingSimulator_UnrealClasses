#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "SBExampleAnalyticsSubsystem.generated.h"

UCLASS()
class SANDBOXPROJECT_API USBExampleAnalyticsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	void SendReportToServer(FString Event)
	{
		//Codigo para conectar con un servidor HTTP externo y mandar datos de analiticas.
	}
};
