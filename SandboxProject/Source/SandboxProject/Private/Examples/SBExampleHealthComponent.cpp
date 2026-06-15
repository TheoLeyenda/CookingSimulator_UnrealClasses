#include "Examples/SBExampleHealthComponent.h"

USBExampleHealthComponent::USBExampleHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void USBExampleHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void USBExampleHealthComponent::TakeDamage(float Amount)
{
	if (Amount <= 0.0f || CurrentHealth <= 0.0f) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("Vida actual del dueño: %f"), CurrentHealth);

	if (CurrentHealth <= 0.0f)
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			UE_LOG(LogTemp, Error, TEXT("%s ha muerto."), *Owner->GetName());
		}
	}
}

