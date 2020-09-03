// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include <GameFramework/Character.h>
#include "CASTypes.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombinedAnimationStarted, const FName&, animTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombinedAnimationEnded, const FName&, animTag);

UENUM(BlueprintType)
enum class ERelativeDirection : uint8
{
	EAny	            UMETA(DisplayName = "Any"),
//	ENotOpposite	    UMETA(DisplayName = "Any Except From Behind"),
	EFrontal			UMETA(DisplayName = "Facing Each Other Only"),
// 	ERight				UMETA(DisplayName = "From Right"),
// 	ELeft				UMETA(DisplayName = "From Right"),
	EOpposite			UMETA(DisplayName = "From Behind"),
};

USTRUCT(BlueprintType)
struct FCombinedAnimsMaster : public FTableRowBase
{
	GENERATED_BODY()

public:

	/*The */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
	class UAnimMontage* MasterAnimMontage;

	/*Max distance between master and slave characters to start snapping throught 
	the start position*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
	float MaxDistanceToStartSnapping = 450.f;

	/*After the snap timeout, the animation combined will only start if we
	are closer then this distance to the target starting position*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
	float MaxDistanceToStartCombinedAnimation = 60.f;
	
	/*If the slave is not in this relative direction to the master, 
	the animation combined cannot start. Select Any to ignore this check*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
	ERelativeDirection SlaveRequiredDirection = ERelativeDirection::EAny;

	/*Once the animation starts, the slaved character will be rotated to this direction.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
	ERelativeDirection SlaveForcedDirection = ERelativeDirection::EFrontal;

};

USTRUCT(BlueprintType)
struct FCombinedAnimsSlave : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		class UAnimMontage* MasterAnimMontage;

};

USTRUCT(BlueprintType)
struct FCurrentCombinedAnim 
{
	GENERATED_BODY()

public:

	FCurrentCombinedAnim(){};

	FCurrentCombinedAnim(const FCombinedAnimsMaster& inMasterConfig, const FName& inTag, ACharacter* inCharacterRef) {
		MasterAnimConfig = inMasterConfig;
		AnimTag = inTag;
		AnimSlave = inCharacterRef;
	}

	/*The */
	UPROPERTY(BlueprintReadOnly, Category = "CAS")
	FCombinedAnimsMaster MasterAnimConfig;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
	FName AnimTag;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
	ACharacter* AnimSlave;
};
/**
 * 
 */
UCLASS()
class COMBINEDANIMATIONSSYSTEM_API UCASTypes : public UObject
{
	GENERATED_BODY()
	
};
