#include "CookingSimulator/Controllers/CSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

void ACSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(auto* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		CameraActor = World->SpawnActor<ACameraActor>(CameraActorClass, CameraActorTransform, SpawnParams);
		if(CameraActor)
		{
			CameraActor->GetCameraComponent()->SetConstraintAspectRatio(false);
			SetViewTargetWithBlend(CameraActor.Get());
		}
		
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(DefaultInputMappingContext.Get(), 0);
			}
		}
	}
}
