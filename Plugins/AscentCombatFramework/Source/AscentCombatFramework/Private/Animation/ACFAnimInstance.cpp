// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Animation/ACFAnimInstance.h"
#include "Actors/ACFCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "Components/ACFLocomotionComponent.h"
#include "Components/ACFActionsManagerComponent.h"
#include "Animation/ACFAnimset.h"
#include <TimerManager.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Game/ACFFunctionLibrary.h"
#include "Components/ACFEffectsManagerComponent.h"
#include <Animation/AimOffsetBlendSpace1D.h>




void UACFAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	SetReferences();

	FACFMoveset* nextMov = Movesets.Find(UACFFunctionLibrary::GetMovesetTypeTagRoot());
	if (nextMov)
	{
		CurrentMoveset = *nextMov;
		bCanUseAdditive = CurrentMoveset.AdditiveBlendspace->IsValidLowLevel();
	}
	currentOverlayTag = UACFFunctionLibrary::GetAnimationOverlayTagRoot();
	SetAnimationOverlay(currentOverlayTag);
	bIsMoving = false;
}

void UACFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ACFCharacter && MovementComp && LocomotionComp)//&& CurrentAnimset)
	{
		if (bUpdateSpeed) {
			Velocity = ACFCharacter->GetVelocity();
			Speed = Velocity.Size();
			NormalizedSpeed = Speed / LocomotionComp->GetCharacterMaxSpeed();
			bIsAccelerating = MovementComp->GetCurrentAcceleration().Size() > 0;
			bIsMoving = !FMath::IsNearlyZero(NormalizedSpeed, IsMovingSpeedThreshold);
		}

	
		Rotation = ACFCharacter->GetActorRotation();	
		Direction = CalculateDirection(Velocity, Rotation);

		// Check if the play is falling?
		bIsInAir = MovementComp->IsFalling();
		// Check if the player try to move?


		if (LocomotionComp->bCanAim)
		{
			UpdateAimOffset(DeltaSeconds);
		}

		if (!FMath::IsNearlyEqual(BlendingAlpha, LocomotionComp->targetAlpha, .001f))
		{
			BlendingAlpha = FMath::FInterpTo(BlendingAlpha, LocomotionComp->targetAlpha, DeltaSeconds, AdditiveInterpSpeed);
		}

		UpdateTurningRate(DeltaSeconds);

		UpdateLocomotion();

		switch (LocomotionComp->reproductionType)
		{
		case EMontageReproductionType::ECurveOverrideSpeed:
			OverrideSpeed();
			break;
		case EMontageReproductionType::ECurveSnapsOnTarget:
			Snap(DeltaSeconds);
			break;
		case EMontageReproductionType::ECurveOverrideSpeedAndDirection:
			OverrideSpeedAndDirection();
			break;
		default:
			break;
		}

		if (LocomotionComp->bForceSpeedToForward && !bIsInAir)
		{
			const FVector forward = ACFCharacter->GetActorForwardVector()  * Speed;

			MovementComp->Velocity = FMath::VInterpTo(Velocity, forward, DeltaSeconds, LocomotionComp->SpeedToForwardInterpRate);
		}
	}

}

void UACFAnimInstance::OverrideSpeedAndDirection()
{
	FVector overrideVelocity = overrideDirection * GetCurveValue(SpeedCurveName) * AnimationCurvesScalingFactor;
	MovementComp->Velocity = FVector(overrideVelocity.X, overrideVelocity.Y, MovementComp->Velocity.Z);
}

void UACFAnimInstance::StartOverrideSpeedAnDirection(const FVector& direction)
{
	if (direction == FVector::ZeroVector) {
		overrideDirection = ACFCharacter->GetActorForwardVector();
	}
	
	overrideDirection = direction.GetSafeNormal();
	LocomotionComp->SetMontageReprodutionType(EMontageReproductionType::ECurveOverrideSpeedAndDirection);
}

void UACFAnimInstance::StopOverrideSpeedAnDirection()
{
	LocomotionComp->SetMontageReprodutionType(EMontageReproductionType::ERootMotion);
}

void UACFAnimInstance::GetMovesetActionsByMoveType(const FGameplayTag& tag, FActionsMap& outActions)
{
	FActionsMap* outMov = MovesetsActions.Find(tag);
	if (outMov) {
		outActions = *outMov;
	}

}

void UACFAnimInstance::PlayFootstepFX() const
{
	if (ACFCharacter)
	{
		UACFEffectsManagerComponent* effectsMan = ACFCharacter->FindComponentByClass<UACFEffectsManagerComponent>();
		if (effectsMan)
		{
			effectsMan->TriggerFootstepFX();
		}
	}

}

void UACFAnimInstance::SetUpdateVelocity(bool bUpdateVelocity)
{
	bUpdateSpeed = bUpdateVelocity;

	if (!bUpdateSpeed) {
		Speed = 0.f;
		NormalizedSpeed = 0.f;
		bIsAccelerating = false;
	}
}

void UACFAnimInstance::StartOverrideSpeed()
{

	LocomotionComp->SetMontageReprodutionType(EMontageReproductionType::ECurveOverrideSpeed);
}

void UACFAnimInstance::StopOverrideSpeed()
{

	LocomotionComp->SetMontageReprodutionType(EMontageReproductionType::ERootMotion);
}

void UACFAnimInstance::SetAnimationOverlay(const FGameplayTag& overlayTag)
{
	FAnimationOverlay* overlay = Overlays.Find(overlayTag);
	if (overlay && overlay->Animation) {
		currentOverlayTag = overlayTag;
		CurrentOverlay.BlendingAlpha = overlay->BlendingAlpha;
		CurrentOverlay.Animation = overlay->Animation;
	}
	else {
		RemoveOverlay();
	}
}

void UACFAnimInstance::RemoveOverlay()
{
	CurrentOverlay.BlendingAlpha = 0.f;
	currentOverlayTag = FGameplayTag();
}

/*
void UACFAnimInstance::StartBlendSnapshotPose()
{
	
	bIsBlendingPose = true;
// 	FTimerHandle TimerHandle;
// 	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UACFAnimInstance::HandleSnapshotBlendEnd, BlendPoseDuration, false);
}

void UACFAnimInstance::StopBlendSnapshotPose()
{
	SavePoseSnapshot(SnapshotPoseName);
	bIsBlendingPose = false;
}*/

void UACFAnimInstance::OverrideSpeed()
{
	float speed = GetCurveValue(SpeedCurveName);
	MovementComp->Velocity = ACFCharacter->GetActorForwardVector() * speed * AnimationCurvesScalingFactor;
}



void UACFAnimInstance::FinishCurrentAction()
{
	if (ACFCharacter)
	{
		UACFActionsManagerComponent* _amc = ACFCharacter->FindComponentByClass<UACFActionsManagerComponent>();
		if (_amc)
		{
			_amc->FreeAction();
		}
	}
}

void UACFAnimInstance::SetReferences()
{
	ACFCharacter = Cast<AACFCharacter>(TryGetPawnOwner());
	if (ACFCharacter)
	{
		ACFCharacter->OnMovementTypeChanged.RemoveDynamic(this, &UACFAnimInstance::HandleMovementTypeChanged);
		ACFCharacter->OnMovementTypeChanged.AddDynamic(this, &UACFAnimInstance::HandleMovementTypeChanged);
		MovementComp = ACFCharacter->GetCharacterMovement();
		LocomotionComp = ACFCharacter->GetLocomotionComponent();
		
	}
}


void UACFAnimInstance::UpdateTurningRate(float _deltatime)
{
	FRotator _delta = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, PreviousRotation);
	float _turn = _delta.Yaw;

	TurnRate = FMath::FInterpTo(TurnRate, _turn, _deltatime, TurnSmoothingRate);
	PreviousRotation = Rotation;
	return;
}


void UACFAnimInstance::HandleMovementTypeChanged(FGameplayTag Movetype)
{

	SwitchMoveset(Movetype);

}

void UACFAnimInstance::SwitchMoveset(FGameplayTag Movetype)
{
	FACFMoveset* nextMov = Movesets.Find(Movetype);
	UWorld* world = GetWorld();
	if (world && nextMov)
	{
		currentMovesetTag = Movetype;
		nextMoveset = *nextMov;
		bIsSwitchingMoveset = true;
		bCanUseAdditive = false;
		FTimerHandle TimerHandle;
		world->GetTimerManager().SetTimer(TimerHandle, this, &UACFAnimInstance::OnMovesetSwitchingFinished, MovesetSwitchTime, false);
	}
}

void UACFAnimInstance::OnMovesetSwitchingFinished()
{
	//CurrentAnimset = NextAnimset;
	CurrentMoveset = nextMoveset;
	bCanUseAdditive = CurrentMoveset.AdditiveBlendspace->IsValidLowLevel();
	bIsSwitchingMoveset = false;
	
}

void UACFAnimInstance::UpdateLocomotion( )
{
	if (MovementComp && !MovementComp->IsFalling() && LocomotionComp && LocomotionComp->reproductionType == EMontageReproductionType::ERootMotion)
	{
		if (MovementComp->GetGroundMovementMode() == MOVE_Walking) {
			for (int i = 0; i < LocomotionComp->LocomotionStates.Num() - 1; i++)
			{
				if (FMath::IsNearlyZero(Speed) && LocomotionComp->currentLocomotionState != ELocomotionState::EIdle) {
					LocomotionComp->HandleStateChanged(ELocomotionState::EIdle);
				}

				else if (LocomotionComp->LocomotionStates[i + 1].State != LocomotionComp->currentLocomotionState &&
					Speed > LocomotionComp->LocomotionStates[i].MaxStateSpeed + 5.f &&
					Speed <= LocomotionComp->LocomotionStates[i + 1].MaxStateSpeed + 5.f)
				{
					LocomotionComp->HandleStateChanged(LocomotionComp->LocomotionStates[i + 1].State);
				}

			}

			if (LocomotionComp->currentLocomotionState == ELocomotionState::ESprint)
			{
				if (FMath::Abs(Direction) > LocomotionComp->SprintDirectionCone)
				{
					LocomotionComp->SetLocomotionState(ELocomotionState::EJog);
				}
			}
		}
		else {
			LocomotionComp->SetLocomotionState(ELocomotionState::EIdle);
		}
	}
}

void UACFAnimInstance::UpdateAimOffset(float deltatime)
{
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(ACFCharacter->GetControlRotation(), Rotation);

	float yawtarget = delta.Yaw;
	float pitchtarget = delta.Pitch;
	if (yawtarget >= 135.0f)
	{
		if (yawtarget < 90)
			yawtarget = -yawtarget;
		else
			yawtarget = yawtarget - 180.0f;

		pitchtarget = -pitchtarget;
	}
	else if (yawtarget <= -135.0f)
	{
		if (yawtarget > -90)
			yawtarget = -yawtarget;
		else
			yawtarget = yawtarget + 180.0f;

		pitchtarget = -pitchtarget;
	}

	AimOffsetYaw = FMath::FInterpTo(AimOffsetYaw, yawtarget, deltatime, AimOffsetSmoothingFactor);
	AimOffsetPitch = FMath::FInterpTo(AimOffsetPitch, pitchtarget, deltatime, AimOffsetSmoothingFactor);

}


void UACFAnimInstance::Snap(float deltaTime)
{
	float speed = GetCurveValue(SpeedCurveName);

	FVector direction = LocomotionComp->CalculateCurrentSnapDirection(deltaTime);
	
	MovementComp->Velocity = direction  * speed * LocomotionComp->CalculateCurrentSnapMultiplier() * AnimationCurvesScalingFactor;
}



