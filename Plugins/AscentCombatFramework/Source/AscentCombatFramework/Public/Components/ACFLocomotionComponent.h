// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Engine/DataTable.h>
#include "Game/ACFData.h"
#include "ARSStatisticsData.h"
#include "Game/ACFData.h"
#include "ACFLocomotionComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocomotionStateChanged, ELocomotionState, State);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimingStateChanged, bool, bIsAiming);


USTRUCT(BlueprintType)
struct FACFLocomotionState : public FTableRowBase
{
	GENERATED_BODY()

	FACFLocomotionState() {};

	FACFLocomotionState(ELocomotionState _state, float _maxStateSpeed) 
	{
		State = _state;
		MaxStateSpeed = _maxStateSpeed;
	};

public: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	ELocomotionState State;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	float MaxStateSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	FName CameraMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	FAttributesSetModifier StateModifier;

	FORCEINLINE	bool	operator<(const FACFLocomotionState &Other) const
	{
		return this->MaxStateSpeed < Other.MaxStateSpeed;
	}

	FORCEINLINE	bool	operator==(const FACFLocomotionState &Other) const
	{
		return this->State == Other.State;
	}

	FORCEINLINE	bool	operator!=(const ELocomotionState &Other) const
	{
		return this->State != Other;
	}

	FORCEINLINE	bool	operator==(const ELocomotionState &Other) const
	{
		return this->State == Other;
	}

	FORCEINLINE	bool	operator!=(const FACFLocomotionState &Other) const
	{
		return this->State != Other.State;
	}

};

UCLASS(Blueprintable, ClassGroup = (ACF), meta = (BlueprintSpawnableComponent))
class ASCENTCOMBATFRAMEWORK_API UACFLocomotionComponent : public UActorComponent
 {
	GENERATED_BODY()

public:

	UACFLocomotionComponent();

	friend class UACFAnimInstance;

// 	UPROPERTY(BlueprintAssignable, Category = ACF)
// 	FOnAimingStateChanged OnAimingStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnLocomotionStateChanged OnLocomotionStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnLocomotionStateChanged OnTargetLocomotionStateChanged;

	UFUNCTION(BlueprintPure, Category = ACF)
	float GetCharacterMaxSpeed() const { return CharacterMaxSpeed; }

	UFUNCTION(BlueprintPure, Category = ACF)
	bool IsCharacterStrafing() const { return bisStrafing; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE ELocomotionState GetCurrentLocomotionState() const { return currentLocomotionState; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	float GetCharacterMaxSpeedByState(ELocomotionState State);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void SetStrafeMovement(bool binShouldStrafe);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void AccelerateToNextState();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void BrakeToPreviousState();

// 	UFUNCTION( BlueprintCallable, Category = ACF)
// 	void TryToAim(bool bShouldAim);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void TurnAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void MoveForwardLocal(float Value);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void TurnAtRateLocal(float Value);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void MoveRight(float Value);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE float GetMoveForwardAxis() const { return MoveForwardAxis; }
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE float GetMoveRightAxis() const { return MoveRightAxis; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FVector GetWorldMovementInputVector();

	UFUNCTION(BlueprintPure, Category = ACF)
	FVector GetCameraMovementInputVector();
// 
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE ELocomotionState GetTargetLocomotionState() const { return targetLocomotionState.State; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	FORCEINLINE float GetDefaultRotationRate() { return RotationRate; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FVector GetCurrentInputVector();

	UFUNCTION(BlueprintPure, Category = ACF)
	EDirection GetCurrentInputDirection();

	UFUNCTION(BlueprintCallable, Category = ACF)
	void ResetToDefaultLocomotionState();
	/*Sets the target locomotion State*/
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void SetLocomotionState(ELocomotionState State);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void SetMontageReprodutionType(EMontageReproductionType repType);

	/*Sets the target locomotion State*/
 	UFUNCTION(BlueprintCallable, Category = ACF)
	void StartSnapping(const FSnapConfiguration& snapConfiguration);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StopSnapping();

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StartOverrideSpeedAndDirection(const FVector& direction);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StopOverrideSpeedAndDirection();

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StartBlendingAdditiveAnimation();

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StopBlendingAdditiveAnimation();

	UFUNCTION(BlueprintPure, Category = ACF)
	float CalculateCurrentSnapMultiplier();

	UFUNCTION(BlueprintPure, Category = ACF)
	FVector CalculateCurrentSnapDirection(float deltaTime);
	
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE	EMontageReproductionType GetMontageReprodutionType()  const { return reproductionType; }


	/**Indicates if this character can Move */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Movement")
	bool bCanMove = true;

 protected:

	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Controller")
	float TurnRate = 75;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Controller")
	float LookUpRate = 75;

	/**Indicates if this character has Aim Offset Logic */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Controller")
	bool bCanAim = true;

	/**Indicates the default locomtionstate*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Movement")
	ELocomotionState DefaultState = ELocomotionState::EJog;

	/**Indicates max speed for each locomtionstate*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Movement")
	TArray<FACFLocomotionState> LocomotionStates;

	/**Indicates if this character follows control rotation and strafes*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Movement")
	bool bShouldStrafe = false;

	/**Indicates the actual rotation rates of the character*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Movement")
	float RotationRate = 180.f;


	/*Indicates the max angular distance from the cone that allows your character to sprint
	(you cannot sprint backward)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Movement")
	float SprintDirectionCone = 10.f;

	/*Indicates if the actual velocity is constantly forced to the forward of the actor, 
	necessary for locomotion system of creatures that cannot strafe, like an horse*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Quadruped Movement")
	bool bForceSpeedToForward = false;

	/*Indicates the speed in which the speed interpolates to the forward if bForceSpeedToForward is
	set to true*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Quadruped Movement")
	float SpeedToForwardInterpRate = 2.f;

	/*When your AnimReproductionType is set to SnapToTarget, this struct 
	identifies the anim ideal distance and the maximum multiplier applied to the animation
	speed to magneticly snap on the target*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Snap")
	FSnapConfiguration defaultSnapConfiguration;

private:

	float CharacterMaxSpeed;
	float MoveForwardAxis;
	float MoveRightAxis;

	void UpdateCharacterMaxSpeed();

	UPROPERTY(Replicated)
	float targetAlpha = 0.f;

	UPROPERTY(Replicated)
	EMontageReproductionType reproductionType = EMontageReproductionType::ERootMotion;

	UPROPERTY()
	class UCharacterMovementComponent* MovementComponent;

	UPROPERTY()
	class AACFCharacter* Character;

	UPROPERTY(ReplicatedUsing = OnRep_LocomotionState)
	FACFLocomotionState targetLocomotionState;

//	UPROPERTY(ReplicatedUsing = OnRep_LocomotionState)
	ELocomotionState currentLocomotionState;

	UPROPERTY(Replicated)
	FSnapConfiguration currentSnapConfiguration;

	UPROPERTY(Replicated)
	float snapMultiplier = 1.0;

	bool bisStrafing;

	UFUNCTION()
	void OnRep_LocomotionState();

	UFUNCTION()
	void HandleStateChanged(ELocomotionState newState);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void ClientsShouldStrafe(bool binShouldStrafe);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void ClientsSetMontageReproduction(EMontageReproductionType repType);

	UPROPERTY()		
	bool bIsSprinting = false;

	void UpdateMaxSpeed();

};
