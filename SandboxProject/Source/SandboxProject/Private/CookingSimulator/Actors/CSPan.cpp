#include "CookingSimulator/Actors/CSPan.h"

#include "CookingSimulator/Actors/CSFoodItem.h"

void ACSPan::OnCooked()
{
	for (auto Element : GetFoodItems())
	{
		Element->SetState(ECSFoodItemState::Fried);
	}
}
