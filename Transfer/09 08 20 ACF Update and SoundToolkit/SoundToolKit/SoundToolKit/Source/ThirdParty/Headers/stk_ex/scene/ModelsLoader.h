///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 28.02.2019
///
#ifndef STK_EX__SCENE__MODELS_LOADER__H
#define STK_EX__SCENE__MODELS_LOADER__H

#include <functional>
#include <stk/StringView.h>
#include <stk/SharedResource.h>

namespace stk
{
	class ISoundToolKit;
	class IMesh;
	class IModel;
}

namespace stk_ex::scene
{
	/// <summary>
	/// The callback called for each loaded mesh with the mesh name, material name, and the mesh itself.
	/// </summary>
	/// <param name="meshName">The name of the mesh, or null view if no name is present.</param>
	/// <param name="materialName">The name of material which should be applied to the mesh, or null pointer if no such material is defined.</param>
	/// <param name="mesh">The created mesh, with no material assigned.</param>
	/// <note>The callback can be used to set the mesh material.</note>
	using MeshMaterialCallback = std::function<void(stk::StringView meshName, stk::StringView materialName, stk::SharedResource<stk::IMesh> mesh)>;

	/// <summary>
	/// Loads all meshes from the specified file in JSON format and creates a model from them.
	/// </summary>
	/// <param name="stk">The SoundToolKit interface used to create resources.</param>
	/// <param name="filePath">A path to the file containing the definitions of model's meshes.</param>
	/// <param name="callback">A callback called for each loaded and created mesh.</param>
	/// <returns>The created model or null pointer in case of critical error.</returns>
	stk::SharedResource<stk::IModel> loadModelJson(stk::ISoundToolKit& stk,
		stk::StringView filePath, MeshMaterialCallback callback);
}

#endif
