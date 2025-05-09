//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/Actors/DungeonMesh.h"
#include "Core/Editors/ThemeEditor/Graph/EdGraphNode_DungeonActorBase.h"
#include "EdGraphNode_DungeonMesh.generated.h"

UCLASS()
class DUNGEONARCHITECTEDITOR_API UEdGraphNode_DungeonMesh : public UEdGraphNode_DungeonActorBase {
    GENERATED_UCLASS_BODY()

public:
    UObject* GetNodeAssetObject(UObject* Outer) override;
    UObject* GetThumbnailAssetObject() override;

    void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    TArray<FMaterialOverride> MaterialOverrides;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Details")
    UStaticMeshComponent* AdvancedOptions;
};
