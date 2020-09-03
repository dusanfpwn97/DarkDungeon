// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>
#include "Game/ACFData.h"
#include "ACFAnimset.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class ASCENTCOMBATFRAMEWORK_API UACFAnimset : public UObject
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		TMap<FGameplayTag, FActionState> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UBlendSpace* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UBlendSpace1D* Idle;

// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 		class UBlendSpace1D* Starts;
// 
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 		class UBlendSpace1D* Stops;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAimOffsetBlendSpace* AimOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* JumpStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* JumpLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* JumpEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* AdditiveAnimation;

};

USTRUCT(BlueprintType)
struct FActionsMap : public FTableRowBase
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		TMap<FGameplayTag, FActionState> Actions;
};

USTRUCT(BlueprintType)
struct FACFMoveset : public FTableRowBase
{

	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UBlendSpace* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UBlendSpace1D* Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAimOffsetBlendSpace* AimOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* JumpStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* JumpLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UAnimSequence* JumpEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	class UAimOffsetBlendSpace1D* AdditiveBlendspace;
};

USTRUCT(BlueprintType)
struct FAnimationOverlay : public FTableRowBase
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	class UAnimSequence* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float BlendingAlpha = 0.7f;

};


