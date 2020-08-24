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
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool ShouldVisualizeLightLineTrace = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	/*virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;*/
	
	UFUNCTION(BlueprintCallable)
	float CalculateLightReceived(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	TArray<ACustomLight*> GetOverlappingLights(AActor* Target);

private:
	float CalculateLightApplied(AActor* Target, ACustomLight* Light);
};
