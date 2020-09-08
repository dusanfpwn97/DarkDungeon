//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkMesh.h"
#include "StkCommon.h"
#include "StkMaterial.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IMaterial.h>
#include <stk/IMesh.h>
THIRD_PARTY_INCLUDES_END

namespace SoundToolKit
{
	FStkMesh::FStkMesh(stk::SharedResource<stk::IMesh> Mesh)
		: StkMesh(Mesh)
	{
	}

	FStkMesh::~FStkMesh() = default;

	void FStkMesh::SetFaces(TArray<stk::face>&& Faces)
	{
		StkMesh->setFaces(stk::ArrayView<stk::face>{Faces.GetData(), static_cast<size_t>(Faces.Num())});
	}

	void FStkMesh::GetFaces(TFunction<void(stk::ArrayView<stk::face>)> callback)
	{
		StkMesh->getFaces(callback);
	}

	void FStkMesh::EnableAsObstacle()
	{
		StkMesh->enable();
		EnabledAsObstacle = true;
	}

	void FStkMesh::DisableAsObstacle()
	{
		StkMesh->disable();
		EnabledAsObstacle = false;
	}

	bool FStkMesh::IsEnabledAsObstacle()
	{
		return EnabledAsObstacle;
	}

	void FStkMesh::SetMaterial(const FStkMaterial& Material)
	{
		StkMesh->setMaterial(Material.Native());
	}

	stk::SharedResource<stk::IMesh> FStkMesh::Native() const
	{
		return StkMesh;
	}
}
