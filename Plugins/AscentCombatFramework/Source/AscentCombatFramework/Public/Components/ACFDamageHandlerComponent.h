// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/ACFDamageType.h"
#include "Game/ACFDamageCalculation.h"
#include "Actors/ACFCharacter.h"
#include "ACFDamageHandlerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);



UCLASS(Blueprintable, ClassGroup=(ACF), meta=(BlueprintSpawnableComponent) )
class ASCENTCOMBATFRAMEWORK_API UACFDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFDamageHandlerComponent();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE	FACFDamageEvent GetLastDamageInfo() const {
		return LastDamageReceived;
	}

	/*assign the correct collision channel to the damage meshes from the team*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	void InitializeDamageCollisions(ETeam combatTeam);

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnDamageReceived OnDamageReceived;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnCharacterDeath OnOwnerDeath;


public:	


	float TakeDamage(class AActor* damageReceiver, float Damage, FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		class AActor* DamageCauser);


	UFUNCTION(BlueprintPure, Category = ACF)
		bool GetIsAlive() const {
		return bIsAlive;
	}

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	bool bAutoDestroyOnDeath = true;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bAutoDestroyOnDeath == true"), Category = ACF)
	float ActorLifeSpanOnDeath = 5.f;


// 	UFUNCTION(BlueprintCallable, Category = ACF)
// 	bool TryRevive(float healthPercentage = 5.f);

private:

	void ConstructDamageReceived(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
			FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
			TSubclassOf<UDamageType> DamageType, AActor* DamageCauser);


	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = ACF)
	void ClientsReceiveDamage(const FACFDamageEvent& damageEvent);

	UPROPERTY()
	class UACFDamageCalculation* DamageCalculator;

	UPROPERTY()
	FACFDamageEvent LastDamageReceived;

	UFUNCTION()
	void HandleStatReachedZero(FGameplayTag stat);
	
	void AssignCollisionChannels(ECollisionChannel channel);

	UPROPERTY(Replicated)
	bool bIsAlive = true;

	
};
