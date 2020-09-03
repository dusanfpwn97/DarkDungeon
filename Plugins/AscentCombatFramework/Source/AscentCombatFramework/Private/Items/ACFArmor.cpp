// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFArmor.h"
#include <Internationalization/Text.h>

AACFArmor::AACFArmor()
{
	ItemInfo.ItemType = EItemType::Armor;
	ItemInfo.Name = FText::FromString("BaseArmor");
}
