// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "CASAnimCondition.h"
#include "CASAnimSlaveComponent.h"
#include <GameFramework/Character.h>


bool UCASAnimCondition::Internal_VerifyCondition( class UCASAnimSlaveComponent* ownerComp, const FName& animTag, const ACharacter* animMaster)
{
	ownerCompoment = ownerComp;
	return VerifyCondition(animTag, animMaster);

};

UWorld* UCASAnimCondition::GetWorld() const
{
	
	return ownerCompoment ? ownerCompoment->GetWorld() : nullptr;
}