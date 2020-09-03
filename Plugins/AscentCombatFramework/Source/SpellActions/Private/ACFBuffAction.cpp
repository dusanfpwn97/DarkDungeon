// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFBuffAction.h"
#include "Actions/ACFBaseAction.h"
#include "Game/ACFFunctionLibrary.h"

void UACFBuffAction::OnNotablePointReached_Implementation()
{
	Super::OnNotablePointReached_Implementation();
	if (CharacterOwner && CharacterOwner->GetStatisticsComponent()) {
		CharacterOwner->GetStatisticsComponent()->AddTimedAttributeSetModifier(BuffToApply.modifier, BuffToApply.duration);
		UACFFunctionLibrary::PlayActionEffectLocally(ActionConfig.ActionEffects, CharacterOwner, this);
	}    	
}
