#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SBExampleSpawnManagerSubsystem.generated.h"

UCLASS()
class SANDBOXPROJECT_API USBExampleSpawnManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		EnemiesAliveCount = 0;
	}

	void RegisterEnemyDeath()
	{
		EnemiesAliveCount = FMath::Max(EnemiesAliveCount - 1, 0);
		if(EnemiesAliveCount <= 0)
		{
			StartNewWave();
		}
	}
	void RegisterSpawnEnemy()
	{
		EnemiesAliveCount++;
	}
	
private:
	int32 EnemiesAliveCount = 0;
	void StartNewWave() { /* Logica de spawn aqui*/ }
};
