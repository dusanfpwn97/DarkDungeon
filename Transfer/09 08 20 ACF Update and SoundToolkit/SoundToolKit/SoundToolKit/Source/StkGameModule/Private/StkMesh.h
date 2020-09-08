//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

THIRD_PARTY_INCLUDES_START
#pragma warning(disable:4310)
#include <stk/SharedResource.h>
#include <stk/ArrayView.h>
#include <stk/IMesh.h>
#pragma warning(default:4310)
THIRD_PARTY_INCLUDES_END

namespace stk
{
	struct face;
}

namespace SoundToolKit
{
	/// <summary>
	/// Manages a Mesh within SoundToolKit engine.
	/// </summary>
	class STKGAMEMODULE_API FStkMesh
	{
	public:

		FStkMesh(stk::SharedResource<stk::IMesh> Mesh);
		~FStkMesh();

		/// <summary>
		/// Sets the mesh faces.
		/// </summary>
		/// <param name="Faces">std::vector containing the faces</param>
		void SetFaces(TArray<stk::face>&& Faces);

		void GetFaces(TFunction<void(stk::ArrayView<stk::face>)> callback);

		/// <summary>
		/// Enables the mesh so it will be taken into account during sound processing. 
		/// It will act as an obstacle, from which the sound can be reflected etc.
		/// </summary>
		void EnableAsObstacle();

		/// <summary>
		/// Disables the mesh so it will not be taken into account during sound processing.
		/// </summary>
		void DisableAsObstacle();

		/// <summary>
		/// Checks if the mesh acts as an obstacle in sound propagation.
		/// </summary>
		bool IsEnabledAsObstacle();

		/// <summary>
		/// Sets the mesh acoustic material.
		/// </summary>
		/// <param name="Material">The material, from which the mesh is made</param>
		void SetMaterial(const class FStkMaterial& Material);

		stk::SharedResource<stk::IMesh> Native() const;

	private:

		stk::SharedResource<stk::IMesh> StkMesh;
		bool EnabledAsObstacle;
	};
}
