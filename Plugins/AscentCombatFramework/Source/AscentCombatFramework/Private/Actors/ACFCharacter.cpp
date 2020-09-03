// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Actors/ACFCharacter.h"
#include "Animation/ACFAnimInstance.h"
#include "Game/ACFDamageCalculation.h"
#include "Game/ACFDamageType.h"
#include "Components/ACFEffectsManagerComponent.h"
#include "Components/ACFEquipmentComponent.h"
#include "Game/ACFFunctionLibrary.h"
#include "Game/ACFGameInstance.h"
#include "Game/ACFGameMode.h"
#include "Components/ACFLocomotionComponent.h"
#include "Items/ACFMeleeWeapon.h"
#include "Game/ACFPlayerController.h"
#include "Items/ACFRangedWeapon.h"
#include "Items/ACFWeapon.h"
#include "ACMCollisionManagerComponent.h"
#include "ARSStatisticsComponent.h"
#include "ATSTargetingComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>
#include <Engine/EngineTypes.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/DamageType.h>
#include <GenericTeamAgentInterface.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include <PhysicalMaterials/PhysicalMaterial.h>
#include <PhysicsEngine/BodyInstance.h>
#include "Net/UnrealNetwork.h"
#include "Components/ACFDamageHandlerComponent.h"
#include "ATSBaseTargetComponent.h"
#include "Components/ACFRagdollComponent.h"

// Sets default values
AACFCharacter::AACFCharacter(const FObjectInitializer &ObjectInitializer)
    : Super(
          ObjectInitializer) //.SetDefaultSubobjectClass<UACFCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  SetReplicates(true);
  SetReplicateMovement(true);

  ActionsComp = CreateDefaultSubobject<UACFActionsManagerComponent>(
      TEXT("Actions Manager"));
  LocomotionComp = CreateDefaultSubobject<UACFLocomotionComponent>(
      TEXT("Locomotion Component"));
  StatisticsComp = CreateDefaultSubobject<UARSStatisticsComponent>(
      TEXT("Statistic Component"));
  CollisionComp = CreateDefaultSubobject<UACMCollisionManagerComponent>(
      TEXT("Collisions Manager"));
  EquipmentComp = CreateDefaultSubobject<UACFEquipmentComponent>(
      TEXT("Equipment Component"));
  AIPerceptionStimuliSource =
      CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(
          TEXT("Perception Stimuli Component"));
  DamageHandlerComp = CreateDefaultSubobject<UACFDamageHandlerComponent>(
	  TEXT("Damage Handler Component"));

  RagdollComp = CreateDefaultSubobject<UACFRagdollComponent>(
	  TEXT("Ragdoll Component"));
  CombatTeam = ETeam::EEnemiesTeam;

  AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
  AudioComp->SetupAttachment(GetCapsuleComponent());
  AudioComp->SetRelativeLocation(FVector::ZeroVector);
  AudioComp->bAllowSpatialization = true;
  AudioComp->bOverrideAttenuation = false;

  // Don't rotate when the controller rotates. Let that just affect the camera.
  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;

  CharacterName = FText::FromString("Dude");

  bIsImmortal = false;

  PrimaryActorTick.bStartWithTickEnabled = false;

  BoneNameToDamageZoneMap.Add("head", EDamageZone::EHighDamage);
}

void AACFCharacter::PostInitProperties() {
  Super::PostInitProperties();

  if (GetMesh()) {
    GetMesh()->SetCollisionObjectType(GetCollisionChannel());
  }

  EffetsComp = FindComponentByClass<UACFEffectsManagerComponent>();
}


void AACFCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AACFCharacter, CombatTeam);

}


void AACFCharacter::PreInitializeComponents() {
  Super::PreInitializeComponents();
}

// Called when the game starts or when spawned
void AACFCharacter::BeginPlay() {
  Super::BeginPlay();
  EffetsComp = FindComponentByClass<UACFEffectsManagerComponent>();

  InitializeCharacter();
}

void AACFCharacter::InitializeCharacter() {
  if (HasAuthority() && !bInitialized) {

    if (StatisticsComp) {
      StatisticsComp->InitializeAttributeSet();
    }

    if (DamageHandlerComp) {
        DamageHandlerComp->OnOwnerDeath.AddDynamic(
			this, &AACFCharacter::HandleCharacterDeath);
		DamageHandlerComp->InitializeDamageCollisions(CombatTeam);

    }
    
    if (EquipmentComp) {
      EquipmentComp->InitializeInventoryAndEquipment();
    }
  }

  if (EquipmentComp) {
    EquipmentComp->OnEquipmentChanged.AddDynamic(
        this, &AACFCharacter::HandleEquipmentChanged);
  }

  if (DamageHandlerComp) {
      DamageHandlerComp->OnDamageReceived.AddDynamic(this, &AACFCharacter::HandleDamageReceived);
  }

  bInitialized = true;
  OnCharacterFullyInitialized.Broadcast();
}

void AACFCharacter::HandleEquipmentChanged(const FEquipment &equipment) {

  FGameplayTag movesetTag, overlayTag, actionsTag;

  if (equipment.MainWeapon) {
    movesetTag = equipment.MainWeapon->GetAssociatedMovesetTag();
    overlayTag = equipment.MainWeapon->GetAssociatedMovesetOverlayTag();
	actionsTag = equipment.MainWeapon->GetAssociatedMovesetActionsTag();

    if (equipment.MainWeapon->IsA<AACFMeleeWeapon>()) {
      CombatType = ECombatType::EMelee;
    } else if (equipment.MainWeapon->IsA<AACFRangedWeapon>()) {
      CombatType = ECombatType::ERanged;
    }
  } else {
    movesetTag = UACFFunctionLibrary::GetMovesetTypeTagRoot();
    overlayTag = UACFFunctionLibrary::GetAnimationOverlayTagRoot();
    CombatType = ECombatType::EUnarmed;
  }

  UACFAnimInstance* acfAnimInst = GetACFAnimInstance();
  if (acfAnimInst){
	  if (movesetTag != FGameplayTag() && movesetTag != acfAnimInst->GetCurrentMoveset()) {
		  Internal_SwitchMovetype(movesetTag);
	  }
	if (overlayTag != FGameplayTag() && overlayTag != acfAnimInst->GetCurrentOverlay()) {
		acfAnimInst->SetAnimationOverlay(overlayTag);
	}
	acfAnimInst->SetMovesetActionsTag(actionsTag);
  }



  OnCombatTypeChanged.Broadcast(CombatType);
}

void AACFCharacter::AssignTeam(ETeam team) {
  CombatTeam = team;

  SetGenericTeamId(uint8(CombatTeam));

  if (DamageHandlerComp) {
	  DamageHandlerComp->InitializeDamageCollisions(CombatTeam);
  }
  SetupCollisionManager();
}

void AACFCharacter::OnActorLoaded_Implementation() {
  if (EquipmentComp) {
    EquipmentComp->RefreshEquipmentAttachments();
  }
  if (!GetController()) {
    SpawnDefaultController();
  }
}

void AACFCharacter::OnActorSaved_Implementation() {}

ETeam AACFCharacter::GetCombatTeam() const {

  return CombatTeam;
}

void AACFCharacter::HandleDamageReceived(const FACFDamageEvent& damageReceived)
{
    OnDamageReceived.Broadcast(damageReceived);
}

void AACFCharacter::SetupCollisionManager() {
  if (CollisionComp) {
  
    CollisionComp->OnCollisionDetected.RemoveAll(this);
    CollisionComp->SetupCollisionManager(GetMesh());
    CollisionComp->SetActorOwner(this);
    CollisionComp->OnCollisionDetected.AddDynamic(
        this, &AACFCharacter::HandleAttackHit);
    CollisionComp->SetCollisionChannels(GetEnemiesCollisionChannel());
    CollisionComp->AddActorToIgnore(this);
  }
}

void AACFCharacter::Internal_SwitchMovetype(FGameplayTag moveType) {
  OnMovementTypeChanged.Broadcast(moveType);
}

void AACFCharacter::ClientsSwitchMovetype_Implementation( FGameplayTag moveType) {
    Internal_SwitchMovetype(moveType);
}

bool AACFCharacter::ClientsSwitchMovetype_Validate(FGameplayTag moveType) {
  return true;
}

void AACFCharacter::SwitchMovementType_Implementation(FGameplayTag moveType) {
  ClientsSwitchMovetype(moveType);
}

bool AACFCharacter::SwitchMovementType_Validate(FGameplayTag moveType) {
  return true;
}

TArray<TEnumAsByte<ECollisionChannel>> AACFCharacter::GetEnemiesCollisionChannel() const {
  TArray<TEnumAsByte<ECollisionChannel>> channels;

  if (UACFFunctionLibrary::GetBattleType(GetWorld()) ==
      EBattleType::EEveryonAgainstEveryone) {
    channels.Add(ECC_ACFEnemiesChannel);
    channels.Add(ECC_ACFHeroesChannel);
  } else {
    if (CombatTeam == ETeam::EHeroesTeam) {
      channels.Add(ECC_ACFEnemiesChannel);
    } else if (CombatTeam == ETeam::EEnemiesTeam) {
      channels.Add(ECC_ACFHeroesChannel);
    }
  }
  return channels;
}

bool AACFCharacter::CanBeRanged() const {

  return EquipmentComp->HasOnBodyAnyWeaponOfType(
      AACFRangedWeapon::StaticClass());
}

// Called to bind functionality to input
void AACFCharacter::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void AACFCharacter::HandleCharacterDeath()
{
	switch (DeathType) {
	case EDeathType::EDeathAction:
		ForceAction(UACFFunctionLibrary::GetDefaultDeathState());
		break;
	case EDeathType::EGoRagdoll:
		RagdollComp->GoRagdollFromDamage(GetLastDamageInfo());
		break;
	case EDeathType::EDestroyImmediately:
		Destroy();
		break;
	default:
		break;

	}

	ClientsOnCharacterDeath();
}

void AACFCharacter::ClientsOnCharacterDeath_Implementation() {
	if (DeathType == EDeathType::EGoRagdoll) {
		RagdollComp->GoRagdollFromDamage(GetLastDamageInfo());
	}
  OnCharacterDeath();
}

bool AACFCharacter::ClientsOnCharacterDeath_Validate() {
	return true; 
}

float AACFCharacter::PlayNetworkedMontage(
    class UAnimMontage *AnimMontage, float InPlayRate /*= 1.f*/,
    FName StartSectionName /* = NAME_None*/) {
  if (AnimMontage) {
    ServerSendPlayMontage(AnimMontage, InPlayRate, StartSectionName);
    int index = AnimMontage->GetSectionIndex(StartSectionName);
    if (index == -1) {
      index = 0;
    }
    return (AnimMontage->GetSectionLength(index) / InPlayRate);
  }
  return 0.f;
}

AActor *AACFCharacter::GetTarget() const {

    AController* controller = GetController();
    if (controller) {
		UATSBaseTargetComponent* targetContr = controller->FindComponentByClass<UATSBaseTargetComponent>();
        if (targetContr) {
            return targetContr->GetCurrentTarget();
        }
    }
  return nullptr;
}

bool AACFCharacter::IsAlive() const
{
	return GetDamageHandlerComponent()->GetIsAlive(); 
}

AACFWeapon *AACFCharacter::GetCurrentWeapon() const {
  if (EquipmentComp) {
    EquipmentComp->GetCurrentMainWeapon();
  }
  return nullptr;
}

 FGameplayTag AACFCharacter::GetCurrentMoveset() const
 {
	 return GetACFAnimInstance()->GetCurrentMoveset();
 }


UACFAnimInstance *AACFCharacter::GetACFAnimInstance() const {
  return Cast<UACFAnimInstance>(GetMesh()->GetAnimInstance());
}

void AACFCharacter::MulticastPlayAnimMontage_Implementation(
    class UAnimMontage *AnimMontage, float InPlayRate /*= 1.f*/,
    FName StartSectionName /*= NAME_None*/) {
	 PlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);
}

bool AACFCharacter::MulticastPlayAnimMontage_Validate(
    class UAnimMontage *AnimMontage, float InPlayRate /*= 1.f*/,
    FName StartSectionName /* = NAME_None*/) {
  return true;
}

void AACFCharacter::ServerSendPlayMontage_Implementation(
    class UAnimMontage *AnimMontage, float InPlayRate /*= 1.f*/,
    FName StartSectionName /*= NAME_None*/) {
  if (AnimMontage) {
    MulticastPlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);
  } else {
    UE_LOG(LogTemp, Log, TEXT("Invalid Montage"));
  }
}

bool AACFCharacter::ServerSendPlayMontage_Validate(
    class UAnimMontage *AnimMontage, float InPlayRate = 1.f,
    FName StartSectionName = NAME_None) {
  return true;
}

void AACFCharacter::ForceAction(FGameplayTag Action) {
  TriggerAction(Action, EActionPriority::EHighest);
}

void AACFCharacter::TriggerAction(FGameplayTag Action,
                                  EActionPriority Priority) {
  if (ActionsComp) {
    ActionsComp->TriggerAction(Action, Priority);
  }
}

void AACFCharacter::ForceActionByName(FName ActionName) {
  if (ActionsComp) {
    ActionsComp->TriggerActionByName(ActionName, EActionPriority::EHighest);
  }
}

FGameplayTag AACFCharacter::GetCurrentActionState() const {

  if (ActionsComp) {
    return ActionsComp->GetCurrentActionTag();
  }

  return FGameplayTag();
}

EDamageZone AACFCharacter::GetDamageZoneByBoneName(FName BoneName) const {
  const EDamageZone *zone = BoneNameToDamageZoneMap.Find(BoneName);
  if (zone) {
    return *zone;
  }
  return EDamageZone::ENormal;
}

float AACFCharacter::GetWalkSpeed() const {
  if (LocomotionComp)
    return LocomotionComp->GetCharacterMaxSpeedByState(ELocomotionState::EWalk);

  return 0.f;
}

float AACFCharacter::GetJogSpeed() const {
  if (LocomotionComp)
    return LocomotionComp->GetCharacterMaxSpeedByState(ELocomotionState::EJog);

  return 0.f;
}

float AACFCharacter::GetSprintSpeed() const {
  if (LocomotionComp)
    return LocomotionComp->GetCharacterMaxSpeedByState(
        ELocomotionState::ESprint);

  return 0.f;
}

void AACFCharacter::SetStrafeMovement(bool bShouldStrafe) {
  if (LocomotionComp)
    LocomotionComp->SetStrafeMovement(bShouldStrafe);
}

float AACFCharacter::TakeDamage(float Damage, FDamageEvent const &DamageEvent,
                                AController *EventInstigator,
                                AActor *DamageCauser) {
  if (!IsAlive() || bIsImmortal)
    return 0.f;

  float damageReceived = DamageHandlerComp->TakeDamage(this, Damage, DamageEvent, EventInstigator, DamageCauser); 
  
  if (GetLastDamageInfo().HitResponseAction != FGameplayTag()) {
	  ForceAction(GetLastDamageInfo().HitResponseAction);
  }

  return damageReceived;
}

 

void AACFCharacter::OnMovementModeChanged(EMovementMode prevMovementMde,
                                          uint8 PreviousCustomMode /*= 0*/) {
  Super::OnMovementModeChanged(prevMovementMde, PreviousCustomMode);

  if (GetMovementComponent()->IsFalling()) {
    ZFalling = GetActorLocation().Z;
  }
}

void AACFCharacter::Landed(const FHitResult &Hit) {
  Super::Landed(Hit);

  if (ZFalling == -1.f)
    return;

  const float totalFallinDistance = ZFalling - GetActorLocation().Z;
  ZFalling = -1.f;
  const float fallDamage = GetFallDamageFromDistance(totalFallinDistance);
  if (fallDamage > 1.f) {
    FDamageEvent damageFall;
    damageFall.DamageTypeClass = UFallDamageType::StaticClass();
    TakeDamage(fallDamage, damageFall, GetController(), this);
  }
}


void AACFCharacter::OnCharacterDeath_Implementation()
{

}

float AACFCharacter::GetFallDamageFromDistance(float fallDistance) {
  const float fallDamageDist = fallDistance - FallDamageDistanceThreshold;
  if (FallDamageByFallDistance && fallDamageDist > 0) {
    return FallDamageByFallDistance->GetFloatValue(fallDamageDist);
  }
  return 0.f;
}

void AACFCharacter::ActivateDamage(const EDamageActivationType &damageActType,
                                   const TArray<FName>& traceChannels) {
  if (damageActType == EDamageActivationType::EPhysical && CollisionComp) {
	  if (!CollisionComp->IsRegistered()) {
		  CollisionComp->RegisterComponent();
	}


    if (!traceChannels.IsValidIndex(0)) {
      CollisionComp->StartAllTraces();
    }

	else {
		for (const auto& channel : traceChannels) {
			CollisionComp->StartSingleTrace(channel);
		}
	}
  } 
  else if (EquipmentComp) {
    switch (damageActType) {
    case EDamageActivationType::ERight:
      EquipmentComp->SetDamageActivation(true, false);
      break;
    case EDamageActivationType::ELeft:
      EquipmentComp->SetDamageActivation(true, true);
      break;
    case EDamageActivationType::EBoth:
      EquipmentComp->SetDamageActivation(true, true);
      EquipmentComp->SetDamageActivation(true, false);
      break;
    }
  }
}

void AACFCharacter::DeactivateDamage(const EDamageActivationType &damageActType,
	 const TArray<FName>& traceChannels) {
  if (damageActType == EDamageActivationType::EPhysical && CollisionComp) {
    if (!traceChannels.IsValidIndex(0)) {
      CollisionComp->StopAllTraces();

    } else {
	for (const auto& channel :  traceChannels) 
      CollisionComp->StopSingleTrace(channel);
    }

  } else if (EquipmentComp) {
    switch (damageActType) {
    case EDamageActivationType::ERight:
      EquipmentComp->SetDamageActivation(false, false);
      break;
    case EDamageActivationType::ELeft:
      EquipmentComp->SetDamageActivation(false, true);
      break;
    case EDamageActivationType::EBoth:
      EquipmentComp->SetDamageActivation(false, true);
      EquipmentComp->SetDamageActivation(false, false);
      break;
    }
  }
}

bool AACFCharacter::IsMyEnemy(AACFCharacter *target) const {
  if (!target)
    return false;

  if (UACFFunctionLibrary::GetBattleType(GetWorld()) ==
      EBattleType::EEveryonAgainstEveryone)
    return true;
  else {
    return UACFFunctionLibrary::AreEnemyTeams(CombatTeam,
                                              target->GetCombatTeam());
  }
}

float AACFCharacter::GetBaseDamage_Implementation() { return 1.f; }



void AACFCharacter::PostInitializeComponents() {
  Super::PostInitializeComponents();
}

void AACFCharacter::SetGenericTeamId(const FGenericTeamId &InTeamID) {
  /*Super::SetGenericTeamId(InTeamID);*/
  CombatTeam = (ETeam)InTeamID.GetId();
}

FGenericTeamId AACFCharacter::GetGenericTeamId() const {
  return uint8(CombatTeam);
}

void AACFCharacter::TryJump() {
  if (ActionsComp->IsInActionState(
          UACFFunctionLibrary::GetDefaultActionsState())) {
    Jump();
  }
}

void AACFCharacter::HandleAttackHit(FName TraceName,
                                    const FHitResult &HitResult) {
  OnDamageInflicted.Broadcast(Cast<AACFCharacter>(HitResult.Actor));
}


void AACFCharacter::KillCharacter_Implementation( float lifespan)
{
	FGameplayTag healthTag = UACFFunctionLibrary::GetHealthTag();
	float damageToApply = StatisticsComp->GetCurrentValueForStatitstic(healthTag);

	StatisticsComp->ModifyStatistic(healthTag, -damageToApply);
	SetLifeSpan(lifespan);
}

bool AACFCharacter::KillCharacter_Validate(float lifespan)
{
	return true;
}

EDirection AACFCharacter::GetRelativeTargetDirection(const AActor *targetActor) {
  if (!targetActor)
    return EDirection::Front;

  float dotProduct = GetDotProductTo(targetActor);

  if (dotProduct >= 0.5f)
    return EDirection::Front;

  else if (dotProduct <= -0.5f)
    return EDirection::Back;

  FVector dirVectorToReceiver = UKismetMathLibrary::GetDirectionUnitVector(
      GetActorLocation(), targetActor->GetActorLocation());

  float dotProductFromRight = UKismetMathLibrary::Dot_VectorVector(
      GetActorRightVector(), dirVectorToReceiver);

  if (dotProductFromRight >= 0.f)
    return EDirection::Right;
  else
    return EDirection::Left;
}

float AACFCharacter::GetCurrentMaxSpeed() const {
  return GetCharacterMovement()->MaxWalkSpeed;
}


FACFDamageEvent AACFCharacter::GetLastDamageInfo() const {
  return DamageHandlerComp->GetLastDamageInfo();
}
