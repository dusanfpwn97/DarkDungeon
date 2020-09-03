// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include "ACFRiderComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRidingStateChanged, bool, bIsRiding);

UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class MOUNTSYSTEM_API UACFRiderComponent : public UActorComponent
{
	GENERATED_BODY()

		

public:	
	// Sets default values for this component's properties
	UACFRiderComponent();

	UPROPERTY(BlueprintAssignable)
	FOnRidingStateChanged OnRidingStateChanged;

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool IsRiding() const {
		return bIsRiding;
	}

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void StartMount(class UACFMountComponent* mount);


	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = ACF)
	void StartDismount(const FName& dismountPoint = NAME_None);


	UFUNCTION(BlueprintPure, Category = ACF)
	class ACharacter* GetMount() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = ACF)
	bool bPossessMount = false;

	UPROPERTY(SaveGame, Replicated, ReplicatedUsing = OnRep_IsRiding)
	bool bIsRiding = false;
private: 

	void FinishMount();
	void FinishDismount(const FName& dismountPoint = NAME_None);
	UPROPERTY(Replicated)
	class UACFMountComponent* Mount;

	UPROPERTY()
	class ACharacter* charOwner;

	UFUNCTION()
	void HandleSnapPointReached(bool bSuccess);
	
	UFUNCTION()
	void OnRep_IsRiding();

	bool bIsSnapping = false;

	void Internal_Ride(bool inIsRiding);

	void Internal_AttachToMount();

	void Internal_Mount();

};
