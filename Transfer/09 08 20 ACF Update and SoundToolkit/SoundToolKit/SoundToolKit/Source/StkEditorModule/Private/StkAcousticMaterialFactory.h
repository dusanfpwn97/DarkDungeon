//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Factories/Factory.h"

#include "StkAcousticMaterialFactory.generated.h"

UCLASS()
class UStkAcousticMaterialFactory : public UFactory
{
	GENERATED_BODY()

public:
	UStkAcousticMaterialFactory();

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface
};
