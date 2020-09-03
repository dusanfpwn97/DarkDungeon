// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Animation/ACFNotifyFX.h"
#include <Components/SkeletalMeshComponent.h>
#include "Components/ACFActionsManagerComponent.h"
#include "Actors/ACFCharacter.h"
#include <Animation/AnimSequenceBase.h>




void UACFNotifyFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AACFCharacter* character = Cast< AACFCharacter>(MeshComp->GetOwner());
	
		if (character)
		{
			UACFActionsManagerComponent* amc = character->GetActionsComponent();
			if (amc)
			{
				amc->PlayCurrentActionFX();
			}
		}
	}
}
