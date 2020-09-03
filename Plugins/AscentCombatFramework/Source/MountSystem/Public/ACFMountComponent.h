// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include "ACFAnimPointsManagerComponent.h"
#include "ACFMountComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMountedStateChanged, bool, inIsMounted);


UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class MOUNTSYSTEM_API UACFMountComponent : public UACFAnimPointsManagerComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFMountComponent();

	friend class UACFRiderComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FName MountPointSocket;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FName DefaultDismountPoint;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	TMap<FGameplayTag, FGameplayTag> ActionsToBeRetriggeredToRider;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	bool bIsPlayerCompanion = true;   

public:	

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StartMount(class ACharacter* inRider);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StopMount(const FName& dismountPoint = NAME_None);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FName GetMountPoint() const{
		return MountPointSocket;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	FTransform GetMountPointTransform() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	class UACFAnimationPointComponent* GetDismountPoint(const FName& dismountPoint = NAME_None) const;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnMountedStateChanged OnMountedStateChanged;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool IsMounted() const {
		return bIsMounted;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class ACharacter* GetRider() const {
		return rider;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class ACharacter* GetMountOwner() const {
		return GetCharacterOwner();
	}


	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool CanBeMounted() const {
		return !rider;
	}
	/*Inventory of this character*/
	UPROPERTY(SaveGame, Replicated, ReplicatedUsing = OnRep_IsMounted)
	bool bIsMounted = false;
private: 

	UFUNCTION()
	void HandleActionTriggered(FGameplayTag ActionState, EActionPriority Priority);

	UFUNCTION()
	void OnRep_IsMounted();

	class ACharacter* rider;

	void SetMounted(bool inMounted);
	
	void SetRider(ACharacter* inRider) {
		rider = inRider;
	}
		
};
