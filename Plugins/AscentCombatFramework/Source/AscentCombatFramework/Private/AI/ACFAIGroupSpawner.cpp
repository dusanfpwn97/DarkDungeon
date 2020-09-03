// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/ACFAIGroupSpawner.h"
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include "AI/ACFAIController.h"
#include <Components/SplineComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Actors/ACFCharacter.h"
#include "AI/Components/ACFGroupAIComponent.h"
#include "../../Public/Game/ACFData.h"

// Sets default values
AACFAIGroupSpawner::AACFAIGroupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// initalize spline component
	
	AIGroupComponent = CreateDefaultSubobject<UACFGroupAIComponent>(TEXT("Group Componnet"));
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Componnet"));
}

// Called when the game starts or when spawned
void AACFAIGroupSpawner::BeginPlay()
{
	Super::BeginPlay();

	SetGenericTeamId(uint8(AIGroupComponent->GetCombatTeam()));
	AActor* Actor = GetOwner();
	if (bSpawnOnBeginPlay && AIGroupComponent && Actor && Actor->HasAuthority()) {
		AIGroupComponent->SpawnGroup();
	}
}

FVector AACFAIGroupSpawner::GetPatrolPoint(int32 patrolIndex)
{
	return GetSplineComponent()->GetLocationAtSplinePoint(patrolIndex, ESplineCoordinateSpace::World);
}

bool AACFAIGroupSpawner::GetAgentWithIndex(int32 index, FAIAgentsInfo& outAgent) const
{
	if (AIGroupComponent) {
		TArray<FAIAgentsInfo> agents; 
		AIGroupComponent->GetGroupAgents(agents);
		if (agents.IsValidIndex(index)) {
			outAgent = agents[index];
			return true;
		}
	}

	return false;
}

AACFCharacter* AACFAIGroupSpawner::GetAgentNearestTo(const FVector& location) 
{
	if (AIGroupComponent) {
		return AIGroupComponent->GetAgentNearestTo(location);
	
	}
	return nullptr;
}

void AACFAIGroupSpawner::OnActorLoaded_Implementation()
{
	if (AIGroupComponent)
		AIGroupComponent->InitAgents();
}

void AACFAIGroupSpawner::OnActorSaved_Implementation()
{

}

void AACFAIGroupSpawner::SetGenericTeamId(const FGenericTeamId& InTeamID) {
	/*Super::SetGenericTeamId(InTeamID);*/
	CombatTeam = (ETeam)InTeamID.GetId();
}

FGenericTeamId AACFAIGroupSpawner::GetGenericTeamId() const {
	return uint8(CombatTeam);
}
