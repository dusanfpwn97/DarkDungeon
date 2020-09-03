// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ACFBaseAction.h"
#include "Game/ACFDamageType.h"
#include "ACFHitAction.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFHitAction : public UACFBaseAction
{
	GENERATED_BODY()

		UACFHitAction();

protected: 

	virtual void OnActionStarted_Implementation() override;
	virtual void OnActionEnded_Implementation() override;

	virtual FName GetMontageSectionName_Implementation() override;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	TMap<EDirection, FName> HitDirectionToMontageSectionMap;

	FACFDamageEvent damageReceived;
};
