   // Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Game/ACFPlayerController.h"
#include "Actors/ACFCharacter.h"
#include "Components/ACFInteractionComponent.h"
#include "ATSTargetingComponent.h"
#include "CCMPlayerCameraManager.h"
#include <TimerManager.h>
#include <Components/ActorComponent.h>
#include "Components/ACFLocomotionComponent.h"
#include "AI/Components/ACFCompanionGroupAIComponent.h"
#include <Net/UnrealNetwork.h>




AACFPlayerController::AACFPlayerController()
{
}

void AACFPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AACFPlayerController, PossessedCharacter);

}

void AACFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CompanionsComponent = FindComponentByClass<UACFCompanionGroupAIComponent>();

}


void AACFPlayerController::SwitchToNearestCompanion(float blendTime /*= 0.5f */)
{
	if (!CompanionsComponent || !PossessedCharacter)
		return ;

	class AACFCharacter* mCompanion = CompanionsComponent->GetAgentNearestTo(PossessedCharacter->GetActorLocation());

	if (!mCompanion)
		return ;

	SwitchPossessionToCharacer(mCompanion, blendTime);
}



void AACFPlayerController::TriggerAction(const FGameplayTag& action, EActionPriority priority /*= EActionPriority::ELow*/)
{
	if (PossessedCharacter)
		PossessedCharacter->TriggerAction(action, priority);
}

void AACFPlayerController::SwitchPossessionToCharacer_Implementation(class AACFCharacter* inCharacter, float blendTime /*= 0.5f */)
{
	if (!CompanionsComponent || !PossessedCharacter)
		return;

	AACFCharacter* oldPossessedChar = PossessedCharacter;
	Internal_SwitchPossessionTo(inCharacter);
	SetViewTarget(oldPossessedChar);
	SetViewTargetWithBlend(PossessedCharacter, blendTime);

}

bool AACFPlayerController::SwitchPossessionToCharacer_Validate(class AACFCharacter* inCharacter, float blendTime /*= 0.5f */)
{
	return true;
}




void AACFPlayerController::OnActorLoaded_Implementation()
{
	AACFCharacter* currentPawn = Cast<AACFCharacter>(GetPawn());
	if (PossessedCharacter != currentPawn) {
		SwitchPossessionToCharacer(PossessedCharacter);
	}
	if (CompanionsComponent)
		CompanionsComponent->InitAgents();
}

void AACFPlayerController::OnActorSaved_Implementation()
{

}

void AACFPlayerController::Internal_SwitchPossessionTo(AACFCharacter* inCharacter)
{
	CompanionsComponent->RemoveAgentFromGroup(inCharacter);
	inCharacter->GetController()->Destroy(true);
	AACFCharacter* oldPossessedChar = Cast<AACFCharacter>(GetPawn());

	Possess(inCharacter);	
	if (oldPossessedChar)
	{
		oldPossessedChar->SpawnDefaultController();
		CompanionsComponent->AddExistingCharacterToGroup(oldPossessedChar);
	}

}

void AACFPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PossessedCharacter = Cast<AACFCharacter>(aPawn);

	if (PossessedCharacter)
	{
		PossessedCharacter->AssignTeam(CombatTeam);
		EnableCharacterComponents(true);
	}

// 	ACCMPlayerCameraManager* ccmCamera = Cast< ACCMPlayerCameraManager>(PlayerCameraManager);
// 	if(ccmCamera)
// 		ccmCamera->UpdateCameraReferences();
	OnPossessedCharacterChanged.Broadcast(PossessedCharacter);
}

void AACFPlayerController::EnableCharacterComponents(bool bEnabled)
{

	UACFInteractionComponent* interComponent = PossessedCharacter->FindComponentByClass<UACFInteractionComponent>();

	if (interComponent)
	{
		if (bEnabled)
			interComponent->RegisterComponent();
		else
			interComponent->UnregisterComponent();
	}
}

void AACFPlayerController::OnUnPossess()
{
	if (PossessedCharacter)
	{
		EnableCharacterComponents(false);
		PossessedCharacter = nullptr;
	}

	Super::OnUnPossess();
}

// 
// UUserWidget* AACFPlayerController::CreateAndShowWidget(TSubclassOf<UUserWidget> widgetClass, uint8 priority /*= 1*/)
// {  
// 	UWorld* world = GetWorld();
// 	if(world)
// 	{
// 		UUserWidget* widget = UWidgetBlueprintLibrary::Create(world, widgetClass, this);
// 		if (widget)
// 		{
// 			widget->AddToViewport(priority);
// 			return widget;
// 		}
// 
// 	}
// 
// 	return nullptr;
// }
// 
// 
