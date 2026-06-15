#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // Estructura necesaria para Enhanced Input
#include "SBCharacterExample.generated.h"

UCLASS()
class SANDBOXPROJECT_API ASBCharacterExample : public ACharacter
{
	GENERATED_BODY()

public:
	ASBCharacterExample();

protected:
	virtual void BeginPlay() override;

	// --- ENHANCED INPUT SYSTEM ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	// Funciones de movimiento
	void Move(const FInputActionValue& Value);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	float InteractionDistance = 1000.0f;

	UFUNCTION(BlueprintPure)
	AActor* GetActorInFrontOfPlayer();

	UFUNCTION(BlueprintCallable)
	void Interact();
};
