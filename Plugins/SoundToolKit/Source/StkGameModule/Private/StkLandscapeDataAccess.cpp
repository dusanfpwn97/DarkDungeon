//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkLandscapeDataAccess.h"
#include "LandscapeComponent.h"
#include "Engine/Texture2D.h"

///
/// <summary>
/// Implementation is based on UE's LandscapeDataAccess.h & LandscapeDataAccess.cpp files (most code is copy-pasted).
/// UE's version of this structure can only be used when editor modules are loaded. This version can be used on non-editor build.
/// </summary>
///
namespace
{
	constexpr float MidValue = 32768.f;

	float GetLocalHeight(uint16 Height)
	{
		constexpr float LandscapeZScale{ 1.0f / 128.0f };
		return (static_cast<float>(Height) - MidValue) * LandscapeZScale;
	}
};

FStkLandscapeComponentDataInterface::FStkLandscapeComponentDataInterface(ULandscapeComponent* InComponent, int32 InMipLevel) :
	Component(InComponent),
	HeightMipData(nullptr),
	XYOffsetMipData(nullptr),
	MipLevel(InMipLevel)
{
	Component->GetHeightmap(true)->UpdateResource();
	if (Component->XYOffsetmapTexture)
	{
		Component->XYOffsetmapTexture->UpdateResource();
	}

	// Offset and stride for this component's data in heightmap texture
	HeightmapStride = Component->GetHeightmap(true)->GetSizeX() >> MipLevel;
	HeightmapComponentOffsetX = FMath::RoundToInt((float)(Component->GetHeightmap(true)->GetSizeX() >> MipLevel) * Component->HeightmapScaleBias.Z);
	HeightmapComponentOffsetY = FMath::RoundToInt((float)(Component->GetHeightmap(true)->GetSizeY() >> MipLevel) * Component->HeightmapScaleBias.W);

	ComponentSizeVerts = (Component->ComponentSizeQuads + 1) >> MipLevel;
	SubsectionSizeVerts = (Component->SubsectionSizeQuads + 1) >> MipLevel;

	if (MipLevel < Component->GetHeightmap(true)->GetNumMips())
	{
		ComponentHeightmapMipData.SetNumZeroed(Component->GetHeightmap()->GetNumMips());
		Component->GetHeightmap()->GetMipData(0, ComponentHeightmapMipData.GetData());
		HeightMipData = static_cast<FColor*>(ComponentHeightmapMipData[MipLevel]);

		if (Component->XYOffsetmapTexture)
		{
			CompoenentXYOffsetTextureMipData.SetNumZeroed(Component->XYOffsetmapTexture->GetNumMips());
			Component->XYOffsetmapTexture->GetMipData(0, CompoenentXYOffsetTextureMipData.GetData());
			XYOffsetMipData = static_cast<FColor*>(CompoenentXYOffsetTextureMipData[MipLevel]);
		}
	}
}

FVector FStkLandscapeComponentDataInterface::GetLocalVertex(int32 LocalX, int32 LocalY) const
{
	const float ScaleFactor = (float)Component->ComponentSizeQuads / (float)(ComponentSizeVerts - 1);
	float XOffset, YOffset;
	GetXYOffset(LocalX, LocalY, XOffset, YOffset);
	return FVector(LocalX * ScaleFactor + XOffset, LocalY * ScaleFactor + YOffset, GetLocalHeight(GetHeight(LocalX, LocalY)));
}

FVector FStkLandscapeComponentDataInterface::GetWorldVertex(int32 LocalX, int32 LocalY) const
{
	return Component->GetComponentTransform().TransformPosition(GetLocalVertex(LocalX, LocalY));
}

void FStkLandscapeComponentDataInterface::ComponentXYToSubsectionXY(int32 CompX, int32 CompY, int32& SubNumX, int32& SubNumY, int32& SubX, int32& SubY) const
{
	// We do the calculation as if we're looking for the previous vertex.
	// This allows us to pick up the last shared vertex of every subsection correctly.
	SubNumX = (CompX - 1) / (SubsectionSizeVerts - 1);
	SubNumY = (CompY - 1) / (SubsectionSizeVerts - 1);
	SubX = (CompX - 1) % (SubsectionSizeVerts - 1) + 1;
	SubY = (CompY - 1) % (SubsectionSizeVerts - 1) + 1;

	// If we're asking for the first vertex, the calculation above will lead
	// to a negative SubNumX/Y, so we need to fix that case up.
	if (SubNumX < 0)
	{
		SubNumX = 0;
		SubX = 0;
	}

	if (SubNumY < 0)
	{
		SubNumY = 0;
		SubY = 0;
	}
}

void FStkLandscapeComponentDataInterface::VertexXYToTexelXY(int32 VertX, int32 VertY, int32& OutX, int32& OutY) const
{
	int32 SubNumX, SubNumY, SubX, SubY;
	ComponentXYToSubsectionXY(VertX, VertY, SubNumX, SubNumY, SubX, SubY);

	OutX = SubNumX * SubsectionSizeVerts + SubX;
	OutY = SubNumY * SubsectionSizeVerts + SubY;
}

FColor* FStkLandscapeComponentDataInterface::GetHeightData(int32 LocalX, int32 LocalY) const
{
	int32 TexelX, TexelY;
	VertexXYToTexelXY(LocalX, LocalY, TexelX, TexelY);

	return &HeightMipData[TexelX + HeightmapComponentOffsetX + (TexelY + HeightmapComponentOffsetY) * HeightmapStride];
}

FColor* FStkLandscapeComponentDataInterface::GetXYOffsetData(int32 LocalX, int32 LocalY) const
{
	const int32 WeightmapSize = (Component->SubsectionSizeQuads + 1) * Component->NumSubsections;
	int32 SubNumX;
	int32 SubNumY;
	int32 SubX;
	int32 SubY;
	ComponentXYToSubsectionXY(LocalX, LocalY, SubNumX, SubNumY, SubX, SubY);

	return &XYOffsetMipData[SubX + SubNumX * SubsectionSizeVerts + (SubY + SubNumY * SubsectionSizeVerts) * WeightmapSize];
}

uint16 FStkLandscapeComponentDataInterface::GetHeight(int32 LocalX, int32 LocalY) const
{
	FColor* Texel = GetHeightData(LocalX, LocalY);
	return (Texel->R << 8) + Texel->G;
}

void FStkLandscapeComponentDataInterface::GetXYOffset(int32 X, int32 Y, float& XOffset, float& YOffset) const
{
	if (XYOffsetMipData)
	{
		constexpr float LandscapeXYOffsetScale{ 1.0f / 256.f };

		FColor* Texel = GetXYOffsetData(X, Y);
		XOffset = ((float)((Texel->R << 8) + Texel->G) - MidValue) * LandscapeXYOffsetScale;
		YOffset = ((float)((Texel->B << 8) + Texel->A) - MidValue) * LandscapeXYOffsetScale;
	}
	else
	{
		XOffset = YOffset = 0.f;
	}
}
