// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "CASAnimSlaveComponent.h"
#include "CASTypes.h"
#include "CASAnimCondition.h"
#include <GameFramework/Character.h>

// Sets default values for this component's properties
UCASAnimSlaveComponent::UCASAnimSlaveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


bool UCASAnimSlaveComponent::SupportsAnimation(const FName& animTag) const
{
	if (SlaveAnimations) {
		FCombinedAnimsSlave* anim = SlaveAnimations->FindRow< FCombinedAnimsSlave>(animTag, "SearchingA Anims...");
		return (anim) && (anim->MasterAnimMontage);
	}
	return false;
}

bool UCASAnimSlaveComponent::CanStartCombinedAnimation(const FName& animTag, const ACharacter* animMaster)
{
	return SupportsAnimation( animTag) && VerifyConditions(animTag, animMaster);
	
}

bool UCASAnimSlaveComponent::TryGetSlaveAnim(const FName& animTag, FCombinedAnimsSlave& outSlave) const
{
	if (SlaveAnimations) {
		FCombinedAnimsSlave* anim = SlaveAnimations->FindRow< FCombinedAnimsSlave>(animTag, "SearchingA Anims...");
		if ((anim) && (anim->MasterAnimMontage)) {
			outSlave = *anim;
			return true;
		}	
	}
	return false;
}

bool UCASAnimSlaveComponent::VerifyConditions(const FName& animTag, const ACharacter* animMaster)
{
	
	for (const auto condition : AnimStartingConditions) {
		if (!condition->Internal_VerifyCondition(this, animTag,  animMaster)) {
			return false;
		}
	}
	return true;
}

// Called when the game starts
void UCASAnimSlaveComponent::BeginPlay()
{
	Super::BeginPlay();

	characterOwner = Cast<ACharacter>(GetOwner());
	
}


