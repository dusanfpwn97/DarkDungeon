// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Animation/ACFPlayImpactFXNotify.h"
#include <Components/SkeletalMeshComponent.h>
#include "Components/ACFEffectsManagerComponent.h"

void UACFPlayImpactFXNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp) {
		UACFEffectsManagerComponent* effectsComp = MeshComp->GetOwner()->FindComponentByClass<UACFEffectsManagerComponent>();

		if (effectsComp) {
			effectsComp->PlayHitReactionEffect(HitReaction, DamageReceivedType, SpawnLocation, SocketOrBoneLocation);
		}
	}

}
