//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Factories/Factory.h"

#include "StkAcousticModelFactory.generated.h"

UCLASS()
class UStkAcousticModelFactory : public UFactory
{
	GENERATED_BODY()

public:
	UStkAcousticModelFactory();

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface
};
