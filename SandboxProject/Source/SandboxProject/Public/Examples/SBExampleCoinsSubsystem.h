#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SBExampleCoinsSubsystem.generated.h"

UCLASS()
class SANDBOXPROJECT_API USBExampleCoinsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category= "Economy")
	void ChangeCoinsAccount(const int32 Account) { Coins += Account; }

	UFUNCTION(BlueprintPure, Category= "Economy")
	int32 GetCoins() const { return Coins; }
private:
	int32 Coins;
};