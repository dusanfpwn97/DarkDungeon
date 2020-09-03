// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <GameFramework/PlayerController.h>
#include "Actors/ACFCharacter.h"
#include "Interfaces/ACFSavableInterface.h"
#include <GameplayTagContainer.h>
#include "ACFPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPossessedCharacterChanged, const class AACFCharacter*, character);

UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFPlayerController : public APlayerController, public IACFSavableInterface
{
	GENERATED_BODY()


public: 

	AACFPlayerController();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class AACFCharacter* GetPossessedACFCharacter() const { return PossessedCharacter; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SwitchToNearestCompanion(float blendTime = 0.5f );

	UFUNCTION(BlueprintCallable, Category = ACF)
	void TriggerAction(const FGameplayTag& action, EActionPriority priority = EActionPriority::ELow);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void SwitchPossessionToCharacer(class AACFCharacter* inCharacter, float blendTime = 0.5f );

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE ETeam GetCombatTeam()const { return CombatTeam; }

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnPossessedCharacterChanged OnPossessedCharacterChanged;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorLoaded();
	virtual void OnActorLoaded_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorSaved();
	virtual void OnActorSaved_Implementation() override;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFCompanionGroupAIComponent* GetCompanionsComponent() const { return CompanionsComponent; }


protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

	void EnableCharacterComponents(bool bEnabled);

	virtual void OnUnPossess() override;

	UPROPERTY(SaveGame, BlueprintReadOnly, Replicated, Category = ACF)
	class AACFCharacter* PossessedCharacter;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class UACFCompanionGroupAIComponent* CompanionsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	ETeam CombatTeam = ETeam::EHeroesTeam;


private: 

	UFUNCTION()
	void Internal_SwitchPossessionTo(AACFCharacter* inCharacter);

	
};
