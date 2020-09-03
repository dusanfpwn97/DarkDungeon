// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/ACFAIController.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>
#include <BehaviorTree/BlackboardData.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Enum.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AIPerceptionTypes.h>
#include <Engine/Engine.h>
#include <Components/SplineComponent.h>
#include "AI/ACFAIGroupSpawner.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Int.h>
#include "Game/ACFData.h"
#include "Components/ACFLocomotionComponent.h"
#include <AI/NavigationSystemBase.h>
#include <NavigationSystem.h>
#include <Navigation/PathFollowingComponent.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Bool.h>
#include <Perception/AISense_Hearing.h>
#include "AI/Components/ACFGroupAIComponent.h"
#include <Navigation/CrowdFollowingComponent.h>
#include "AI/Components/ACFCommandsManagerComponent.h"
#include "ATSTargetingComponent.h"
#include "Components/ACFInteractionComponent.h"
#include "Game/ACFGameState.h"
#include "ATSAITargetComponent.h"
#include "Interfaces/ACFEntityInterface.h"
#include "Actors/ACFActor.h"
#include "Components/ACFDamageHandlerComponent.h"
#include "AI/Components/ACFThreatManagerComponent.h"
#include "AI/Components/ACFCombatBehaviourComponent.h"
#include "Game/ACFFunctionLibrary.h"


AACFAIController::AACFAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	CommandsManagerComp = CreateDefaultSubobject<UACFCommandsManagerComponent>(TEXT("CommandManager"));
	TargetingComponent = CreateDefaultSubobject<UATSAITargetComponent>(TEXT("TargetComp"));
//	CombatBehaviorComponent = CreateDefaultSubobject<UACFCombatBehaviourComponent>(TEXT("CombatBehav"));
	ThreatComponent = CreateDefaultSubobject<UACFThreatManagerComponent>(TEXT("ThreatManager"));

}




void AACFAIController::OnPossess(APawn* _possPawn)
{
	//UE_LOG(LogTemp, Warning, TEXT("AACFAIController possess on %s"), *_possPawn->GetName());

	Super::OnPossess(_possPawn);
	CharacterOwned = Cast<AACFCharacter>(_possPawn);
	if (CharacterOwned == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AACFAIController possess non - AACEnemyCharacter type, %s"), *_possPawn->GetName());
		return;
	}

	CharacterOwned->OnDamageReceived.AddDynamic(this, &AACFAIController::HandleCharacterHit);
	CharacterOwned->GetDamageHandlerComponent()->OnOwnerDeath.AddDynamic(this, &AACFAIController::HandleCharacterDeath);

	if (BehaviorTree == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("This AACEnemyCharacter should be assigned with a behavior Tree, %s"), *_possPawn->GetName());
		return;
	}


	UBlackboardData* const bbData = BehaviorTree->BlackboardAsset;
	if (bbData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("This behavior Tree should be assigned with a blackborad, %s"), *_possPawn->GetName());
		return;
	}

	BlackboardComponent->InitializeBlackboard(*bbData);
	Blackboard = BlackboardComponent;

	// Fetch the Keys
	targetActorKey = BlackboardComponent->GetKeyID("TargetActor");
	targetPointLocationKey = BlackboardComponent->GetKeyID("TargetLocation");
	targetActorDistanceKey = BlackboardComponent->GetKeyID("TargetActorDistance");
	aiStateKey = BlackboardComponent->GetKeyID("AIState");
	targetDistanceKey = BlackboardComponent->GetKeyID("TargetLocationDistance");
	commandDurationTimeKey = BlackboardComponent->GetKeyID("CommandDuration");
	groupLeaderKey = BlackboardComponent->GetKeyID("GroupLeader");
	comboCounterKey = BlackboardComponent->GetKeyID("ComboCounter");
	combatStateKey = BlackboardComponent->GetKeyID("CombatState");
	leadDistanceKey = BlackboardComponent->GetKeyID("GroupLeadDistance");

	BlackboardComponent->SetValue<UBlackboardKeyType_Float>(targetDistanceKey, MAX_FLT);
	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(targetPointLocationKey, _possPawn->GetActorLocation());

	CharacterOwned->AssignTeam(CombatTeam);
	SetGenericTeamId(FGenericTeamId(uint8(CombatTeam)));

	SetCurrentAIStateBK(DefaultState);
	// Launch behavior Tree
	BehaviorTreeComponent->StartTree(*BehaviorTree);

	if (PerceptionComponent) {
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AACFAIController::HandlePerceptionUpdated);
	}

	if (ThreatComponent) {
		ThreatComponent->OnNewMaxThreateningActor.AddDynamic(this, &AACFAIController::HandleMaxThreatUpdated);
	}

	EnableCharacterComponents(false);

}

void AACFAIController::OnUnPossess()
{
	Super::OnUnPossess();

	if (PerceptionComponent) {
		PerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &AACFAIController::HandlePerceptionUpdated);
	}

	if (ThreatComponent) {
		ThreatComponent->OnNewMaxThreateningActor.RemoveDynamic(this, &AACFAIController::HandleMaxThreatUpdated);
	}
}

void AACFAIController::EnableCharacterComponents(bool bEnabled)
{
	UACFInteractionComponent* interComponent = CharacterOwned->FindComponentByClass<UACFInteractionComponent>();

	if (interComponent)
	{
		if (bEnabled)
			interComponent->RegisterComponent();
		else
			interComponent->UnregisterComponent();
	}
}


void AACFAIController::HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!bIsAggressive || !Stimulus.IsActive())
		return;

	if (Actor == GetPawn())
		return;

	if (Actor && !ThreatComponent->IsThreatening(Actor))
	{
		float threat = ThreatComponent->GetDefaultThreatForActor(Actor);
		if (threat == 0.f) {
			return;

		}
		ThreatComponent->AddThreat(Actor, threat);
	}	
}





void AACFAIController::HandleMaxThreatUpdated(AActor* newMax)
{
	SetTarget(newMax);
}

void AACFAIController::PostInitProperties()
{
	Super::PostInitProperties();

}

void AACFAIController::BeginPlay()
{
	Super::BeginPlay();
	CombatBehaviorComponent = FindComponentByClass<UACFCombatBehaviourComponent>();
}

void AACFAIController::EndPlay(const EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	AACFGameState * gameState = GetWorld()->GetGameState<AACFGameState>();
	if (gameState)
	{
		gameState->RemoveAIFromBattle(this);
	}

}

void AACFAIController::TriggerCommand(const FGameplayTag& command)
{
	if (CommandsManagerComp)
		CommandsManagerComp->TriggerCommand(command);
}

void AACFAIController::SetGenericTeamId(const FGenericTeamId & InTeamID)
{
	Super::SetGenericTeamId(InTeamID);
	CombatTeam = (ETeam)InTeamID.GetId();
}

FGenericTeamId AACFAIController::GetGenericTeamId() const
{
	return uint8(CombatTeam);
}

void AACFAIController::SetWaitDurationTimeBK(float time)
{
	if (Blackboard)
		Blackboard->SetValue<UBlackboardKeyType_Float>(commandDurationTimeKey, time);
}

float AACFAIController::GetCommandDurationTimeBK() const
{
	if (Blackboard)
		return Blackboard->GetValue<UBlackboardKeyType_Float>(commandDurationTimeKey);
	return -1.f;
}

void AACFAIController::SetLeadActorBK(AActor* _target)
{
	BlackboardComponent->SetValue<UBlackboardKeyType_Object>(groupLeaderKey, _target);
}

FVector AACFAIController::GetTargetPointLocationBK() const
{
	return 	BlackboardComponent->GetValue<UBlackboardKeyType_Vector>(targetPointLocationKey);
}

AActor* AACFAIController::GetLeadActorBK() const
{
	if (Blackboard)
	{
		AActor* lead = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(groupLeaderKey));
		return lead;
	}
	return nullptr;
}

void AACFAIController::SetTargetActorBK(AActor* _target)
{
	if (Blackboard)
		Blackboard->SetValue<UBlackboardKeyType_Object>(targetActorKey, _target);
}

void AACFAIController::SetTargetLocationBK(const FVector& _targetLocation)
{
	if (Blackboard)
		Blackboard->SetValue<UBlackboardKeyType_Vector>(targetPointLocationKey, _targetLocation);
}

void AACFAIController::SetCurrentAIStateBK(EAIState _aiState)
{
	if (_aiState == GetAIStateBK())
	{
		return;
	}

	if (GetAIStateBK() == EAIState::EBattle && CombatBehaviorComponent && PerceptionComponent && _aiState != EAIState::EBattle)
	{
		CombatBehaviorComponent->UninitBehavior();
// 		PerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
// 		PerceptionComponent->SetSenseEnabled(UAISense_Hearing::StaticClass(), true);
	}


	if (Blackboard)
		Blackboard->SetValue<UBlackboardKeyType_Enum>(aiStateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(_aiState));

	OnAIStateChanged.Broadcast(_aiState);

	ELocomotionState* locstate = LocomotionStateByAIState.Find(_aiState);
	if (locstate && CharacterOwned && CharacterOwned->GetLocomotionComponent())
	{
		CharacterOwned->GetLocomotionComponent()->SetLocomotionState(*locstate);
	}

	if (_aiState == EAIState::EFollowLeader)
	{
		SetFocus(GetLeadActorBK(), EAIFocusPriority::Gameplay);
	}

	if (_aiState == EAIState::EBattle && CombatBehaviorComponent)
	{
		CombatBehaviorComponent->InitBehavior(this);
	}

	//GameState settings
	AACFGameState * gameState = GetWorld()->GetGameState<AACFGameState>();
	if (!gameState) {
		return;
	}

	if ( _aiState == EAIState::EBattle)
	{
		gameState->AddAIToBattle(this);
	}
	else 
	{
		gameState->RemoveAIFromBattle(this);
	}
}

AActor * AACFAIController::GetTargetActorBK() const
{
	if (Blackboard)
	{
		AActor* targetActor = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(targetActorKey));
		return targetActor;
	}
	return nullptr;
}

EAIState AACFAIController::GetAIStateBK() const
{
	return static_cast<EAIState>(Blackboard->GetValue<UBlackboardKeyType_Enum>(aiStateKey));
}

EAICombatState AACFAIController::GetCombatStateBK() const
{
	return static_cast<EAICombatState>(Blackboard->GetValue<UBlackboardKeyType_Enum>(combatStateKey));
}

void AACFAIController::SetCombatStateBK(EAICombatState _aiState)
{
	if (Blackboard)
		Blackboard->SetValue<UBlackboardKeyType_Enum>(combatStateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(_aiState));

	if (CombatBehaviorComponent && CharacterOwned)
	{
		const FAICombatStateConfig *locstate = CombatBehaviorComponent->CombatStatesConfig.Find(_aiState);
		if (locstate  && CharacterOwned->GetLocomotionComponent())
		{
			CharacterOwned->GetLocomotionComponent()->SetLocomotionState(locstate->LocomotionState);
		}
	}
}
void AACFAIController::SetComboCounterBK(int32 _comboCount) 
{
	if (Blackboard)
		Blackboard->SetValue < UBlackboardKeyType_Int >(comboCounterKey, _comboCount);
}

int32  AACFAIController::GetComboCounterBK() const
{
	return Blackboard->GetValue < UBlackboardKeyType_Int >(comboCounterKey);
}

float AACFAIController::GetTargetActorDistanceBK() const
{
	if (Blackboard)
		return Blackboard->GetValue < UBlackboardKeyType_Float >(targetActorDistanceKey);

	return -1.f;

}

float AACFAIController::GetTargetPointDistanceBK() const
{
	if (Blackboard)
		return Blackboard->GetValue < UBlackboardKeyType_Float >(targetDistanceKey);

	return -1.f;
}

float AACFAIController::GetHomeDistanceBK() const
{
	if (Blackboard)
		return Blackboard->GetValue < UBlackboardKeyType_Float >(leadDistanceKey);

	return -1.f;
}

void AACFAIController::SetTargetPointDistanceBK(float _distance)
{
	if (Blackboard)
		 Blackboard->SetValue < UBlackboardKeyType_Float >(targetDistanceKey, _distance);
}

void AACFAIController::SetHomeDistanceBK(float _distance)
{
	if (Blackboard)
		Blackboard->SetValue < UBlackboardKeyType_Float >(leadDistanceKey, _distance);
}

void AACFAIController::SetTargetActorDistanceBK(float _distance)
{
	if (Blackboard)
		Blackboard->SetValue < UBlackboardKeyType_Float >(targetActorDistanceKey, _distance);
}

float AACFAIController::GetPathDistanceFromTarget()
{
	return GetPathFollowingComponent()->GetRemainingPathCost();
}

bool AACFAIController::TryGoToNextWaypoint()
{
	USplineComponent* SplineComponent = nullptr;

	if (mGroup) {
		SplineComponent = mGroup->GetSplineComponent();
	}

	if (!SplineComponent) {
		return false;
	}

	if (bIsReversed)
	{
		if (patrolIndex <= 0)
		{
			if (SplineComponent->IsClosedLoop())
			{
				patrolIndex = SplineComponent->GetNumberOfSplinePoints() - 1;
			}
			else
			{
				patrolIndex = 1;
				bIsReversed = false;
			}
		}
		else --patrolIndex;
	}
	else
	{
		if (patrolIndex >= SplineComponent->GetNumberOfSplinePoints() - 1)
		{
			if (SplineComponent->IsClosedLoop())
			{
				patrolIndex = 0;
			}
			else
			{
				bIsReversed = true,
				patrolIndex = SplineComponent->GetNumberOfSplinePoints() - 2;
			}

		}
		else ++patrolIndex;
	}

	FTransform waypoint = SplineComponent->GetTransformAtSplinePoint(patrolIndex, ESplineCoordinateSpace::World);

	SetTargetLocationBK(waypoint.GetLocation());
	return true;
}

void AACFAIController::TeleportNearLead()
{
	AActor* lead = GetLeadActorBK();
	if (lead)
	{
		FVector homeLoc = lead->GetActorLocation();
		FVector outLoc;
		if (CharacterOwned && UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, homeLoc, outLoc, TeleportHomeNearRadius))
		{
			CharacterOwned->SetActorLocation(homeLoc);
		}
	}
}

void AACFAIController::OnTargetDeathHandle()
{
	if (CharacterOwned->IsAlive())
	{
		AActor* target = ThreatComponent->GetActorWithHigherThreat();
		if (target)
		{
			SetTarget(target);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s is requesting new target - AACFAIController::OnTargetDeathHandle"), *this->GetName());
			RequestAnotherTarget();
		}
	}
}

void AACFAIController::SetGroupOwner(class UACFGroupAIComponent* _Group, int _groupIndex, bool _disablePerception)
{
	if (_Group)
	{
		mGroup = _Group;
		mGroupIndex = _groupIndex;

		UAIPerceptionComponent* perception = FindComponentByClass< UAIPerceptionComponent>();
		if (perception && _disablePerception)
		{
			perception->UnregisterComponent();
// 			perception->SetSenseEnabled(UAISense_Sight::StaticClass(), !_disablePerception);
// 			perception->SetSenseEnabled(UAISense_Hearing::StaticClass(), !_disablePerception);
		}
	
	}
}



void AACFAIController::SetTarget(AActor* inTarget)
{
	AActor* currentTarget = GetTargetActorBK();

	TargetingComponent->SetCurrentTarget(inTarget);
	SetTargetActorBK(inTarget);

	if (!inTarget || inTarget == CharacterOwned)
	{
		ThreatComponent->RemoveThreatening(currentTarget);
		if (currentTarget) {

			UACFDamageHandlerComponent* oldDamageComp = currentTarget->FindComponentByClass< UACFDamageHandlerComponent>();
			if (oldDamageComp) {
				oldDamageComp->OnOwnerDeath.RemoveDynamic(this, &AACFAIController::OnTargetDeathHandle);
			}
		}
		return;
	}


	// if our target is changed to a new target
	if (inTarget != currentTarget)
	{	
		IACFEntityInterface* entity = Cast<IACFEntityInterface>(inTarget);

		if (currentTarget) {

			UACFDamageHandlerComponent* oldDamageComp = currentTarget->FindComponentByClass< UACFDamageHandlerComponent>();
			if (oldDamageComp) {
				oldDamageComp->OnOwnerDeath.RemoveDynamic(this, &AACFAIController::OnTargetDeathHandle);
			}
		}

		if (entity && inTarget &&  IACFEntityInterface::Execute_IsEntityAlive(inTarget) && 
			UACFFunctionLibrary::AreEnemyTeams(CombatTeam, IACFEntityInterface::Execute_GetEntityCombatTeam(inTarget))
			)
		{
			SetCurrentAIStateBK(EAIState::EBattle);
			UACFDamageHandlerComponent* damageComp = inTarget->FindComponentByClass< UACFDamageHandlerComponent>();
			if (damageComp) {
				damageComp->OnOwnerDeath.AddDynamic(this, &AACFAIController::OnTargetDeathHandle);
			}

			if (mGroup)
			{

				AACFCharacter* aiTarget = Cast< AACFCharacter>(inTarget);
				if(aiTarget){
					AACFAIController* targetCont = Cast< AACFAIController>(aiTarget->GetController());
					if (targetCont)
					{
						mGroup->SetEnemyGroup(targetCont->GetGroup());
					}
				}

				if (!mGroup->IsInBattle())
				{
					mGroup->SetInBattle(true, inTarget);
				}
			}
		}
	}
}

AActor * AACFAIController::GetTarget() const
{
	return 	TargetingComponent->GetCurrentTarget();
}

void AACFAIController::RequestAnotherTarget()
{
	if ( CharacterOwned && !CharacterOwned->IsPendingKill())
	{
		AActor* target = ThreatComponent->GetActorWithHigherThreat();
		if (mGroup && !target)
		{
			target = mGroup->RequestNewTarget(this);
		} 		

		if (target)
		{
			SetTarget(target);
		}
		else
		{
			SetCurrentAIStateBK(DefaultState);
		}
	}
}





void AACFAIController::HandleCharacterHit(const FACFDamageEvent& damageReceived)
{
	if (damageReceived.DamageDealer && !damageReceived.DamageDealer->IsAlive())
		return;
	if (bShouldReactOnHit) {
		ThreatComponent->AddThreat(damageReceived.DamageDealer, damageReceived.FinalDamage);
		if (GetAIStateBK() != EAIState::EBattle) {
			SetTarget(ThreatComponent->GetActorWithHigherThreat());
		}

		if (mGroup && !mGroup->IsInBattle()) {
			mGroup->SetInBattle(true, damageReceived.DamageDealer);
		}
	}

}

void AACFAIController::HandleCharacterDeath()
{
	if (mGroup)
	{
		mGroup->OnChildDeath(mGroupIndex);
	}
	SetCurrentAIStateBK(EAIState::EFollowLeader);
	UnPossess();
	Destroy();
}
