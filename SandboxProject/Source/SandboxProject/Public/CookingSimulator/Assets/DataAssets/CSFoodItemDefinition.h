#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CSFoodItemDefinition.generated.h"

UCLASS()
class SANDBOXPROJECT_API UCSFoodItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TObjectPtr<UStaticMesh> DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UStaticMesh> HalfSlicedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UStaticMesh> SlicedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UStaticMesh> OnPlateMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UTexture> Icon;
};
