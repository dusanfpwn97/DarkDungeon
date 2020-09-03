// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include <GameplayTagContainer.h>
#include "ACFAnimset.h"
#include "Actions/ACFBaseAction.h"
#include "Game/ACFData.h"
#include "ACFAnimInstance.generated.h"

/**
 * 
 */


UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFAnimInstance : public UAnimInstance
   {
	GENERATED_BODY()
	

public: 

	friend class AACFCharacter;
	friend class UACFLocomotionComponent;
	friend class UACFActionsManagerComponent;
	/* begin play */
	virtual void NativeInitializeAnimation() override;
	/* tick */
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE float GetDirection(){ return Direction; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE float GetNormalizedSpeed() const { return NormalizedSpeed; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE float GetTurnRate() const { return TurnRate; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	void GetMovesetActionsByMoveType(const FGameplayTag& tag, FActionsMap& outActions);

 	UFUNCTION(BlueprintCallable, Category = ACF)
 	void PlayFootstepFX() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetUpdateVelocity(bool bUpdateVelocity);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetAnimationOverlay(const FGameplayTag& overlayTag);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetMovesetActionsTag(const FGameplayTag& actionsTag) {
		currentMovesetActionsTag = actionsTag;
	}

	UFUNCTION(BlueprintCallable, Category = ACF)
	void RemoveOverlay();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool IsVelocityOverrideByAnim() const { return bVelocityOverrideByAnim; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetCurrentMoveset() const { return currentMovesetTag; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetCurrentMovesetActionsTag() const { return currentMovesetActionsTag; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetCurrentOverlay() const { return currentOverlayTag; }

// 	UFUNCTION(BlueprintPure, Category = ACF)
// 	FORCEINLINE FName GetSnapshotPoseName() const { return SnapshotPoseName; }


// 	void StartBlendSnapshotPose();
// 
// 	void StopBlendSnapshotPose();

protected:

	UFUNCTION(BlueprintCallable, Category = ACF)
	void FinishCurrentAction();

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FACFMoveset nextMoveset;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FGameplayTag currentMovesetActionsTag;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FGameplayTag currentMovesetTag;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FGameplayTag currentOverlayTag;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bCanUseAdditive = false;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FACFMoveset CurrentMoveset;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FAnimationOverlay CurrentOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float AdditiveAnimBlendTime = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float MovesetSwitchTime = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float IsMovingSpeedThreshold = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TMap<FGameplayTag, FActionState> CommonActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TMap<FGameplayTag, FActionsMap> MovesetsActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TMap<FGameplayTag, FACFMoveset> Movesets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TMap<FGameplayTag, FAnimationOverlay> Overlays;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bIsSwitchingMoveset = false;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	float Speed; 

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	float NormalizedSpeed;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FRotator Rotation;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bIsMoving;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bUpdateSpeed = true;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bIsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class AACFCharacter* ACFCharacter;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class UCharacterMovementComponent* MovementComp;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class UACFLocomotionComponent* LocomotionComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ACF)
	float AimOffsetSmoothingFactor = 3.f;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	float AimOffsetYaw;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	float AimOffsetPitch;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = ACF)
	float AimOffsetAlpha = 1.f;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	float TurnRate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ACF)
	float TurnSmoothingRate = 8.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ACF)
	float AnimationCurvesScalingFactor = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FName SpeedCurveName = "Speed";

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bVelocityOverrideByAnim;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	float AdditiveInterpSpeed = 1.f;

// 	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ACF | Ragdoll")
// 	FName SnapshotPoseName = "RagdollPose";

// 	UPROPERTY(EditDefaultsOnly, Category = "ACF | Ragdoll")
// 	float BlendPoseDuration = 0.4f;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	float BlendingAlpha = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bIsBlendingPose = false;

private: 
	UPROPERTY()
		bool  bOverrideVelocitybyVector = false;

	UPROPERTY()
		FVector overrideDirection;

	/** Update the Yaw and Pitch for head track based on Control rotation between mesh forward vector*/
	void UpdateAimOffset(float deltatime);

	void Snap(float deltaTime);
	void SetReferences();
	void OverrideSpeedAndDirection();

	void OverrideSpeed();

	void UpdateTurningRate(float _deltatime);

	FRotator PreviousRotation;

	UFUNCTION()
	void HandleMovementTypeChanged(FGameplayTag Movetype);

	void SwitchMoveset(FGameplayTag Movetype);

	void OnMovesetSwitchingFinished();

	void UpdateLocomotion();

	void StartOverrideSpeed();

	void StopOverrideSpeed();

	void StartOverrideSpeedAnDirection(const FVector& direction);

	void StopOverrideSpeedAnDirection();
	
};
