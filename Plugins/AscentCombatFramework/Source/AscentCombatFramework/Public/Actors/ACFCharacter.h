// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ACFActionsManagerComponent.h"
#include "Game/ACFDamageType.h"
#include "Interfaces/ACFInteractableInterface.h"
#include "Animation/ACFAnimset.h"
#include <GenericTeamAgentInterface.h>
#include "Game/ACFData.h"
#include "Interfaces/ACFSavableInterface.h"
#include "Game/ACFDamageType.h"
#include "Components/ACFEquipmentComponent.h"
#include "Animation/ACFAnimset.h"
#include "Interfaces/ACFEntityInterface.h"
#include "ACFCharacter.generated.h"


#define ECC_ACFHeroesChannel  ECollisionChannel::ECC_GameTraceChannel1
#define ECC_ACFEnemiesChannel  ECollisionChannel::ECC_GameTraceChannel2

 enum class EActionPriority : uint8;
 enum class EDamageZone : uint8;


 DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterFullyInitialized);

 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageReceived, const FACFDamageEvent&, damageReceived);

 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageInflicted,  class AActor*, damageReceiver);

 

 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementTypeChanged, FGameplayTag, MovementType);

 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatTypeChanged, ECombatType, CombatType);


UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFCharacter : public ACharacter,
	public IGenericTeamAgentInterface, public IACFSavableInterface, public IACFEntityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACFCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void PostInitProperties() override;

	virtual void PreInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	


	virtual void OnMovementModeChanged(EMovementMode prevMovementMde, uint8 PreviousCustomMode = 0) override;

	virtual void Landed(const FHitResult& Hit) override;

	/*Name Displayed in UI*/
	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FText CharacterName ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACF)
	TMap<FName, EDamageZone> BoneNameToDamageZoneMap;


	UPROPERTY(EditAnywhere, config, Category = ACF)
	float FallDamageDistanceThreshold = 200.f;

	UPROPERTY(EditAnywhere, Category = ACF)
	class UCurveFloat* FallDamageByFallDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFActionsManagerComponent* ActionsComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFLocomotionComponent* LocomotionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UARSStatisticsComponent* StatisticsComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACMCollisionManagerComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFEquipmentComponent* EquipmentComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFEffectsManagerComponent* EffetsComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFDamageHandlerComponent* DamageHandlerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFRagdollComponent* RagdollComp;

	UPROPERTY()
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UAudioComponent* AudioComp;


	UFUNCTION(BlueprintNativeEvent, Category = ACF)
	float GetBaseDamage();
	virtual float GetBaseDamage_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = ACF)
	void OnCharacterDeath();
	virtual void OnCharacterDeath_Implementation();

	UFUNCTION(BlueprintCallable, Category = ACF)
	float GetFallDamageFromDistance(float fallDistance);
	
	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = ACF)
	void MulticastPlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	ECombatType CombatType = ECombatType::EUnarmed;
	
	UPROPERTY(EditDefaultsOnly, Category = ACF)
	EDeathType DeathType = EDeathType::EGoRagdoll;

	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	/*virtual  ETeamAttitude::Type GetTeamAttitudeTowards(class AActor const &)const;*/


	UFUNCTION(BlueprintCallable, Category = ACF)
	void TryJump();

private: 
	bool bInitialized = false;

	float ZFalling = -1.f;

	UFUNCTION()
	void HandleDamageReceived( const FACFDamageEvent& damageReceived);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void ServerSendPlayMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

	UFUNCTION()
	void SetupCollisionManager();

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void SwitchMovementType(FGameplayTag moveType);

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = ACF)
	void ClientsSwitchMovetype(FGameplayTag moveType);

	void Internal_SwitchMovetype(FGameplayTag moveType);

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = ACF)
	void ClientsOnCharacterDeath();


	UFUNCTION()
	void HandleCharacterDeath();

	UFUNCTION()
	void InitializeCharacter();

	UFUNCTION()
	void HandleEquipmentChanged(const FEquipment& equipment);

	UPROPERTY(Replicated)
	ETeam CombatTeam = ETeam::EHeroesTeam;

public:

	UFUNCTION(BlueprintCallable, Category = ACF)
    void AssignTeam(ETeam team);

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//SAVABLE INTERFACE
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorLoaded();
	virtual void OnActorLoaded_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorSaved();
	virtual void OnActorSaved_Implementation() override;

	//acf entity interface
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		ETeam GetEntityCombatTeam();
	virtual ETeam GetEntityCombatTeam_Implementation() override {
		return GetCombatTeam();
	}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		bool IsEntityAlive();
	virtual bool IsEntityAlive_Implementation() override {
		return IsAlive();
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	ETeam GetCombatTeam() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool IsMyEnemy(AACFCharacter* target) const;

	UFUNCTION(BlueprintPure, Category = ACF)
	EDeathType GetDeathType() const {
		return DeathType;
	}

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetDeathType(EDeathType inDeathType) {
		DeathType = inDeathType;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE ECollisionChannel GetCollisionChannel() const
	{
		if (CombatTeam == ETeam::EHeroesTeam)	{
			return ECC_ACFHeroesChannel;
		}
		else {
			return ECC_ACFEnemiesChannel;
		}
	}

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnDamageReceived OnDamageReceived;

	UFUNCTION(BlueprintPure, Category = ACF)
	TArray<TEnumAsByte<ECollisionChannel>>  GetEnemiesCollisionChannel() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool IsRanged() const
	{
		return CombatType == ECombatType::ERanged;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	bool CanBeRanged() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnMovementTypeChanged OnMovementTypeChanged;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnCombatTypeChanged OnCombatTypeChanged;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnDamageInflicted OnDamageInflicted;


	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnCharacterFullyInitialized OnCharacterFullyInitialized;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	bool bIsImmortal = false;

	UFUNCTION(BlueprintCallable, Category = ACF)
	EDamageZone GetDamageZoneByBoneName(FName BoneName) const;

	UFUNCTION(BlueprintPure, Category = ACF)
	float GetWalkSpeed() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	float GetJogSpeed() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	float GetSprintSpeed() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	void TriggerAction(FGameplayTag Action, EActionPriority Priority);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void ForceActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void ForceAction(FGameplayTag Action);

	UFUNCTION(BlueprintPure, Category = ACF)
	FGameplayTag GetCurrentActionState() const;

	UFUNCTION( BlueprintCallable, Category = ACF)
	float PlayNetworkedMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

	UFUNCTION(BlueprintPure, Category = ACF)
	AActor* GetTarget() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFLocomotionComponent* GetLocomotionComponent() const { return LocomotionComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFActionsManagerComponent*  GetActionsComponent() const { return ActionsComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UARSStatisticsComponent* GetStatisticsComponent() const { return StatisticsComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFEquipmentComponent* GetEquipmentComponent() const { return EquipmentComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACMCollisionManagerComponent* GetCollisionsComponent() const { return CollisionComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFDamageHandlerComponent* GetDamageHandlerComponent() const { return DamageHandlerComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFRagdollComponent* GetRagdollComponent() const { return RagdollComp; }

	UFUNCTION(BlueprintPure, Category = ACF)
	bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	class AACFWeapon* GetCurrentWeapon() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FText GetCharacterName() const { return CharacterName;} 

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UAudioComponent* GetAudioComp() const { return AudioComp; }


	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE ECombatType GetCombatType() const { return CombatType; }

	UFUNCTION(BlueprintPure, Category = ACF)
	 FGameplayTag GetCurrentMoveset() const; 

	UFUNCTION(BlueprintPure, Category = ACF)
	class UACFAnimInstance* GetACFAnimInstance() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetStrafeMovement(bool bShouldStrafe);

	UFUNCTION(BlueprintCallable, Category = ACF)
	float GetCurrentMaxSpeed() const;
	

	UFUNCTION(BlueprintPure, Category = ACF)
	FACFDamageEvent GetLastDamageInfo() const;

	UFUNCTION()
	void HandleAttackHit(FName TraceName, const FHitResult& HitResult);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool GetIsDead() const { return !IsAlive(); }

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void KillCharacter(float lifeSpan = 2.f);

	UFUNCTION(BlueprintCallable, Category = ACF)
	EDirection GetRelativeTargetDirection(const AActor* targetActor);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void ActivateDamage(const EDamageActivationType& damageActType, const TArray<FName>& traceChannels);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void DeactivateDamage(const EDamageActivationType& damageActType, const TArray<FName>& traceChannels);


};




