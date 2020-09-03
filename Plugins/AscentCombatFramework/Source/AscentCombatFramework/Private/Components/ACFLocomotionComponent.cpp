// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Components/ACFLocomotionComponent.h"
#include "Actors/ACFCharacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Animation/ACFAnimInstance.h"
#include "Game/ACFFunctionLibrary.h"
#include <GameFramework/Pawn.h>
#include <GameFramework/Controller.h>
#include "Components/ACFActionsManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include <Engine/World.h>
#include <TimerManager.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Game/ACFDamageType.h"
#include <Animation/AnimEnums.h>
#include "ARSStatisticsComponent.h"
#include "CCMCameraFunctionLibrary.h"
#include "CASSnapperComponent.h"


UACFLocomotionComponent::UACFLocomotionComponent()
{
	bEditableWhenInherited = true;
	PrimaryComponentTick.bCanEverTick = false;
	
 	LocomotionStates.Add(FACFLocomotionState( ELocomotionState::EIdle, 0.f));
	LocomotionStates.Add(FACFLocomotionState(ELocomotionState::EWalk, 180.f));
	LocomotionStates.Add(FACFLocomotionState(ELocomotionState::EJog, 350.f));
	LocomotionStates.Add(FACFLocomotionState(ELocomotionState::ESprint, 550.f));

	SetIsReplicatedByDefault(true);
	currentLocomotionState = ELocomotionState::EIdle;
}

void UACFLocomotionComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UACFLocomotionComponent, targetLocomotionState);
	DOREPLIFETIME(UACFLocomotionComponent, reproductionType);
	DOREPLIFETIME(UACFLocomotionComponent, targetAlpha);
	DOREPLIFETIME(UACFLocomotionComponent, currentSnapConfiguration);
	DOREPLIFETIME(UACFLocomotionComponent, snapMultiplier);
}

void UACFLocomotionComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AACFCharacter>(GetOwner());
	if (Character)
	{
		MovementComponent = Character->FindComponentByClass<UCharacterMovementComponent>();
		if (MovementComponent)
		{			
			MovementComponent->RotationRate.Yaw = RotationRate;
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Component not found in Character"));
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner not found!"));
	}

	UCameraComponent * Camera = Character->FindComponentByClass<UCameraComponent>();
	USpringArmComponent* CameraBoom = Character->FindComponentByClass<USpringArmComponent>();

	if (Camera && CameraBoom)
	{
		Camera->bUsePawnControlRotation = false;
		CameraBoom->bUsePawnControlRotation = true;
	}

// 	if (UKismetSystemLibrary::IsServer(this))
// 	{
		SetStrafeMovement(bShouldStrafe);
		SetLocomotionState(DefaultState);
/*	}*/

	UpdateCharacterMaxSpeed();

	LocomotionStates.Sort();

}



void UACFLocomotionComponent::SetLocomotionState_Implementation(ELocomotionState State)
{
	FACFLocomotionState* _state = LocomotionStates.FindByKey(State);
	
	if (_state && MovementComponent)
	{		
		targetLocomotionState = *(_state);
		MovementComponent->MaxWalkSpeed = GetCharacterMaxSpeedByState(State);
		targetLocomotionState.MaxStateSpeed = GetCharacterMaxSpeedByState(State);
		OnTargetLocomotionStateChanged.Broadcast(State);

		//OnLocomotionStateChanged.Broadcast(State);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Locomotion State inexistent"));
	}
}

bool UACFLocomotionComponent::SetLocomotionState_Validate(ELocomotionState State)
{
	return true;
}


float UACFLocomotionComponent::GetCharacterMaxSpeedByState(ELocomotionState State)
{
	FACFLocomotionState* _state = LocomotionStates.FindByKey(State);
	if (_state)
	{
		return _state->MaxStateSpeed;
	}
	return 0.0f;
}

void UACFLocomotionComponent::UpdateCharacterMaxSpeed()
{
	float maxspeed = 0.0f;
	for (FACFLocomotionState state : LocomotionStates)
	{
		if (state.MaxStateSpeed >= maxspeed)
		{
			maxspeed = state.MaxStateSpeed;
		}
	}
	CharacterMaxSpeed = maxspeed;
}

void UACFLocomotionComponent::OnRep_LocomotionState()
{
	if (!MovementComponent)
	{
		Character = Cast<AACFCharacter>(GetOwner());
		if (Character)
		{
			MovementComponent = Character->FindComponentByClass<UCharacterMovementComponent>();
		}
	}
	MovementComponent->MaxWalkSpeed = GetCharacterMaxSpeedByState(targetLocomotionState.State);
	targetLocomotionState.MaxStateSpeed = GetCharacterMaxSpeedByState(targetLocomotionState.State);
		
}



void UACFLocomotionComponent::HandleStateChanged(ELocomotionState newState)
{

	if (currentLocomotionState == newState) {
		return;
	}

	FACFLocomotionState* oldState = LocomotionStates.FindByKey(currentLocomotionState);
	FACFLocomotionState* nextState = LocomotionStates.FindByKey(newState);

	if (oldState && nextState && Character) {
		UARSStatisticsComponent* statComp = Character->GetStatisticsComponent();

		statComp->RemoveAttributeSetModifier(oldState->StateModifier);
		statComp->AddAttributeSetModifier(nextState->StateModifier);

		if (Character == UACFFunctionLibrary::GetLocalACFPlayerCharacter(this)) {
			UCCMCameraFunctionLibrary::StopCameraEvent(this, oldState->CameraMovement);
			UCCMCameraFunctionLibrary::TriggerCameraEvent(this, nextState->CameraMovement);

		}
	}
	currentLocomotionState = newState;
	OnLocomotionStateChanged.Broadcast(newState);
}

void UACFLocomotionComponent::ClientsShouldStrafe_Implementation(bool binShouldStrafe)
{
  	if (Character)
	{
		bisStrafing = binShouldStrafe;
		MovementComponent->bOrientRotationToMovement = !bisStrafing; // Character moves in the direction of input..
		MovementComponent->bUseControllerDesiredRotation = bisStrafing;
	}
}

bool UACFLocomotionComponent::ClientsShouldStrafe_Validate(bool binShouldStrafe)
{
	return true;
}

void UACFLocomotionComponent::SetStrafeMovement_Implementation(bool shouldStrafe)
{
	if (Character)
	{
		bisStrafing = shouldStrafe;
		MovementComponent->bOrientRotationToMovement = !bisStrafing; // Character moves in the direction of input..
		MovementComponent->bUseControllerDesiredRotation = bisStrafing;
	}
	ClientsShouldStrafe(shouldStrafe);
}

bool UACFLocomotionComponent::SetStrafeMovement_Validate(bool shouldStrafe)
{
	return true;
}


void UACFLocomotionComponent::AccelerateToNextState_Implementation()
{
	LocomotionStates.Sort();

	int32 actualindex = LocomotionStates.IndexOfByKey(currentLocomotionState);

	if (LocomotionStates.IsValidIndex(actualindex + 1))
	{
		SetLocomotionState(LocomotionStates[actualindex + 1].State);
	}
}

bool UACFLocomotionComponent::AccelerateToNextState_Validate()
{
	return true;
}

void UACFLocomotionComponent::BrakeToPreviousState_Implementation()
{
	LocomotionStates.Sort();
	
	int32 actualindex = LocomotionStates.IndexOfByKey(currentLocomotionState);

	if (LocomotionStates.IsValidIndex(actualindex - 1))
	{
		SetLocomotionState(LocomotionStates[actualindex - 1].State);
	}
}

bool UACFLocomotionComponent::BrakeToPreviousState_Validate()
{
	return true;
}

// void UACFLocomotionComponent::TryToAim(bool bShouldAim)
// {
// 	if (!bShouldStrafe)
// 	{
// 		SetStrafeMovement(bShouldAim);
// 	}
// 	OnAimingStateChanged.Broadcast(bShouldAim);
// }

void UACFLocomotionComponent::TurnAtRate(float Rate)
{
	if (Character)
	{
		Character->AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
	}

}

void UACFLocomotionComponent::LookUpAtRate(float Rate)
{
	if (Character)
	{
		Character->AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void UACFLocomotionComponent::MoveForwardLocal(float Value)
{
	if (!bCanMove)
		return;
	// catch the forward axis

	MoveForwardAxis = Value;

	if (Character && Character->Controller && (MoveForwardAxis != 0.0f))
	{
		// get forward vector
		const FVector Direction = Character->GetActorForwardVector();

		Character->AddMovementInput(Direction, Value);
	}
}

void UACFLocomotionComponent::TurnAtRateLocal(float Value)
{
	if (Value != 0 && Character)
	{
		const FRotator YawRotation(0, Value, 0);
		Character->AddActorLocalRotation(YawRotation);
	}
		
}

void UACFLocomotionComponent::MoveForward(float Value)
{

	if (!bCanMove)
		return;
	// catch the forward axis
		
	MoveForwardAxis = Value;

	if (Character && Character->Controller && (MoveForwardAxis != 0.0f))
	{
		
		// find out which way is forward
		const FRotator Rotation = Character->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		Character->AddMovementInput(Direction, Value);
	}
}

void UACFLocomotionComponent::MoveRight(float Value)
{
	if (!bCanMove)
		return;

	// Catch the right axis 

		MoveRightAxis = Value;
		
	if (Character && Character->Controller && (MoveRightAxis != 0.0f))
	{
			
		// find out which way is right
		const FRotator Rotation = Character->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		Character->AddMovementInput(Direction, Value);
	}
}

FVector UACFLocomotionComponent::GetWorldMovementInputVector()
{
	if (Character)
	{
		FVector localDir = FVector(MoveForwardAxis, MoveRightAxis, 0.f);
		
		FVector WorlDir = Character->GetActorForwardVector().Rotation().RotateVector(localDir);
		WorlDir.Normalize();
		return WorlDir;
	}
	return FVector();
}

FVector UACFLocomotionComponent::GetCameraMovementInputVector()
{
	if (Character)
	{
		FVector localDir = FVector(MoveForwardAxis, MoveRightAxis, 0.f);
		FVector WorlDir = Character->GetController()->GetControlRotation().RotateVector(localDir);
		WorlDir.Normalize();
		return WorlDir;
	}
	return FVector();
}

void UACFLocomotionComponent::StartBlendingAdditiveAnimation()
{
	targetAlpha = 1.0f;
}

void UACFLocomotionComponent::StopBlendingAdditiveAnimation()
{
	targetAlpha = 0.0f;
}

float UACFLocomotionComponent::CalculateCurrentSnapMultiplier()
{
	if (Character && currentSnapConfiguration.target) {
		float distance = FVector::Distance(Character->GetActorLocation(), currentSnapConfiguration.target->GetActorLocation());

		if (distance <= currentSnapConfiguration.maxSnapMultiplier * currentSnapConfiguration.preferredDistance)
		{
			snapMultiplier = distance / currentSnapConfiguration.preferredDistance;
		}

		return snapMultiplier;
	}
	return 1.f;
}

FVector UACFLocomotionComponent::CalculateCurrentSnapDirection(float deltaTime)
{	
	if (currentSnapConfiguration.target)
	{
		FVector targetDir =   currentSnapConfiguration.target->GetActorLocation() - Character->GetActorLocation();
		return FMath::VInterpTo(Character->GetActorForwardVector(), targetDir, MovementComponent->RotationRate.Yaw * currentSnapConfiguration.RotationRateSnapMult, deltaTime).GetSafeNormal();
	}
	return Character->GetActorForwardVector();
}



void UACFLocomotionComponent::StartOverrideSpeedAndDirection(const FVector& direction)
{
	if (Character && Character->GetACFAnimInstance())
	{
		Character->GetACFAnimInstance()->StartOverrideSpeedAnDirection(direction);
	}
}

void UACFLocomotionComponent::StopOverrideSpeedAndDirection()
{
	if (Character && Character->GetACFAnimInstance())
	{
		Character->GetACFAnimInstance()->StopOverrideSpeedAnDirection();
	}
}

void UACFLocomotionComponent::SetMontageReprodutionType_Implementation(EMontageReproductionType repType)
{
	ClientsSetMontageReproduction(repType);
}

bool UACFLocomotionComponent::SetMontageReprodutionType_Validate(EMontageReproductionType repType)
{
	return true;
}

void UACFLocomotionComponent::ClientsSetMontageReproduction_Implementation(EMontageReproductionType repType)
{
	if (MovementComponent)
	{
		MovementComponent->RotationRate.Yaw = GetDefaultRotationRate();
	}
	reproductionType = repType;

	ERootMotionMode::Type rootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;

	switch (repType)
	{
	case EMontageReproductionType::ERootMotion:
		rootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;
		break;
	case EMontageReproductionType::ECurveOverrideSpeed:
	case EMontageReproductionType::ECurveSnapsOnTarget:
	case EMontageReproductionType::ECurveOverrideSpeedAndDirection:
		rootMotionMode = ERootMotionMode::IgnoreRootMotion;
		break;
	default:
		break;
	}

	if (Character && Character->GetACFAnimInstance()) {
		Character->GetACFAnimInstance()->SetRootMotionMode(rootMotionMode);
	}
}

bool UACFLocomotionComponent::ClientsSetMontageReproduction_Validate(EMontageReproductionType repType)
{
	return true;
}

FVector UACFLocomotionComponent::GetCurrentInputVector()
{
	FVector dir = FVector(MoveForwardAxis, MoveRightAxis, 0.f);
	dir.Normalize();
	return dir ;
}

EDirection UACFLocomotionComponent::GetCurrentInputDirection()
{
	if (Character)
	{
		const FVector direction = GetCurrentInputVector();

		if (FMath::Abs(direction.X) > FMath::Abs(direction.Y))
		{
			if (direction.X > 0)
			{
				return EDirection::Front;
			}
			else
			{
				return EDirection::Back;
			}
		}
		else
		{
			if (direction.Y > 0)
			{
				return EDirection::Right;
			}
			else
			{
				return EDirection::Left;
			}
		}

	}
	return EDirection::Front;
}


void UACFLocomotionComponent::ResetToDefaultLocomotionState()
{
	SetLocomotionState(DefaultState);
}

void UACFLocomotionComponent::StartSnapping(const FSnapConfiguration& snapConfiguration) 
{
	if (snapConfiguration.target && Character)
	{
		currentSnapConfiguration = snapConfiguration;
		SetMontageReprodutionType(EMontageReproductionType::ECurveSnapsOnTarget);
	}
}

void UACFLocomotionComponent::StopSnapping()
{
	currentSnapConfiguration = defaultSnapConfiguration;
	snapMultiplier = 1.0f;
}



