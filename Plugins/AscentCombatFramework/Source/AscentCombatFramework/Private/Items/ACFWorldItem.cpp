// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFWorldItem.h"
#include <Components/StaticMeshComponent.h>
#include "Items/ACFItem.h"
#include "Components/ACFEquipmentComponent.h"
#include <Components/SphereComponent.h>
#include "Net/UnrealNetwork.h"
#include "Game/ACFFunctionLibrary.h"


AACFWorldItem::AACFWorldItem()
{
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	/*InteractableArea = CreateDefaultSubobject<USphereComponent>(TEXT("Interactable Area"));*/
	bReplicates = true;
/*	InteractableArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/
	ObjectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AACFWorldItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AACFWorldItem, Items);


}

void AACFWorldItem::BeginPlay()
{	
	Super::BeginPlay();
	if (Items.IsValidIndex(0) && Items[0].ItemClass != nullptr) {
		//Add an index to worlditem to make it easier to calculate when picking
		for (int i = 0; i < Items.Num(); i++)
		{
			Items[i].Index = i;
		}
		SetItemsArray(Items);
	}
		
}

void AACFWorldItem::SetItemsArray(const TArray<FBaseItem>& inItems)
{
	Items = inItems;

	if (ObjectMesh && Items.IsValidIndex(0) && Items[0].ItemClass)
	{
		AACFItem* _item = Items[0].ItemClass.GetDefaultObject();

		if (_item)
		{
			ItemInfo = _item->GetItemInfo();
			if (_item->GetItemInfo().WorldMesh)
			{
				ObjectMesh->SetStaticMesh(_item->GetItemInfo().WorldMesh);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("StaticMesh Not Assigned!!! - ACFWorldItem"));
			}
		}	
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Trying to assign a wrong Item to the World Item!! - ACFWorldItem"));
	}
}


void AACFWorldItem::RemoveItems_Implementation(const TArray<FBaseItem>& inItems)
{
	TArray<FBaseItem> pendingRemove;
	for (auto item : inItems) {
		FBaseItem* currentItem = Items.FindByKey(item);

		if (currentItem) {
			currentItem->Count -= item.Count;

			if (currentItem->Count <= 0) {
				pendingRemove.Add(*currentItem);
			}
		}
	}

	for (auto removed : pendingRemove) {
		Items.Remove(removed);
	}

	OnWorldItemChanged.Broadcast(Items);
	if (Items.Num() == 0 && bDestroyOnGather) {
		this->Destroy();
	}
}

bool AACFWorldItem::RemoveItems_Validate(const TArray<FBaseItem>& inItems)
{
	return true;
}

void AACFWorldItem::OnInteractedByPawn_Implementation(class APawn* Pawn)
{
	if (Pawn)
	{
		UACFEquipmentComponent* _equipComp = Pawn->FindComponentByClass<UACFEquipmentComponent>();
		if (_equipComp)
		{
			TArray<int> ItemToPick;
			for (int i = 0; i < Items.Num(); i++)
			{
				ItemToPick.Add(Items[i].Index);
			}
			_equipComp->AddWorldItemToInventory(this, ItemToPick);
		}
	}	
}

void AACFWorldItem::OnInteractableRegisteredByPawn_Implementation(class APawn* Pawn)
{

}


void AACFWorldItem::OnInteractableUnregisteredByPawn_Implementation(class APawn* Pawn)
{

}

FText AACFWorldItem::GetInteractableName_Implementation()
{	
	FString completeName = "";
	if(Items.IsValidIndex(0)){
		completeName = ItemInfo.Name.ToString() + " x" + FString::FromInt( Items[0].Count);
	}
	
	//completeName.AppendInt(Count);
	return FText::FromString(completeName);
}

void AACFWorldItem::OnActorLoaded_Implementation()
{
	SetItemsArray(Items);
}

void AACFWorldItem::OnActorSaved_Implementation()
{

}

void AACFWorldItem::ConstructInventoryItems(TArray<FInventoryItem>& outItems) 
{
	for (auto item : Items) {
		FInventoryItem outItem;
		outItem.Item = NewObject<AACFItem>(this, item.ItemClass);
		outItem.Count = item.Count;
		outItems.Add(outItem);
	}
}

void AACFWorldItem::RemoveItemsByIndex_Implementation(const TArray<FBaseItem>& inItems)
{
	
	for (auto removed : inItems) {
		Items.RemoveAll([=](FBaseItem& This)
		{
			return removed.Index==This.Index;
		});
	}
	OnWorldItemChanged.Broadcast(Items);//addition code
	if (Items.Num() == 0 && bDestroyOnGather) {
		this->Destroy();
	}
}

bool AACFWorldItem::RemoveItemsByIndex_Validate(const TArray<FBaseItem>& inItems)
{
	return true;
}

//addition code
void AACFWorldItem::OnRep_Items()
{
	OnWorldItemChanged.Broadcast(Items);
}

bool AACFWorldItem::CanBeInteracted_Implementation(class APawn* Pawn)
{
	return true;
}

