// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "CCMSequenceNotifyState.h"
#include <Kismet/GameplayStatics.h>
#include <Components/SkeletalMeshComponent.h>
#include "CCMPlayerCameraManager.h"
#include "CCMCameraFunctionLibrary.h"

void UCCMSequenceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (bActivateOnlyIfOwningPlayer &&
		(MeshComp->GetOwner()) != (AActor*)UGameplayStatics::GetPlayerCharacter(MeshComp, 0)){
		return;
	}

	ACCMPlayerCameraManager* cameraMan = UCCMCameraFunctionLibrary::GetLocalCinematicCameraManager(MeshComp);
	if (cameraMan) {
		cameraMan->AddSequenceEventModifier(SequenceModifier);
	}
}

void UCCMSequenceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (bActivateOnlyIfOwningPlayer &&
		(MeshComp->GetOwner()) != (AActor*)UGameplayStatics::GetPlayerCharacter(MeshComp, 0)) {
		return;
	}

	ACCMPlayerCameraManager* cameraMan = UCCMCameraFunctionLibrary::GetLocalCinematicCameraManager(MeshComp);
	if (cameraMan) {
		cameraMan->RemoveSequenceEventModifier(SequenceModifier);
	}

}
