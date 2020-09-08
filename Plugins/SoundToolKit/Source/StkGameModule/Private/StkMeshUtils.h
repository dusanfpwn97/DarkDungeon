//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

THIRD_PARTY_INCLUDES_START
#include "stk/Math.h"
THIRD_PARTY_INCLUDES_END

class UStaticMesh;
class ALandscape;

namespace SoundToolKit
{
	namespace Utils
	{
		/// <summary>
		/// A helper function which extracts faces from StaticMesh for given LOD.
		/// </summary>
		/// <param name="StaticMesh">Mesh to get faces from.</param>
		/// <param name="LODIndex">Index of the LOD.</param>
		/// <param name="LocalToWorld">Actor to world matrix.</param>
		/// <param name="OutMeshSectionFaces">Extracted faces per section.</param>
		void GetStaticMeshFacesForLOD(
			UStaticMesh* StaticMesh, const int32 LODIndex, const struct FMatrix& LocalToWorld, TArray<TArray<stk::face>>& OutMeshSectionFaces);

		/// <summary>
		/// A helper function which extracts collision faces from Landscape.
		/// </summary>
		/// <param name="Landscape">Landscape for which faces should be extracted.</param>
		/// <param name="OutFaces">Extracted Landscape's faces.</param>
		void GetLandscapeCollisionFaces(ALandscape* Landscape, TArray<stk::face>& OutFaces);
	}
}
