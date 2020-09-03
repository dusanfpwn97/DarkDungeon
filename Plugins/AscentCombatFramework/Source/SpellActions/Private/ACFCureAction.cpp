// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFCureAction.h"
#include "Actions/ACFBaseAction.h"
#include "Game/ACFFunctionLibrary.h"
#include "Game/ACFData.h"
#include "ARSStatisticsComponent.h"

void UACFCureAction::OnNotablePointReached_Implementation()
{
	Super::OnNotablePointReached_Implementation();
	if (CharacterOwner && CharacterOwner->GetStatisticsComponent()) {
		CharacterOwner->GetStatisticsComponent()->ModifyStat(StatModifier);
		UACFFunctionLibrary::PlayActionEffect(ActionConfig.ActionEffects, CharacterOwner, this);
	}
}
