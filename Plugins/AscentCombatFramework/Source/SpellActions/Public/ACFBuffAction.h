// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ACFBaseAction.h"
#include "ARSStatisticsData.h"
#include "ACFBuffAction.generated.h"

/**
 * 
 */
UCLASS()
class SPELLACTIONS_API UACFBuffAction : public UACFBaseAction
{
	GENERATED_BODY()
	
protected: 

    virtual void OnNotablePointReached_Implementation() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = ACF )
	FTimedAttributeSetModifier BuffToApply;
};
