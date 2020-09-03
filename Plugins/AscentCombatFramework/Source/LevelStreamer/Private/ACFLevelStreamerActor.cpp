// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFLevelStreamerActor.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Pawn.h>
#include <Components/StaticMeshComponent.h>
#include <TimerManager.h>

// Sets default values
AACFLevelStreamerActor::AACFLevelStreamerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DistanceLODMesh = CreateDefaultSubobject<UStaticMeshComponent>( "Static Mesh LOD Proxy");

}

// Called when the game starts or when spawned
void AACFLevelStreamerActor::BeginPlay()
{
	Super::BeginPlay();
	DistanceLODMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CheckAndUpdateLevel();
	UWorld* world = GetWorld();
	if (world) {
		world->GetTimerManager().SetTimer(
			timerHandle, this, &AACFLevelStreamerActor::CheckAndUpdateLevel,
			TimeInterval, true);

	}
}
	

void AACFLevelStreamerActor::CheckAndUpdateLevel()
{
	APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (pawn) {
		float distance = GetDistanceTo(pawn); 
		if (distance > MaxDistanceFromPlayer && bIsLevelLoaded) {
			UnloadLevel();
		}
		else if (distance < MaxDistanceFromPlayer && !bIsLevelLoaded) {
			LoadLevel();
		}
	}
}

void AACFLevelStreamerActor::LoadLevel()
{
	bIsLevelLoaded = true;
	UGameplayStatics::LoadStreamLevel(this, LevelName, true, false, FLatentActionInfo());
	DistanceLODMesh->SetHiddenInGame(true);
}

void AACFLevelStreamerActor::UnloadLevel()
{
	bIsLevelLoaded = false;
	UGameplayStatics::UnloadStreamLevel(this, LevelName, FLatentActionInfo(), false);
	DistanceLODMesh->SetHiddenInGame(false);
}

