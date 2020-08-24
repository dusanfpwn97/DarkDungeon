// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "CustomLight.generated.h"

UCLASS()
class DARKGAME_API ACustomLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomLight();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UPointLightComponent* PointLight;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USphereComponent* LightCollider;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USceneComponent* SceneComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

private:
	void UpdateLightColliderRadius();


};
