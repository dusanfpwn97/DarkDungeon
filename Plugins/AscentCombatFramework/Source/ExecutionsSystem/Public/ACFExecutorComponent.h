// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include "Game/ACFData.h"
#include "CASAnimMasterComponent.h"
#include "ACFExecutorComponent.generated.h"




USTRUCT(BlueprintType)
struct FExecution
{
	GENERATED_BODY()

public:

	/*The animation COmbined To Be Played*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF")
	FName AnimationTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF")
	FName CameraEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF")
	bool bIsFatal = true;

};

USTRUCT(BlueprintType)
struct FExecutionArray
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF")

		TArray< FExecution> ExecutionTag;

};


USTRUCT(BlueprintType)
struct FExecutions
{
	GENERATED_BODY()

public:

	/*The executable animations categorized by weapontype*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF")
	TMap<FGameplayTag, FExecutionArray> ExecutionsByWeaponType;

};


UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class EXECUTIONSSYSTEM_API UACFExecutorComponent : public UCASAnimMasterComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFExecutorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

 	UPROPERTY(EditDefaultsOnly, Category = ACF)
 	TMap<ERelativeDirection, FExecutions> ExecutionsByDirectionAndWeaponType;

	virtual void OnCombinedAnimStarted(const FName& animTag) override;
	virtual void OnCombinedAnimEnded(const FName& animTag) override;

public:	


	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryExecuteCharacter(  class ACharacter* target);

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryExecuteCurrentTarget();

	UFUNCTION(BlueprintCallable, Category = ACF)
	FName GetBestExecutionTagForCharacter( class ACharacter* target);
private:

	bool TryGetBestExecutionTag(const FGameplayTag& weaponTag, ERelativeDirection dir, FExecution& outExec);

	void SetCharacterActionsLock(ACharacter* target, bool lockstatus);

	FExecution currentBestExec;

};
