// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <Components/SceneComponent.h>
#include <GameplayTagContainer.h>
#include "ACFAnimationPointComponent.generated.h"


UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class MOUNTSYSTEM_API UACFAnimationPointComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFAnimationPointComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FName PointTag;

public:	

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FName GetPointTag() const {
		return PointTag;
	}
		
};
