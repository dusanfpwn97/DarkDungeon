// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Animation/ACFActivateDamageNotifyState.h"
#include <Components/SkeletalMeshComponent.h>
#include "Actors/ACFCharacter.h"

void UACFActivateDamageNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp) {

		AACFCharacter* CharacterOwner = Cast< AACFCharacter>(MeshComp->GetOwner());
		if (CharacterOwner) {
			CharacterOwner->ActivateDamage(DamageToActivate, TraceChannels);
		}
	}

}

void UACFActivateDamageNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp) {

		AACFCharacter* CharacterOwner = Cast< AACFCharacter>(MeshComp->GetOwner());
		if (CharacterOwner) {
			CharacterOwner->DeactivateDamage(DamageToActivate, TraceChannels);
		}
	}
}
