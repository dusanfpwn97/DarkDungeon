// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.
/*
2018 PakyMan Prod.
*/
#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include <Engine/DataTable.h>
#include <GameFramework/Actor.h>
#include "CCMData.h"
#include "CCMPlayerCameraManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraSequenceStarted, const FName&, cameraSequence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraSequenceEnded, const FName&, cameraSequence);


UCLASS()
class CINEMATICCAMERAMANAGER_API ACCMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public: 

	ACCMPlayerCameraManager();

protected: 
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void UpdateCamera(float deltaTime) override;

	UPROPERTY(EditAnywhere, Category = "CCM Camera")
	UDataTable* CameraMovements;

	UPROPERTY(EditAnywhere, Category = "CCM Camera")
	float CameraLockPitchUpperLimit = 75.f;
	 
	UPROPERTY(EditAnywhere, Category = "CCM Camera")
	float CameraLockPitchLowerLimit = 35.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CCM Camera")
	TSubclassOf<ACameraActor> CameraActorClass;

	UPROPERTY(BlueprintReadOnly, Category = "CCM Camera")
	FCCMCameraMovementSettings FinalMov;


	UPROPERTY(BlueprintReadOnly, Category = "CCM Camera")
	class UCameraComponent* _playerCamera;

	UPROPERTY(BlueprintReadOnly, Category = "CCM Camera")
	class USpringArmComponent* _cameraBoom;


	//UPROPERTY(BlueprintReadOnly, Category = CCM)
	UPROPERTY()
	bool bIsPlayingSequence = false;

 	UPROPERTY()
	class ACameraActor* sequenceCameraActor;

	UPROPERTY()
	FCurrentSequence  currentSequence;
	
public:

	UPROPERTY(BlueprintAssignable, Category = "CCM")
	FOnCameraSequenceStarted OnCameraSequenceStarted;

	UPROPERTY(BlueprintAssignable, Category = "CCM")
	FOnCameraSequenceEnded OnCameraSequenceEnded;

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void TriggerCameraEvent(FName CameraEventName);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void TriggerTimedCameraEvent(FName CameraEventName, float duration);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void StopCameraEvent(FName CameraEventName);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void ResetCameraPosition(bool bInstantReset = false);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void LockCameraOnActor(class AActor* ActorLookAt, ELockType lockType, float lockStrength = 5.f );

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void LockCameraOnComponent(class USceneComponent* ComponentToLookAt, ELockType lockType, float lockStrength = 5.f);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void StopLookingActor();

	void UpdateCameraReferences();

	UFUNCTION(BlueprintCallable, Category = "CCM")
	FORCEINLINE bool IsCameraRotatingAroundCharacter() const { return bIsRotating; }

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void TriggerCameraSequence(AActor* cameraOwner, FName CameraEventName);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void StopCurrentCameraSequence();

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void AddSequenceEventModifier(const FCCMSequenceEvent& modifier);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void RemoveSequenceEventModifier(const FCCMSequenceEvent& modifier);

	UFUNCTION(BlueprintCallable, Category = "CCM")
	void OverrideCameraReferences(class UCameraComponent* inPlayerCamera,	class USpringArmComponent* inCameraBoom);

private:

	void MoveCamera(float deltaTime);

	void SetCameraSequenceData();

	void UpdateLockOnTarget(float deltaTime);

	 void UpdateCameraSequence(float deltaTime);

	void LockCameraOnPosition(FVector localPos, float deltaTime);

	void StoreData();
	void RecoverStoredData();

	UPROPERTY()
	TMap<FName, FCCMCameraMovementSettings> _currentlyActiveCameraEvents;

	UPROPERTY()
	class APawn* _playerCharacter;

	UPROPERTY()
	FVector _originalPos;

	UPROPERTY()
	float _originalFov;

	UPROPERTY()
	FRotator _originalRelativeRot;

	UPROPERTY()
	FVector _localPos;

	UPROPERTY()
	float _localFov;

	UPROPERTY()
	float _localTimeDilatation;

	UPROPERTY()
	ETargetLockType _localIsLockingAt;

	UPROPERTY()
	bool _localStrafing;

	UPROPERTY()
	float _lockStrength;

	UPROPERTY()
	bool _localOrientToMov;
	
	UPROPERTY()
	float _localArmLength;

	UPROPERTY()
	bool bIsRotating = false;

	UPROPERTY()
	ETargetLockType targetLockType = ETargetLockType::ENone;

	UPROPERTY()
	ELockType currentLockType;
	
	UPROPERTY()
	class AActor* localtarget;

	UPROPERTY()
	class USceneComponent* localtargetComponent;

	UFUNCTION()
	void HandlePawnChanged(APawn* newPawn);

	UPROPERTY()
	FCCMCameraSequenceSettings currentSequenceSettings;


};
