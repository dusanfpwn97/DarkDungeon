//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"

#include "StkOcclusionSourceSettingsFactory.generated.h"

namespace SoundToolKit
{
	class FAssetTypeActions_StkOcclusionSourceSettings : public FAssetTypeActions_Base
	{
	public:
		// FAssetTypeActions_Base interface
		virtual uint32 GetCategories() override;
		virtual FText GetName() const override;
		virtual UClass* GetSupportedClass() const override;
		virtual FColor GetTypeColor() const override;
		// End of FAssetTypeActions_Base interface
	};
}

UCLASS()
class UStkOcclusionSourceSettingsFactory : public UFactory
{
	GENERATED_BODY()

public:
	UStkOcclusionSourceSettingsFactory();

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface
};
