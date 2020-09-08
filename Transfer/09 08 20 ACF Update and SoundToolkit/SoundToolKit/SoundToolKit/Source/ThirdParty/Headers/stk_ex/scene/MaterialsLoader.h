///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.05.2019
///
#ifndef STK_EX__SCENE__MATERIALS_LOADER__H
#define STK_EX__SCENE__MATERIALS_LOADER__H

#include <functional>
#include <stk/StringView.h>
#include <stk/SharedResource.h>

namespace stk
{
	class ISoundToolKit;
	class IMaterial;
}

namespace stk_ex::scene
{
	/// <summary>
	/// Loads a material from a given string.
	/// </summary>
	/// <param name="stk">The SoundToolKit interface used to create resources.</param>
	/// <param name="materialData">The string containing the material definition.</param>
	/// <returns>The loaded material if data was loaded correctly, or null pointer otherwise.</returns>
	stk::SharedResource<stk::IMaterial> loadMaterialJsonFromMemory(stk::ISoundToolKit& stk, stk::StringView materialData);

	/// <summary>
	/// Loads a material contained in a specified file in JSON format.
	/// </summary>
	/// <param name="stk">The SoundToolKit interface used to create resources.</param>
	/// <param name="filePath">A path to the file containing the material definition.</param>
	/// <returns>The loaded material if data was loaded correctly, or null pointer otherwise.</returns>
	stk::SharedResource<stk::IMaterial> loadMaterialJsonFromFile(stk::ISoundToolKit& stk, stk::StringView filePath);
}

#endif
