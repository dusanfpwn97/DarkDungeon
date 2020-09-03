// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CASTypes.h"
#include "CASAnimSlaveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBINEDANIMATIONSSYSTEM_API UCASAnimSlaveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCASAnimSlaveComponent();

	/*Returns True if an animation with the provided tags exists in the DB*/
	UFUNCTION(BlueprintCallable, Category = CAS)
	bool SupportsAnimation(const FName& animTag) const;

	/*Returns True if the owner supports the animTag provided and
	all conditions are verified*/
	UFUNCTION(BlueprintCallable, Category = CAS)
	bool CanStartCombinedAnimation(const FName& animTag, const class ACharacter* animMaster);

	/*Returns as outParam the quested animation*/
	UFUNCTION(BlueprintCallable, Category = CAS)
	bool TryGetSlaveAnim(const FName& animTag, FCombinedAnimsSlave& outSlave) const;

	UFUNCTION(BlueprintPure, Category = CAS)
	FORCEINLINE class ACharacter* GetCharacterOwner() const {
		return characterOwner;
	}

	UPROPERTY(BlueprintAssignable, Category = CAS)
	FOnCombinedAnimationStarted OnCombinedAnimationStarted;

	UPROPERTY(BlueprintAssignable, Category = CAS)
	FOnCombinedAnimationEnded OnCombinedAnimationEnded;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = CAS)
	class UDataTable* SlaveAnimations;


	UPROPERTY(EditDefaultsOnly, Instanced, Category = CAS)
	TArray<class UCASAnimCondition*> AnimStartingConditions;

private: 

	bool VerifyConditions(const FName& animTag, const class ACharacter* animMaster) ;

	class ACharacter* characterOwner;
		
};
