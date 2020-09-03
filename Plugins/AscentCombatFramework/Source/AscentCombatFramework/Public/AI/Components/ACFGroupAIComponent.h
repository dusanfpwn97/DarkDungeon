// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>
#include <Components/SplineComponent.h>
#include "Game/ACFData.h"
#include <Components/SceneComponent.h>
#include "ACFGroupAIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAgentDeath, int32, agentIndex);

UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class ASCENTCOMBATFRAMEWORK_API UACFGroupAIComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFGroupAIComponent();

protected:
	UPROPERTY(SaveGame)
	bool bAlreadySpawned = false;
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetReferences();

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	bool bInBattle;

	/*Should use group or agent perception?*/
	UPROPERTY(EditAnywhere, Category = ACF)
	bool bOverrideAgentPerception = true;

	UPROPERTY(EditAnywhere, Category = ACF)
	bool bOverrideAgentTeam = true;

	UPROPERTY(EditAnywhere, Category = ACF)
	FVector2D spawnOffset;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = ACF)
	class AActor* groupLead;

	UPROPERTY(SaveGame, Replicated)
	TArray<FAIAgentsInfo> AICharactersInfo;
public:

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnAgentDeath OnAgentDeath;

	UFUNCTION()
	virtual void OnChildDeath(int _childIndex);

	void Internal_RemoveAgentAtIndex(int _childIndex);

	UFUNCTION(BlueprintCallable, Category = ACF)
	class AACFCharacter* GetAgentNearestTo(const FVector& location);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool IsInBattle() const { return bInBattle; }

	UFUNCTION(BlueprintPure, Category = ACF)
		ETeam GetCombatTeam() const {
		return CombatTeam;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE int GetGroupSize() const { return AICharactersInfo.Num(); }

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool RemoveAgentFromGroup(AACFCharacter* character);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void GetGroupAgents(TArray<FAIAgentsInfo>& outAgents) const { outAgents = AICharactersInfo; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetInBattle(bool inBattle, AActor* newTarget);

	void SetEnemyGroup(UACFGroupAIComponent* inEnemyGroup);

	UFUNCTION(BlueprintPure, Category = ACF)
	class UACFGroupAIComponent* GetEnemyGroup() const { return enemyGroup;}

	UFUNCTION(BlueprintCallable, Category = ACF)
	class AACFCharacter* RequestNewTarget(const AACFAIController* requestSender);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void SendCommandToCompanions(FGameplayTag command);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void SpawnGroup();

	void InitAgents();

	UFUNCTION(BlueprintCallable, Category = ACF)
	uint8 AddAgentToGroup(float inXOffset, float inYOffset, TSubclassOf<AACFCharacter> ClassToSpawn);

	UFUNCTION( BlueprintCallable, Category = ACF)
	uint8 AddExistingCharacterToGroup(AACFCharacter* character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TArray<FAISpawnInfo> AIToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	ETeam CombatTeam = ETeam::EEnemiesTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	EAIState DefaultAiState = EAIState::EPatrol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	bool CanSpawnMultitpleTimes = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	uint8 MaxSimultaneousAgents = 10;

	UFUNCTION(BlueprintCallable, Category = ACF)
	FORCEINLINE class USplineComponent* GetSplineComponent() { return GetOwner()->FindComponentByClass<USplineComponent>(); }
private:

	void Internal_SendCommandToAgents(FGameplayTag command);

	UPROPERTY()
	UACFGroupAIComponent* enemyGroup;

	UPROPERTY()
	TArray<int> FormationInfo;

	void Internal_SpawnGroup();	

	void InitAgent(FAIAgentsInfo& agent, int32 childIndex);

	// offset on forward direction
	float xOffset = 0.0f;
	float yOffset = 0.0f;

	float maxGroupWidth = -1, maxGroupLength = -1;

	int childGroupIndex = 0;

	// the first row of current class
	int fi_currClassRowBase = 0;
	float colPadding = 0;
	float rowPadding = 0;


};
