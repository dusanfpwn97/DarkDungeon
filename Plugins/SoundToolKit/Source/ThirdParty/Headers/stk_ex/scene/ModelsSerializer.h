///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 06.03.2019
///
#ifndef STK_EX__SCENE__MODEL_SERIALIZER__H
#define STK_EX__SCENE__MODEL_SERIALIZER__H

#include <utility>
#include <functional>
#include <stk/StringView.h>

namespace stk
{
	class ISoundToolKit;
	class IMesh;
	class IModel;
}

namespace stk_ex::scene
{
	/// <summary>
	/// A callback called for each mesh during model serialization.
	/// </summary>
	/// <param name="mesh">The mesh for which the callback is called.</param>
	/// <returns>The desired mesh name and mesh material name as a pair.</param>
	using SerializeModelNamesCallback = std::function<std::pair<stk::StringView, stk::StringView>(stk::IMesh& mesh)>;

	/// <summary>
	/// Serializes meshes from the given model to a text string in json format, which is accepted by ModelsLoader.
	/// </summary>
	/// <param name="model">The model to serialize.</param>
	/// <param name="namesCallback">A callback called for each mesh, should return pair(meshName, materialName).</param>
	/// <param name="outputCallback">A callback called with serialized meshes data.</param>
	void serializeModelJson(stk::ISoundToolKit& stk, stk::IModel& model,
		SerializeModelNamesCallback namesCallback, std::function<void(stk::StringView)> outputCallback);
}

#endif
