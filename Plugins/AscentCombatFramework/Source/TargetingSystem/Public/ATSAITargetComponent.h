// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ATSBaseTargetComponent.h"
#include "ATSAITargetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (ATS), Blueprintable, meta = (BlueprintSpawnableComponent))
class TARGETINGSYSTEM_API UATSAITargetComponent : public UATSBaseTargetComponent
{
	GENERATED_BODY()
	
public: 


	virtual	void SetCurrentTarget(class AActor* target) override;

};
