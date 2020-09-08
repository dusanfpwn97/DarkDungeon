//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkAcousticModel.generated.h"

///	Class representing acoustical model asset.
UCLASS(ClassGroup = (SoundToolKit))
class STKGAMEMODULE_API UStkAcousticModel : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, VisibleAnywhere, Category = "Model Content")
	TArray<class ALandscape*> Landscapes;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Model Content")
	TArray<class UStaticMeshComponent*> StaticMeshComponents;

#if WITH_EDITOR
public:
	void Add(UObject* Object);
	void Remove(UObject* Object);
	bool Contains(UObject* Object);

public:
	// UObject interface
	virtual void PostLoad() override;
	// End of UObject interface
#endif
};
