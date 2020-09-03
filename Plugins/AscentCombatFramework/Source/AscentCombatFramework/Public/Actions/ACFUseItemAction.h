// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ACFBaseAction.h"
#include "ACFUseItemAction.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFUseItemAction : public UACFBaseAction
{
	GENERATED_BODY()

protected: 

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FGameplayTag ItemSlot;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	bool bShouldUseIfInterrupted = false;

	bool bSuccess = false;

	virtual void OnActionStarted_Implementation() override;

	virtual void OnNotablePointReached_Implementation() override;

	virtual void OnActionEnded_Implementation() override;

	virtual bool CanExecuteAction_Implementation(class AACFCharacter* owner) override;

private: 
	void UseItem();
	
};
