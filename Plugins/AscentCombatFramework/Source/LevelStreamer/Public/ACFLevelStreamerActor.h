// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACFLevelStreamerActor.generated.h"

UCLASS()
class LEVELSTREAMER_API AACFLevelStreamerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACFLevelStreamerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Name of the level to be loaded*/
	UPROPERTY(EditAnywhere, Category = ACF)
	FName LevelName;

	/*Time Interval between distance Checks*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	float TimeInterval = 0.2;

	/*Distance from player at which the level will be loaded in memory*/
	UPROPERTY(EditAnywhere, Category = ACF)
	float MaxDistanceFromPlayer = 25000;

	UPROPERTY(VisibleAnywhere, Category = ACF)
	UStaticMeshComponent* DistanceLODMesh;
	

private:	
	
	void CheckAndUpdateLevel();

	void LoadLevel();
	void UnloadLevel();

	bool bIsLevelLoaded = false;

	FTimerHandle timerHandle;
};
