//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/Editors/ThemeEditor/Graph/EdGraphNode_DungeonActorBase.h"

#include "Components/PointLightComponent.h"
#include "EdGraphNode_DungeonPointLight.generated.h"

UCLASS()
class DUNGEONARCHITECTEDITOR_API UEdGraphNode_DungeonPointLight : public UEdGraphNode_DungeonActorBase {
    GENERATED_UCLASS_BODY()

public:
    UObject* GetNodeAssetObject(UObject* Outer) override;
    UObject* GetThumbnailAssetObject() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    UPointLightComponent* PointLight;
};
