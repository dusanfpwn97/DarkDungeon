// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CASTypes.h"
#include "CASAnimMasterComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBINEDANIMATIONSSYSTEM_API UCASAnimMasterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCASAnimMasterComponent();

	/*Tries to play the animation tagged as combineAnimationTag with OtherCharacter and returns wathever this 
	operation is successful*/
	UFUNCTION( BlueprintCallable, Category = CAS)
	bool TryPlayCombinedAnimation( class ACharacter* otherCharachter, const FName& combineAnimTag);

	UFUNCTION(BlueprintPure, Category = CAS)
	FORCEINLINE bool IsPlayingCombinedAnimation() const {
		return bIsPlayingCombAnim;
	}

	UFUNCTION(BlueprintPure, Category = CAS)
	FORCEINLINE ACharacter* GetCharacterOwner() const {
		return characterOwner;
	}

	UFUNCTION(BlueprintPure, Category = CAS)
	FORCEINLINE ACharacter* GetCharacterSlave() const {
		return currentAnim.AnimSlave;
	}

	UPROPERTY(BlueprintAssignable, Category = CAS)
	FOnCombinedAnimationStarted OnCombinedAnimationStarted;

	UPROPERTY(BlueprintAssignable, Category = CAS)
	FOnCombinedAnimationEnded OnCombinedAnimationEnded;

	UFUNCTION(BlueprintCallable, Category = CAS)
	ERelativeDirection GetCharacterRelativedDirection( const ACharacter* otherChar) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = CAS)
	float SnapSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = CAS)
	float SnapTimeout = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = CAS)
	class UDataTable* MasterAnimsConfig;

	virtual bool EvaluateCombinedAnim(const FCombinedAnimsMaster& animConfig, const ACharacter* otherChar) const;

	virtual void OnCombinedAnimStarted(const FName& animTag);
	virtual void OnCombinedAnimEnded(const FName& animTag);

	FCurrentCombinedAnim currentAnim;
private:

	bool bIsPlayingCombAnim = false;

	class ACharacter* characterOwner;


	UFUNCTION()
	void HandleMontageFinished(UAnimMontage* inMontage, bool bInterruptted);

	UFUNCTION()
	void HandleSnapPointReached(bool bSuccess);

	void StartAnim();

	void StartAnimOnSlave();


};
