// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameplayTagContainer.h>
#include "Game/ACFData.h"
#include "Interfaces/ACFSavableInterface.h"
#include <GameFramework/Pawn.h>
#include <GenericTeamAgentInterface.h>
#include "ACFAIGroupSpawner.generated.h"



UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFAIGroupSpawner : public APawn, public IACFSavableInterface,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:	

	AACFAIGroupSpawner();


// 	friend class AACFAIController;
// 	friend class UACFGroupAIComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class USplineComponent* SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFGroupAIComponent* AIGroupComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	bool bSpawnOnBeginPlay = false;


	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

public:

	UFUNCTION(BlueprintCallable, Category = ACF)
	FVector GetPatrolPoint(int32 patrolIndex);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class USplineComponent* GetSplineComponent() const { return SplineComponent; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFGroupAIComponent* GetAIGroupComponent() const { return AIGroupComponent; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  ETeam GetCombatTeam() const { return CombatTeam; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool GetAgentWithIndex(int32 index, FAIAgentsInfo& outAgent) const;
	
	UFUNCTION(BlueprintCallable, Category = ACF)
	AACFCharacter* GetAgentNearestTo(const FVector& location);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorLoaded();
	virtual void OnActorLoaded_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorSaved();
	virtual void OnActorSaved_Implementation() override;

private:
	UPROPERTY()
	ETeam CombatTeam = ETeam::EEnemiesTeam;
};
