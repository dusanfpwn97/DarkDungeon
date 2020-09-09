// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "CustomLight.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "CharBase.generated.h"

UCLASS()
class DARKGAME_API ACharBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharBase();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float AdditionalLightIntensity = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(Server, Reliable)
		void ServerCalculateLightReceived();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool ShouldCalculateLightReceived = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool ShouldVisualizeLightReceivedTrace = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float UpdateTimeCalculateLightReceived = 0.1f;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:


	UFUNCTION(BlueprintCallable)
		TArray<ACustomLight*> ServerGetOverlappingLights(AActor* Target);

	UFUNCTION(BlueprintImplementableEvent)
		void OnCalculationForLightCalled(float LightReceived);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetLastReceivedLightIntensity();

	UFUNCTION(BlueprintCallable)
		float CalculateLightApplied(AActor* Target, ACustomLight* LightThatApplies);

	UFUNCTION(BlueprintCallable)
		void ServerStartCalculatingLightReceived();

	UFUNCTION(BlueprintCallable)
		void ServerStopCalculatingLightReceived();
private:

	UPROPERTY()
		FTimerHandle CalculateLightReceivedTimerHandle;

	UPROPERTY(Replicated)
		float LastReceivedLightIntensity = 0;

};
