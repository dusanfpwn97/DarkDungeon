// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CCMLookAtPointComponent.generated.h"


UCLASS(ClassGroup = (CCM), Blueprintable, meta = (BlueprintSpawnableComponent))
class CINEMATICCAMERAMANAGER_API UCCMLookAtPointComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCCMLookAtPointComponent();

	/*Returns a target point actor used for tracking*/
	UFUNCTION(BlueprintCallable, Category = CCM)
	class ATargetPoint* GetTargetPoint();

	UFUNCTION(BlueprintPure, Category = CCM)
	FORCEINLINE FName GetPointName() const {
		return PointName;
	}

protected:

	UPROPERTY(EditDefaultsOnly, Category = CCM)
	FName PointName;

private: 
		
	UPROPERTY()
	class ATargetPoint* targetPoint;

		
};
