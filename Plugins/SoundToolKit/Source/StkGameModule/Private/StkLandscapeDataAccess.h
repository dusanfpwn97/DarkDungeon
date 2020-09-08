//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

class ULandscapeComponent;

/// Used to get Landscape's mesh data.
struct FStkLandscapeComponentDataInterface
{
	FStkLandscapeComponentDataInterface(ULandscapeComponent* InComponent, int32 InMipLevel = 0);

public:
	FVector GetLocalVertex(int32 LocalX, int32 LocalY) const;
	FVector GetWorldVertex(int32 LocalX, int32 LocalY) const;

private:
	void ComponentXYToSubsectionXY(int32 CompX, int32 CompY, int32& SubNumX, int32& SubNumY, int32& SubX, int32& SubY) const;
	void VertexXYToTexelXY(int32 VertX, int32 VertY, int32& OutX, int32& OutY) const;
	FColor* GetHeightData(int32 LocalX, int32 LocalY) const;
	FColor* GetXYOffsetData(int32 LocalX, int32 LocalY) const;
	uint16 GetHeight(int32 LocalX, int32 LocalY) const;
	void GetXYOffset(int32 X, int32 Y, float& XOffset, float& YOffset) const;

private:
	ULandscapeComponent* Component;

	TArray<void*> ComponentHeightmapMipData;
	TArray<void*> CompoenentXYOffsetTextureMipData;

	// Offset of this component's data into heightmap texture
	int32 HeightmapStride;
	int32 HeightmapComponentOffsetX;
	int32 HeightmapComponentOffsetY;

	FColor* HeightMipData;
	FColor* XYOffsetMipData;

	int32 ComponentSizeVerts;
	int32 SubsectionSizeVerts;

	const int32 MipLevel;
};
