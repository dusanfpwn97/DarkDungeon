// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ACFEquippableItem.h"
#include "ACFAccessory.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFAccessory : public AACFEquippableItem
{
	GENERATED_BODY()

public:

	AACFAccessory();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FName GetAttachmentSocket() const {
		return AttachmentSocket;
	}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	FName AttachmentSocket;
	
};
