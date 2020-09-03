// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Components/ACFDamageHandlerComponent.h"
#include <Engine/EngineTypes.h>
#include <GameFramework/Controller.h>
#include <GameFramework/Actor.h>
#include <GameFramework/DamageType.h>
#include "Game/ACFFunctionLibrary.h"
#include <PhysicsEngine/BodyInstance.h>
#include "AI/Components/ACFCombatBehaviourComponent.h"
#include "AI/ACFAIController.h"
#include "ARSStatisticsComponent.h"
#include "Actors/ACFCharacter.h"
#include "Game/ACFDamageType.h"
#include "ARSStatisticsData.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Components/MeshComponent.h>
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UACFDamageHandlerComponent::UACFDamageHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bIsAlive=true;
}



void UACFDamageHandlerComponent::InitializeDamageCollisions(ETeam combatTeam)
{
	switch (combatTeam) {
	case ETeam::EHeroesTeam:
		AssignCollisionChannels(ECC_ACFHeroesChannel);
		break;
	case ETeam::EEnemiesTeam:
		AssignCollisionChannels(ECC_ACFEnemiesChannel);
		break;
	}
}

void UACFDamageHandlerComponent::AssignCollisionChannels(ECollisionChannel channel)
{
	TArray<UActorComponent*> meshes;
	GetOwner()->GetComponents(UMeshComponent::StaticClass(), meshes);

	for (auto mesh : meshes) {
		UMeshComponent* meshComp = Cast< UMeshComponent>(mesh);

		if (meshComp) {
			meshComp->SetCollisionObjectType(channel);
		}
	}
}


float UACFDamageHandlerComponent::TakeDamage(class AActor* damageReceiver, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!damageReceiver)
		return 0;

	FHitResult outDamage;
	FVector ShotDirection;
	DamageEvent.GetBestHitInfo(damageReceiver, DamageCauser, outDamage, ShotDirection);

	ConstructDamageReceived(damageReceiver, Damage, EventInstigator, outDamage.Location,
		outDamage.Component.Get(), outDamage.BoneName,
		ShotDirection, DamageEvent.DamageTypeClass,
		DamageCauser);

	if (!DamageCalculator ) {
		DamageCalculator =
			NewObject<UACFDamageCalculation>(this, UACFFunctionLibrary::GetDamageCalculationClass());
	}

	if (DamageCalculator) {
		FACFDamageEvent outDamageEvent;
		// APPARENTLY USELESS STUFF TO LET YOU MODIFY IN BLUEPRINT THE DAMAGE WITH
		// YOUR OWN CALCULATION
		DamageCalculator->CalculateFinalDamage(LastDamageReceived, outDamageEvent);
		LastDamageReceived = outDamageEvent;
		
		UARSStatisticsComponent* StatisticsComp = damageReceiver->FindComponentByClass<UARSStatisticsComponent>();

		if (StatisticsComp) {
			LastDamageReceived.FinalDamage =
				UACFFunctionLibrary::ApplyRandomDeviationToDamage(LastDamageReceived.FinalDamage) *	LastDamageReceived.DamageMultiplier;

			FStatisticModifier statMod(UACFFunctionLibrary::GetHealthTag(), -LastDamageReceived.FinalDamage);
			StatisticsComp->ModifyStat(statMod);
		}
		ClientsReceiveDamage(LastDamageReceived);
		return LastDamageReceived.FinalDamage;
	}
	return 0.f;
}

void UACFDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	UARSStatisticsComponent* StatisticsComp = GetOwner()->FindComponentByClass< UARSStatisticsComponent>();
	if (StatisticsComp) {

		StatisticsComp->OnStatisiticReachesZero.AddDynamic(
			this, &UACFDamageHandlerComponent::HandleStatReachedZero);
	}

	//GetOwner()->OnTakeAnyDamage.AddDynamic(this, UACFDamageHandlerComponent::HandleDamageTaken);
}

void UACFDamageHandlerComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UACFDamageHandlerComponent, bIsAlive);

}

void UACFDamageHandlerComponent::ConstructDamageReceived(
	AActor* DamagedActor, float Damage, class AController* InstigatedBy,
	FVector HitLocation, class UPrimitiveComponent* FHitComponent,
	FName BoneName, FVector ShotFromDirection,
	TSubclassOf<UDamageType> DamageType, AActor* DamageCauser) {

	LastDamageReceived.contextString = NAME_None;
	LastDamageReceived.FinalDamage = Damage;
	LastDamageReceived.DamageDealer = Cast<AACFCharacter>(DamageCauser);
	LastDamageReceived.hitDirection = ShotFromDirection;
	LastDamageReceived.hitResult.BoneName = BoneName;
	LastDamageReceived.hitResult.Actor = DamagedActor;
	LastDamageReceived.hitResult.ImpactPoint = HitLocation;
	LastDamageReceived.hitResult.Location = HitLocation;


	LastDamageReceived.DamageReceiver = DamagedActor;
	LastDamageReceived.DamageClass = DamageType;

	LastDamageReceived.DamageDirection =
		UACFFunctionLibrary::GetHitDirectionByHitResult(
			LastDamageReceived.DamageDealer, LastDamageReceived.hitResult);

	LastDamageReceived.HitResponseAction = FGameplayTag();
	
	AACFCharacter* acfReceiver = Cast<AACFCharacter>(DamagedActor);

	if (acfReceiver) {
		LastDamageReceived.DamageZone = acfReceiver->GetDamageZoneByBoneName(BoneName);
		LastDamageReceived.DamageMultiplier =
			UACFFunctionLibrary::GetDamageMultiplierByDamageZone(
				LastDamageReceived.DamageZone);
		FBodyInstance* bodyInstance = acfReceiver->GetMesh()->GetBodyInstance(BoneName);
		if (bodyInstance) {
			LastDamageReceived.PhysMaterial = bodyInstance->GetSimplePhysicalMaterial();
		}

		AACFAIController* controller = Cast<AACFAIController>(acfReceiver->GetController());
		if (controller) {
			UACFCombatBehaviourComponent* behav = controller->GetCombatBehavior();
			ensure(behav);

			LastDamageReceived.HitResponseAction =
				behav->EvaluateHitResponse(LastDamageReceived);
		}	
	}
	
}

void UACFDamageHandlerComponent::HandleStatReachedZero(FGameplayTag stat)
{
	if (UACFFunctionLibrary::GetHealthTag() == stat) {

		if (GetOwner()->HasAuthority()) {
			if (bAutoDestroyOnDeath) {
				GetOwner()->SetLifeSpan(ActorLifeSpanOnDeath);
			}

			UARSStatisticsComponent* StatisticsComp = GetOwner()->FindComponentByClass<UARSStatisticsComponent>();
			if (StatisticsComp) {
				StatisticsComp->StopRegeneration();
				if (LastDamageReceived.DamageDealer) {
					UARSStatisticsComponent* dealerStatComp = LastDamageReceived.DamageDealer->GetStatisticsComponent();
					if (dealerStatComp) {
						dealerStatComp->AddExp(StatisticsComp->GetExpOnDeath());
					}
				}
			}
		}
		bIsAlive = false;
		OnOwnerDeath.Broadcast();
	}
}


void UACFDamageHandlerComponent::ClientsReceiveDamage_Implementation(
	const FACFDamageEvent& damageEvent) {
	LastDamageReceived = damageEvent;

	OnDamageReceived.Broadcast(damageEvent);
}

bool UACFDamageHandlerComponent::ClientsReceiveDamage_Validate(const FACFDamageEvent& damageEvent) {
	return true;
}