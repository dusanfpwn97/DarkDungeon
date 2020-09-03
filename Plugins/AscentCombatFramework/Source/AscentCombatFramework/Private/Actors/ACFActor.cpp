// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Actors/ACFActor.h"
#include <Kismet/KismetSystemLibrary.h>
#include "ARSStatisticsComponent.h"
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include "Components/ACFDamageHandlerComponent.h"
#include <Components/AudioComponent.h>
#include "Components/ACFEffectsManagerComponent.h"
#include <Perception/AISense_Sight.h>
#include "Net/UnrealNetwork.h"


// Sets default values
AACFActor::AACFActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetReplicates(true);
	StatisticsComp = CreateDefaultSubobject<UARSStatisticsComponent>(
		TEXT("Statistic Component"));

	AIPerceptionStimuliSource =
		CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(
			TEXT("Perception Stimuli Component"));
	DamageHandlerComp = CreateDefaultSubobject<UACFDamageHandlerComponent>(
		TEXT("Damage Handler Component"));

	AIPerceptionStimuliSource->bAutoRegister = true;
	AIPerceptionStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());

	EquipmentComp = CreateDefaultSubobject<UACFEquipmentComponent>(
		TEXT("Equipment Component"));
	CombatTeam = ETeam::EEnemiesTeam;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComp->SetRelativeLocation(FVector::ZeroVector);
	AudioComp->bAllowSpatialization = true;
	AudioComp->bOverrideAttenuation = false;
}

void AACFActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AACFActor, bIsDead);

}

// Called when the game starts or when spawned
void AACFActor::BeginPlay() {

	Super::BeginPlay();
	SetGenericTeamId(uint8(CombatTeam));

	if (UKismetSystemLibrary::IsServer(this)) {

		if (EquipmentComp) {
			EquipmentComp->InitializeInventoryAndEquipment();
		}

		if (StatisticsComp) {
			StatisticsComp->InitializeAttributeSet();
		}

		if (DamageHandlerComp) {
			DamageHandlerComp->OnOwnerDeath.AddDynamic(
				this, &AACFActor::HandleDeath);
			DamageHandlerComp->InitializeDamageCollisions(CombatTeam);
		}

		EffetsComp = FindComponentByClass<UACFEffectsManagerComponent>();
	}
}


float AACFActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return DamageHandlerComp->TakeDamage(this, Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AACFActor::HandleDeath()
{
	bIsDead = true;
	OnActorDestroyed();
}

void AACFActor::OnActorDestroyed_Implementation()
{

}

void AACFActor::SetGenericTeamId(const FGenericTeamId& InTeamID) {
	/*Super::SetGenericTeamId(InTeamID);*/
	CombatTeam = (ETeam)InTeamID.GetId();
}

FGenericTeamId AACFActor::GetGenericTeamId() const {
	return uint8(CombatTeam);
}


FACFDamageEvent AACFActor::GetLastDamageInfo() const {
	return DamageHandlerComp->GetLastDamageInfo();
}

