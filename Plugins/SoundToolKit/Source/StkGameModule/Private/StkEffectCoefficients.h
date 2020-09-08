//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkEffectCoefficients.generated.h"

USTRUCT(BlueprintType)
struct FStkEffectCoefficients
{
	GENERATED_BODY()

	/// Effect severity in a 125 Hz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "125 Hz"))
	float Band125Hz;

	/// Effect severity in a 250 Hz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "250 Hz"))
	float Band250Hz;

	/// Effect severity in a 500 Hz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "500 Hz"))
	float Band500Hz;

	/// Effect severity in a 1 kHz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "1000 Hz"))
	float Band1000Hz;

	/// Effect severity in a 2 kHz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "2000 Hz"))
	float Band2000Hz;

	/// Effect severity in a 4 kHz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "4000 Hz"))
	float Band4000Hz;

	/// Effect severity in a 8 kHz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "8000 Hz"))
	float Band8000Hz;

	/// Effect severity in a 16 kHz octave band.
	UPROPERTY(BlueprintReadWrite, Category = "Effect Severity", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "16000 Hz"))
	float Band16000Hz;

	FStkEffectCoefficients()
		: FStkEffectCoefficients(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
	{}

	FStkEffectCoefficients(float band125Hz, float band250Hz, float band500Hz, float band1000Hz, float band2000Hz, float band4000Hz, float band8000Hz, float band16000Hz)
		: Band125Hz(band125Hz)
		, Band250Hz(band250Hz)
		, Band500Hz(band500Hz)
		, Band1000Hz(band1000Hz)
		, Band2000Hz(band2000Hz)
		, Band4000Hz(band4000Hz)
		, Band8000Hz(band8000Hz)
		, Band16000Hz(band16000Hz)
	{}
};
