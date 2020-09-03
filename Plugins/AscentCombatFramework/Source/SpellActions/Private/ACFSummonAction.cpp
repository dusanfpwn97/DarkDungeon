// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFSummonAction.h"
#include <NavigationSystem/Public/NavigationSystem.h>
#include <Engine/World.h>
#include "Game/ACFData.h"
#include "Game/ACFFunctionLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include "Actions/ACFBaseAction.h"
#include <GameFramework/Actor.h>
#include "Actors/ACFCharacter.h"
#include "Components/ACFDamageHandlerComponent.h"
#include "AI/Components/ACFCompanionGroupAIComponent.h"
#include <TimerManager.h>
#include <Engine/EngineTypes.h>

void UACFSummonAction::OnNotablePointReached_Implementation()
{
	Super::OnNotablePointReached_Implementation();
	//resetting to avoid having 
	if (currentCompIndex >= 250) {
		currentCompIndex = 0;
	}   

	FVector outLoc;
	if (CharacterOwner &&
	UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, CharacterOwner->GetActorLocation(), outLoc, SpawnRadius))
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		if (world && CompanionToSummonClass)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(outLoc, CharacterOwner->GetActorLocation());
			rot.Pitch = 0.f;
			AACFCharacter* comp = world->SpawnActor<AACFCharacter>(CompanionToSummonClass, outLoc, rot, SpawnParams);
			
			if (comp) {
				Companions.Add(comp);
				UACFFunctionLibrary::PlayActionEffect(ActionConfig.ActionEffects, comp, this);
				AController* controller = CharacterOwner->GetController();
				if (controller) {
					UACFCompanionGroupAIComponent* groupComp = controller->FindComponentByClass<UACFCompanionGroupAIComponent>();
					if (groupComp) {
						groupComp->AddExistingCharacterToGroup(comp);
					}
					else {
						UE_LOG(LogTemp, Error, TEXT("No CompanionsComp on Controller!!"));
					}
				}
	
				UACFDamageHandlerComponent* damageHandler = comp->GetDamageHandlerComponent();
				damageHandler->OnOwnerDeath.AddDynamic(this, &UACFSummonAction::OnCompanionDeath);
				if (bAutoKillAfterSeconds) {
					FTimerDelegate TimerDel;
					FTimerHandle TimerHandle;
					TimerDel.BindUFunction(this, FName("KillCompanion"), comp);
					world->GetTimerManager().SetTimer(TimerHandle, TimerDel, AutoKillTime, false);
				}
			}
		}
	}
}

bool UACFSummonAction::CanExecuteAction_Implementation(class AACFCharacter* owner)
{
	return Companions.Num() < MaxCompanionNumb;
}

void UACFSummonAction::KillCompanion(class AACFCharacter* comp)
{
	if (Companions.Contains(comp)) {
		 comp->KillCharacter(2.0f);
		 Companions.Remove(comp);
	}
}

void UACFSummonAction::OnCompanionDeath()
{
	TArray<AACFCharacter*> pendingDelete;
	for (const auto comp : Companions) {
		if (comp && comp->IsAlive()) {
			continue;
		}
		pendingDelete.Add(comp);
	}

	for (const auto tobeRem : pendingDelete) {
		Companions.Remove(tobeRem);
	}
}

