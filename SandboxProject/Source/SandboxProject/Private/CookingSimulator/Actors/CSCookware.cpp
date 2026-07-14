#include "CookingSimulator/Actors/CSCookware.h"

void ACSCookware::Cook(bool bEnable)
{
	bIsCooking = bEnable;

	if(bIsCooking && GetFoodItems().Num() > 0)
	{
		UpdateCookingProgress();
	}
}

void ACSCookware::OnCooked()
{
		
}

void ACSCookware::UpdateCookingProgress()
{
	CookingScore++;
	UE_LOG(LogTemp, Warning, TEXT("*** CookingScore: %d"), CookingScore);

	if(CookingScore >= CookingTargetScorePerItem * GetFoodItems().Num())
	{
		bIsCooking = false;
		OnCooked();
	}
	
	if(bIsCooking)
	{
		SendUpdateCookingProgressTimer();
	}
}

void ACSCookware::SendUpdateCookingProgressTimer()
{
	if(const auto* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
		   UpdateCookingProgressHandle,
		   this,
		   &ACSCookware::UpdateCookingProgress,
		   UpdateCookingProgressRate,
		   false
	   );
	}
}

