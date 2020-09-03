// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFItem.h"


// Sets default values
AACFItem::AACFItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemInfo.GUID = GetUniqueID(); //Item with a unique ID only while it is alive
	SetReplicates(true);
}



