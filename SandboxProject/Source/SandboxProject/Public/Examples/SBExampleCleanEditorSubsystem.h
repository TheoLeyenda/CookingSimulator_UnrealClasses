#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "SBExampleCleanEditorSubsystem.generated.h"

UCLASS()
class SANDBOXPROJECT_API USBExampleCleanEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= "Development Tools")
	void DeleteUnreferencedAssets()
	{
		//Codigo para buscar assets no referenciados en el editor y borrarlos.
	}
};
