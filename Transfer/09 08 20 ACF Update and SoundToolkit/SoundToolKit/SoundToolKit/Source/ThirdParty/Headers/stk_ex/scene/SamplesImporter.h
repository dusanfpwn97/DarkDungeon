///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 05.12.2018
///
#ifndef STK_EX__SCENE__SAMPLES_IMPORTER__H
#define STK_EX__SCENE__SAMPLES_IMPORTER__H

#include <stk/StringView.h>
#include <stk/SharedResource.h>
#include <stk/ISampleStatic.h>

namespace stk
{
	class ISoundToolKit;
}

namespace stk_ex::scene
{
	/// <summary>
	/// Import a sample contained in the specified file in some well-known format.
	/// The implementation is based on FFMpeg Library.
	/// <summary>
	/// <param name="stk">A SoundToolKit interface to create the sample.</param>
	/// <param name="path">A path to a file containing the sound data.</param>
	/// <returns>The loaded sample if data was loaded correctly, or null pointer otherwise.</returns>
	stk::SharedResource<stk::ISampleStatic> importSample(
		stk::ISoundToolKit& stk, stk::StringView filePath);
}

#endif
