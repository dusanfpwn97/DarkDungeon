// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLight.h"

// Sets default values
ACustomLight::ACustomLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneComponent"));
	RootComponent = SceneComponent;
	PointLight = CreateDefaultSubobject<UPointLightComponent>(FName("PointLight"));
	LightCollider = CreateDefaultSubobject<USphereComponent>(FName("LightCollider"));
	PointLight->SetupAttachment(SceneComponent);
	LightCollider->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ACustomLight::BeginPlay()
{
	Super::BeginPlay();
}

void ACustomLight::OnConstruction(const FTransform & Transform)
{
	// This updates the collider radius to be equal to the radius of light the point light
	UpdateLightColliderRadius();
}

void ACustomLight::UpdateLightColliderRadius()
{
	LightCollider->SetSphereRadius(PointLight->AttenuationRadius, false);
}
