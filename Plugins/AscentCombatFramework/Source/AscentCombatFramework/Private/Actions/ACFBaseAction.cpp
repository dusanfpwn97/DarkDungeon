// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Actions/ACFBaseAction.h"
#include "Actors/ACFCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Animation/ACFAnimInstance.h"
#include "Game/ACFFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "ARSStatisticsComponent.h"
#include "Components/ACFLocomotionComponent.h"
#include "Game/ACFPlayerController.h"
#include "AI/ACFAIController.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include"Game/ACFData.h"
#include <TimerManager.h>





void UACFBaseAction::OnActionStarted_Implementation()
{
	//This comment was added by Mighteemouse because he doesn't want to break anything when he checks it in!

}

void UACFBaseAction::OnActionEnded_Implementation()
{

}

void UACFBaseAction::OnActionTransition_Implementation(class UACFBaseAction* previousState)
{

}

void UACFBaseAction::PlayEffects_Implementation()
{	
	if (ActionConfig.ActionEffects.ActionParticle || ActionConfig.ActionEffects.ActionSound) {
		UACFFunctionLibrary::PlayActionEffectLocally(ActionConfig.ActionEffects, CharacterOwner, this);
	}
}

void UACFBaseAction::OnTick_Implementation(float DeltaTime)
{

}

bool UACFBaseAction::CanExecuteAction_Implementation(class AACFCharacter* owner)
{
	return true;
}

FName UACFBaseAction::GetMontageSectionName_Implementation()
{
	return NAME_None;
}

void UACFBaseAction::OnNotablePointReached_Implementation()
{

}

void UACFBaseAction::OnSubActionStateEntered_Implementation()
{

}

void UACFBaseAction::OnSubActionStateExited_Implementation()
{

}
void UACFBaseAction::HandleMontageStarted(UAnimMontage * _animMontage)
{

	UAnimInstance* _animinst = (CharacterOwner->GetMesh()->GetAnimInstance());
	if (_animinst)
	{		
		_animinst->OnMontageStarted.RemoveDynamic(this, &UACFBaseAction::HandleMontageStarted);
		_animinst->OnMontageBlendingOut.RemoveDynamic(this, &UACFBaseAction::HandleMontageFinished);
		if (_animMontage == animMontage)
		{
			_animinst->OnMontageBlendingOut.AddDynamic(this, &UACFBaseAction::HandleMontageFinished);
		}	

	}
}

void UACFBaseAction::ExecuteAction()
{
	FName Section;
		
	if (ActionConfig.bPlayRandomMontageSection)
	{
		int32 numSections = animMontage->CompositeSections.Num();

		int32 sectionToPlay = FMath::RandHelper(numSections);

		Section = animMontage->GetSectionName(sectionToPlay);
	}
	else
	{
		Section = GetMontageSectionName();
	}

	if (CharacterOwner)
	{
		UAnimInstance* _animinst = (CharacterOwner->GetMesh()->GetAnimInstance());		
		if (_animinst)
		{
			_animinst->OnMontageStarted.AddDynamic(this, &UACFBaseAction::HandleMontageStarted);
			UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();
			if (locComp)
			{
				locComp->SetMontageReprodutionType(ActionConfig.MontageReproductionType);
			}
		
			CharacterOwner->PlayNetworkedMontage(animMontage, GetPlayRate(), Section);
			bIsExecutingAction = true;
		}
	
	}

}

void UACFBaseAction::ExitAction()
{
	if ( ActionsManager)
	{
		ActionsManager->InternalExitAction();
	}
}

float UACFBaseAction::GetPlayRate_Implementation()
{
	return 1.f;
}

void UACFBaseAction::HandleMontageFinished(UAnimMontage * _animMontage, bool _bInterruptted)
{
	if (_animMontage == animMontage  && bIsExecutingAction && !_bInterruptted && ActionConfig.bBindActionToAnimation)
	{
		ExitAction();
	}
}


void UACFBaseAction::Internal_OnActivated(class UACFActionsManagerComponent* _actionmanger, class UAnimMontage* _animMontage)
{
	ActionsManager = _actionmanger;
	animMontage = _animMontage;
	if (ActionsManager)
	{
		CharacterOwner = ActionsManager->CharacterOwner;
		ActionTag = ActionsManager->CurrentActionTag;
		StatisticComp = CharacterOwner->GetStatisticsComponent();

		if (StatisticComp)
		{
			StatisticComp->ConsumeStatistics(ActionConfig.ActionCost);
			StatisticComp->AddAttributeSetModifier(ActionConfig.AttributeModifier);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Statistic Component!"));
			ExitAction();
			return;
		}

		
	}

	if (ActionConfig.bStopBehavioralThree) {
		AACFAIController* aiContr = Cast< AACFAIController>(CharacterOwner->GetController());
		if (aiContr) {
			UBehaviorTreeComponent* behavComp = aiContr->GetBehaviorThreeComponent();
			if (behavComp) {
				behavComp->PauseLogic("Blocking Action");
			}
		}
	}

	PlayerController = Cast<AACFPlayerController>(UGameplayStatics::GetPlayerController(ActionsManager, 0));

	ensure(PlayerController);

	OnActionStarted();

	if(ActionConfig.bBindActionToAnimation)
	{
		ExecuteAction();	
	}
}



void UACFBaseAction::Internal_OnDeactivated()
{

	if (bIsExecutingAction)
	{
		bIsExecutingAction = false;
	}

	UAnimInstance* _animinst = (CharacterOwner->GetMesh()->GetAnimInstance());
	if (_animinst)
	{
		_animinst->OnMontageBlendingOut.RemoveDynamic(this, &UACFBaseAction::HandleMontageFinished);
	}
	UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();
	if (locComp)
	{
		locComp->SetMontageReprodutionType(EMontageReproductionType::ERootMotion);
	}

	if (StatisticComp)
	{
		StatisticComp->RemoveAttributeSetModifier(ActionConfig.AttributeModifier);
	}

	if (bIsInSubState)
	{
		OnSubActionStateExited();
	}

	if (ActionConfig.bStopBehavioralThree) {
		AACFAIController* aiContr = Cast< AACFAIController>(CharacterOwner->GetController());
		if (aiContr) {
			UBehaviorTreeComponent* behavComp = aiContr->GetBehaviorThreeComponent();
			if (behavComp) {
				behavComp->ResumeLogic("Blocking Action");
			}
		}
	}

	OnActionEnded();
}
float UACFBaseAction::GetCooldownTimeRemaining()
{

	UWorld* _world = GetWorld();
	if (_world)
	{


		return _world->GetTimerManager().GetTimerRemaining(CooldownTimerReference);

	}
	else {
		return 0.0f;
	}


}

