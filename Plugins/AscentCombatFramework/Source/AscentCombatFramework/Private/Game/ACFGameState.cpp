// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Game/ACFGameState.h"
#include "Components/ACFEffectsDispatcherComponent.h"

void AACFGameState::UpdateBattleState()
{
	EBattleState state = InBattleAIs.Num() > 0 ? EBattleState::EBattle : EBattleState::EExploration;
	if (gameState != state)
	{
		gameState = state;
		OnBattleStateChanged.Broadcast(gameState);
	}
}

AACFGameState::AACFGameState()
{
	EffectsComp = CreateDefaultSubobject<UACFEffectsDispatcherComponent>(TEXT("Effects Component"));
}

void AACFGameState::AddAIToBattle(class AACFAIController* contr)
{
	if (!contr)
		return;

	InBattleAIs.Add(contr);
	UpdateBattleState();
}

void AACFGameState::RemoveAIFromBattle(class AACFAIController* contr)
{
	if (contr && InBattleAIs.Contains(contr))
	{
		InBattleAIs.Remove(contr);
		UpdateBattleState();
	}
}
