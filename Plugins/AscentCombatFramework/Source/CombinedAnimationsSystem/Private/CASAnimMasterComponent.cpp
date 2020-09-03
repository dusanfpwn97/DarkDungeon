// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "CASAnimMasterComponent.h"
#include "GameFramework/Character.h"
#include "CASAnimSlaveComponent.h"
#include "CASTypes.h"
#include "CASSnapperComponent.h"
#include <Animation/AnimInstance.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UCASAnimMasterComponent::UCASAnimMasterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	// ...
}


bool UCASAnimMasterComponent::TryPlayCombinedAnimation( ACharacter* otherCharachter, const FName& combineAnimTag)
{
	if (bIsPlayingCombAnim || !otherCharachter || otherCharachter->IsPendingKill()) {
		return false;
	}

	if (!MasterAnimsConfig) {
		UE_LOG(LogTemp, Warning, TEXT("NO Anim Data Table! -UCASAnimMasterComponent::TryPlayCombinedAnimation "));
		return false;
	}

	FCombinedAnimsMaster* animConfig = MasterAnimsConfig->FindRow<FCombinedAnimsMaster>(combineAnimTag, "Searching Master Anims");
 
 	UCASAnimSlaveComponent* slaveComp = otherCharachter->FindComponentByClass< UCASAnimSlaveComponent>();
	if (!slaveComp || !animConfig) {
		return false;
	}

	if (!slaveComp->CanStartCombinedAnimation(combineAnimTag, GetCharacterOwner()) || !EvaluateCombinedAnim(*animConfig, otherCharachter)) {
		return false;
	}

	

	UCASSnapperComponent* snapComponent = characterOwner->FindComponentByClass< UCASSnapperComponent>();
	if (animConfig->MasterAnimMontage && snapComponent ) {
		currentAnim = FCurrentCombinedAnim(*animConfig, combineAnimTag, otherCharachter);
		if (characterOwner->GetDistanceTo(otherCharachter) >= animConfig->MaxDistanceToStartCombinedAnimation) {
			snapComponent->OnSnapPointReached.AddDynamic(this, &UCASAnimMasterComponent::HandleSnapPointReached);		
			snapComponent->SnapToActor(otherCharachter, SnapSpeed, animConfig->MaxDistanceToStartCombinedAnimation, SnapTimeout);
		}

		StartAnim();

		bIsPlayingCombAnim = true;
		return true;
	}

	return false;
}



// Called when the game starts
void UCASAnimMasterComponent::BeginPlay()
{
	Super::BeginPlay();

	characterOwner = Cast<ACharacter>(GetOwner());
	
}

bool UCASAnimMasterComponent::EvaluateCombinedAnim(const FCombinedAnimsMaster& animConfig, const ACharacter* otherChar) const
{
	return animConfig.MasterAnimMontage != nullptr &&
						  characterOwner->GetDistanceTo(otherChar) <= animConfig.MaxDistanceToStartSnapping &&
		(animConfig.SlaveRequiredDirection == GetCharacterRelativedDirection(otherChar) || animConfig.SlaveRequiredDirection == ERelativeDirection::EAny);
}


void UCASAnimMasterComponent::OnCombinedAnimStarted(const FName& animTag)
{

}

void UCASAnimMasterComponent::OnCombinedAnimEnded(const FName& animTag)
{

}

ERelativeDirection UCASAnimMasterComponent::GetCharacterRelativedDirection(const ACharacter* otherChar) const
{
	if (!otherChar || !characterOwner) {
		return ERelativeDirection::EAny;
	}

	FVector masterRelative = characterOwner->GetActorLocation()
		- otherChar->GetActorLocation();

	FVector relativeNormalized = masterRelative.GetUnsafeNormal();

	float forwardDot = FVector::DotProduct(otherChar->GetActorForwardVector(), relativeNormalized);
	float rightDot = FVector::DotProduct(otherChar->GetActorRightVector(), relativeNormalized);
	if (forwardDot >= 0.707f || rightDot >= 0.707f || rightDot <= -0.707f)
		return  ERelativeDirection::EFrontal;
	else
		return  ERelativeDirection::EOpposite;

}

void UCASAnimMasterComponent::HandleMontageFinished(UAnimMontage* inMontage, bool bInterruptted)
{
	if (currentAnim.MasterAnimConfig.MasterAnimMontage == inMontage) {
		OnCombinedAnimationEnded.Broadcast(currentAnim.AnimTag);
		OnCombinedAnimEnded(currentAnim.AnimTag);
		UAnimInstance* animinst = (characterOwner->GetMesh()->GetAnimInstance());

		if (animinst)
		{
			animinst->OnMontageBlendingOut.RemoveDynamic(this, &UCASAnimMasterComponent::HandleMontageFinished);
		}
		bIsPlayingCombAnim = false;

	}

}

void UCASAnimMasterComponent::HandleSnapPointReached(bool bSuccess)
{
		UCASSnapperComponent* snapComponent = characterOwner->FindComponentByClass< UCASSnapperComponent>();
		if (snapComponent) {
	 		snapComponent->OnSnapPointReached.RemoveDynamic(this, &UCASAnimMasterComponent::HandleSnapPointReached);
		}
}

void UCASAnimMasterComponent::StartAnim()
{
	UAnimInstance* animinst = (characterOwner->GetMesh()->GetAnimInstance());
	if (animinst && currentAnim.AnimSlave && currentAnim.MasterAnimConfig.MasterAnimMontage)
	{
		animinst->OnMontageBlendingOut.AddDynamic(this, &UCASAnimMasterComponent::HandleMontageFinished);
		animinst->Montage_Play(currentAnim.MasterAnimConfig.MasterAnimMontage);

		FRotator rotation = characterOwner->GetActorRotation();
		rotation.Yaw = UKismetMathLibrary::FindLookAtRotation(characterOwner->GetActorLocation(), currentAnim.AnimSlave->GetActorLocation()).Yaw;
		characterOwner->SetActorRotation(rotation);
		StartAnimOnSlave();

		OnCombinedAnimationStarted.Broadcast(currentAnim.AnimTag);
		OnCombinedAnimStarted(currentAnim.AnimTag);
	}
}

void UCASAnimMasterComponent::StartAnimOnSlave()
{
	if (currentAnim.AnimSlave) {
		UCASAnimSlaveComponent* slaveComp = currentAnim.AnimSlave->FindComponentByClass< UCASAnimSlaveComponent>();

		FCombinedAnimsSlave outAnim;
		if (slaveComp->TryGetSlaveAnim(currentAnim.AnimTag, outAnim) && outAnim.MasterAnimMontage) {
			FRotator rotation = currentAnim.AnimSlave->GetActorRotation();

			switch (currentAnim.MasterAnimConfig.SlaveForcedDirection) {
			case ERelativeDirection::EFrontal:
				rotation = UKismetMathLibrary::FindLookAtRotation(currentAnim.AnimSlave->GetActorLocation(), characterOwner->GetActorLocation());
				break;
			case ERelativeDirection::EOpposite:
				rotation = UKismetMathLibrary::FindLookAtRotation(currentAnim.AnimSlave->GetActorLocation(), characterOwner->GetActorLocation()).GetInverse();
				break;
			case ERelativeDirection::EAny:
			default:
				break;
			}

			currentAnim.AnimSlave->SetActorRotation(rotation);
			currentAnim.AnimSlave->PlayAnimMontage(outAnim.MasterAnimMontage);
			slaveComp->OnCombinedAnimationStarted.Broadcast(currentAnim.AnimTag);
		}
		else {
			bIsPlayingCombAnim = false;
		}
	}

}


