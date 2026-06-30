#include "CookingSimulator/Actors/CSCookware.h"

void ACSCookware::Cook(bool bEnable)
{
	bIsCooking = bEnable;

	if(bIsCooking && FoodItems.Num() > 0)
	{
		UpdateCookingProgress();
	}
}

void ACSCookware::UpdateCookingProgress()
{
	CookingScore++;
	UE_LOG(LogTemp, Warning, TEXT("*** CookingScore: %d"), CookingScore);

	if(CookingScore >= CookingTargetScorePerItem * FoodItems.Num())
	{
		bIsCooking = false;
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

