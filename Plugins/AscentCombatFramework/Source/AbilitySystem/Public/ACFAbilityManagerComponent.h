// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include "ACFAbilityManagerComponent.generated.h"



UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UACFAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "ACF | Default Values")
	class UDataTable* AbilitiesDB;

};
   