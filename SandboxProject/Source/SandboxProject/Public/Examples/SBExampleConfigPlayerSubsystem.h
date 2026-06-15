#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "SBExampleConfigPlayerSubsystem.generated.h"

UCLASS()
class SANDBOXPROJECT_API USBExampleConfigPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= "Settings")
	void SetMouseSensibility(float NewSensibility)
	{
		MouseSensibility = NewSensibility;
	}

	UFUNCTION(BlueprintPure, Category= "Settings")
	float GetMouseSensibility() { return MouseSensibility; }
	
private:
	float MouseSensibility = 1.0;
};
