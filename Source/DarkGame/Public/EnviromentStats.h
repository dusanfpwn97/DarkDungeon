// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomLight.h"
#include "EnviromentStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKGAME_API UEnviromentStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnviromentStats();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ShouldCalculateLightReceived = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ShouldVisualizeLightReceivedTrace = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UpdateTimeCalculateLightReceived = 0.1f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//
public:	
	// Called every frame. I've commented it out because we might use it in the future
	/*virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;*/

	UFUNCTION()
	void CalculateLightReceived();

	UFUNCTION(BlueprintCallable)
	TArray<ACustomLight*> GetOverlappingLights(AActor* Target);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCalculationForLightCalled(float LightReceived);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetLastReceivedLightIntensity();

	UFUNCTION(BlueprintCallable)
	float CalculateLightApplied(AActor* Target, ACustomLight* LightThatApplies);

	UFUNCTION(BlueprintCallable)
	void StartCalculatingLightReceived();

	UFUNCTION(BlueprintCallable)
	void StopCalculatingLightReceived();
private:

	UPROPERTY()
	FTimerHandle CalculateLightReceivedTimerHandle;

	UPROPERTY()
	float LastReceivedLightIntensity = 0;

};
