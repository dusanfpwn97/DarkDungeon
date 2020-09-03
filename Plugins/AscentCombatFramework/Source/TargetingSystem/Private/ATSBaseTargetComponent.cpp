// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ATSBaseTargetComponent.h"
#include <GameFramework/Controller.h>


// Sets default values for this component's properties
UATSBaseTargetComponent::UATSBaseTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}



bool UATSBaseTargetComponent::IsTargetInSight() const
{
	AController* contr = Cast< AController>(GetOwner());
	if (contr) {
		return contr->LineOfSightTo(CurrentTarget);
	}
	return false;
}


