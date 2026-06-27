#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Interfaces/CSInteractable.h"
#include "GameFramework/Actor.h"
#include "CSGrabbableActor.generated.h"

class UBoxComponent;
class ACSCharacter;

UCLASS()
class SANDBOXPROJECT_API ACSGrabbableActor : public AActor, public ICSInteractable
{
	GENERATED_BODY()
	
public:	
	ACSGrabbableActor();
	
	UPROPERTY(EditDefaultsOnly, Category= "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category= "Components")
	TObjectPtr<UBoxComponent> BoxComponent;

	virtual void GrabAndDrop(AActor* Interactor) override;
	virtual bool CanBeGrabbed(ACSCharacter* Character) const;

	void DisablePhysics();
	void EnablePhysics();
	
	UFUNCTION(BlueprintCallable)
	void Drop();

	UFUNCTION(BlueprintCallable)
	virtual void Grab(ACSCharacter* Character);
};
