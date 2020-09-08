///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 16.04.2019
///
#ifndef STK_EX__SCENE__SCENE_SERIALIZER__H
#define STK_EX__SCENE__SCENE_SERIALIZER__H

#include <functional>
#include <stk/StringView.h>

namespace stk
{
	class ISoundToolKit;
}

namespace stk_ex::scene
{
	class ISceneDescription;

	/// <summary>
	/// Serializes the scene description to a string in json format. This function serializes just the scene description,
	/// without any saving or verification if individual resources files are available under given file paths.
	/// </summary>
	/// <param name="stk">The main Sound Tool Kit interface.</param>
	/// <param name="sceneDescription">The scene description containing all scene elements to serialize.</param>
	/// <param name="callback">A callback called with the serialized scene description.</param>
	void serializeSceneJson(stk::ISoundToolKit& stk, const ISceneDescription& sceneDescription,
		std::function<void(stk::StringView)> callback);
}

#endif
