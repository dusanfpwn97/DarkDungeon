// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/Components/ACFGroupAIComponent.h"
#include "Game/ACFDamageType.h"
#include "ACFCompanionGroupAIComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class ASCENTCOMBATFRAMEWORK_API UACFCompanionGroupAIComponent : public UACFGroupAIComponent
{
	GENERATED_BODY()

public: 

	UACFCompanionGroupAIComponent() {};

	UFUNCTION(BlueprintCallable, Category = ACF)
	void AddExpToTheGroup(int32 Exp);

protected: 

	virtual void SetReferences() override;

	virtual void BeginPlay() override;
private: 

	UPROPERTY()
	class AController* contr;
	
	UFUNCTION()
	void HandleLeadGetHit(const FACFDamageEvent& damage);

	UFUNCTION()
	void HandleLeadHits(class AActor* damaged);

	UFUNCTION()
	void HandlePossessedCharacterChanged(const class AACFCharacter* _char);
};
