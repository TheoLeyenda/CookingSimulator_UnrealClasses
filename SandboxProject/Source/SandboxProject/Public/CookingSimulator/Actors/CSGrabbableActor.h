#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Interfaces/CSInteractable.h"
#include "GameFramework/Actor.h"
#include "CSGrabbableActor.generated.h"

class ACSCharacter;
class USphereComponent;

UCLASS()
class SANDBOXPROJECT_API ACSGrabbableActor : public AActor, public ICSInteractable
{
	GENERATED_BODY()
	
public:	
	ACSGrabbableActor();
	
	UPROPERTY(EditDefaultsOnly, Category= "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category= "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	virtual void Interact(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable)
	void Drop();
protected:
	UFUNCTION(BlueprintCallable)
	void Grab(ACSCharacter* Character);
};
