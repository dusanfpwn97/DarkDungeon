///
/// \author Michal Majewski <michal.majewski@techmo.pl>
/// \date 07.01.2019
///
#ifndef STK_EX__SCENE__MATERIALS_SERIALIZER__H
#define STK_EX__SCENE__MATERIALS_SERIALIZER__H

#include <functional>
#include <stk/StringView.h>

namespace stk
{
	class IMaterial;
	class ISoundToolKit;
}

namespace stk_ex::scene
{
	/// <summary>
	/// Serializes a material to a text string in json format, which is accepted by MaterialLoader.
	/// </summary>
	/// <param name="material">The material to serialize.</param>
	/// <param name="callback">A callback called with serialized material data.</param>
	void serializeMaterialJson(stk::ISoundToolKit& stk, stk::IMaterial& material,
		std::function<void(stk::StringView)> callback);
}

#endif
