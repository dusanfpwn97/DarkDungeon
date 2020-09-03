// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include "ACFAnimPointsManagerComponent.generated.h"


UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class MOUNTSYSTEM_API UACFAnimPointsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFAnimPointsManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = ACF)
	FName GetNearestAnimationPointTag(const FVector& location) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	class UACFAnimationPointComponent* GetNearestAnimationPoint(const FVector& location) const;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class ACharacter* GetCharacterOwner() const {
		return characterOwner;
	}
private:
	class ACharacter* characterOwner;

		
};
