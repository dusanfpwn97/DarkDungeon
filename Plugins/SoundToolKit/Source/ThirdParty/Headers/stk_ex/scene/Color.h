///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 20.03.2019
///
#ifndef STK_EX__SCENE__COLOR__H
#define STK_EX__SCENE__COLOR__H

namespace stk_ex::scene
{
	/// <summary>
	/// An RGB color representation used to save/load visual representation of acoustic meshes in scene.
	/// <summary>
	struct Color
	{
		float r;
		float g;
		float b;
	};
}

#endif
