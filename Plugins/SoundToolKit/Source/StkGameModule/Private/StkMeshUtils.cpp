//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkMeshUtils.h"
#include "StkLog.h"
#include "StkCommon.h"
#include "StkLandscapeDataAccess.h"

THIRD_PARTY_INCLUDES_START
#include "stk_ex/utility/MeshFaceValidator.h"
THIRD_PARTY_INCLUDES_END

#include "Engine/StaticMesh.h"
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "LandscapeHeightfieldCollisionComponent.h"

namespace
{
	void AddFaceIfValid(FString Name, TArray<stk::face>& Faces, stk::face&& Face)
	{
		if (stk_ex::utility::isValidMeshFace(Face))
		{
			Faces.Emplace(std::move(Face));
		}
		else
		{
			STK_LOG(Warning, TEXT("Omitting invalid triangle (a=[%s], b=[%s], c=[%s]) inside %s."),
				*SoundToolKit::Utils::ConvertVector(Face.a).ToString(),
				*SoundToolKit::Utils::ConvertVector(Face.b).ToString(),
				*SoundToolKit::Utils::ConvertVector(Face.c).ToString(),
				*Name);
		}
	}
}

namespace SoundToolKit
{
	namespace Utils
	{
		void GetStaticMeshFacesForLOD(
			UStaticMesh* StaticMesh, const int32 LODIndex, const struct FMatrix& LocalToWorld, TArray<TArray<stk::face>>& OutMeshSectionFaces)
		{
			const FStaticMeshLODResources& RenderData = StaticMesh->GetLODForExport(LODIndex);

			STK_CHECK(StaticMesh->bAllowCPUAccess, Error, TEXT("CPU access must be enabled on static meshes used as acoustic mesh (%s)."),
				*StaticMesh->GetFName().ToString());
			FIndexArrayView Indices = RenderData.IndexBuffer.GetArrayView();
			uint32 NumIndices = Indices.Num();

			// There should be 3 indices for each triangle
			if (NumIndices % 3 != 0)
			{
				STK_LOG(Error, TEXT("Wrong indices count in %s."), *StaticMesh->GetName());
				return;
			}

			uint32 VertexCount = RenderData.VertexBuffers.PositionVertexBuffer.GetNumVertices();
			if (VertexCount != RenderData.GetNumVertices())
			{
				STK_LOG(Error, TEXT("VertexCount mismatch in %s."), *StaticMesh->GetName());
				return;
			}

			TArray<FVector> Vertices;
			Vertices.AddUninitialized(VertexCount);

			for (uint32 i = 0; i < VertexCount; ++i)
			{
				Vertices[i] = LocalToWorld.TransformPosition(RenderData.VertexBuffers.PositionVertexBuffer.VertexPosition(i));
			}

			bool bFlipCullMode = LocalToWorld.RotDeterminant() < 0.0f;

			OutMeshSectionFaces.AddZeroed(RenderData.Sections.Num());
			for (int32 SectionIndex = 0; SectionIndex < OutMeshSectionFaces.Num(); ++SectionIndex)
			{
				const FStaticMeshSection& Section = RenderData.Sections[SectionIndex];

				// The vector with faces for this section
				OutMeshSectionFaces[SectionIndex].Reserve(Section.NumTriangles);

				for (uint32 i = 0; i < Section.NumTriangles; i++)
				{
					// Indexes in Vertices array
					uint32 a = Indices[Section.FirstIndex + i * 3 + 0];
					uint32 b = Indices[Section.FirstIndex + i * 3 + 1];
					uint32 c = Indices[Section.FirstIndex + i * 3 + 2];

					if (bFlipCullMode)
					{
						Swap(a, c);
					}

					stk::face Face = {
						SoundToolKit::Utils::ConvertVector(Vertices[a]),
						SoundToolKit::Utils::ConvertVector(Vertices[b]),
						SoundToolKit::Utils::ConvertVector(Vertices[c]) };

					AddFaceIfValid(StaticMesh->GetFName().ToString(), OutMeshSectionFaces[SectionIndex], std::move(Face));
				}
			}
		}

		void GetLandscapeCollisionFaces(ALandscape* Landscape, TArray<stk::face>& OutFaces)
		{
			for (ULandscapeComponent* Component : Landscape->LandscapeComponents)
			{
				const int32 CollisionMipLevel = FMath::Max(Component->CollisionMipLevel, Component->SimpleCollisionMipLevel);
				const int32 CollisionSizeQuads = Component->CollisionMipLevel >= Component->SimpleCollisionMipLevel ?
					Component->CollisionComponent->CollisionSizeQuads : Component->CollisionComponent->SimpleCollisionSizeQuads;

				FStkLandscapeComponentDataInterface LandscapeData(Component, CollisionMipLevel);

				for (auto Y = 0; Y < CollisionSizeQuads; ++Y)
				{
					for (auto X = 0; X < CollisionSizeQuads; ++X)
					{
						stk::vec3 Vertex1 = SoundToolKit::Utils::ConvertVector(LandscapeData.GetWorldVertex(X, Y));
						stk::vec3 Vertex2 = SoundToolKit::Utils::ConvertVector(LandscapeData.GetWorldVertex(X, Y + 1));
						stk::vec3 Vertex3 = SoundToolKit::Utils::ConvertVector(LandscapeData.GetWorldVertex(X + 1, Y + 1));
						stk::vec3 Vertex4 = SoundToolKit::Utils::ConvertVector(LandscapeData.GetWorldVertex(X + 1, Y));

						stk::face Face1 = { Vertex1, Vertex2, Vertex3 };
						stk::face Face2 = { Vertex3, Vertex4, Vertex1 };

						AddFaceIfValid(Landscape->GetName(), OutFaces, std::move(Face1));
						AddFaceIfValid(Landscape->GetName(), OutFaces, std::move(Face2));
					}
				}
			}
		}
	}
}
