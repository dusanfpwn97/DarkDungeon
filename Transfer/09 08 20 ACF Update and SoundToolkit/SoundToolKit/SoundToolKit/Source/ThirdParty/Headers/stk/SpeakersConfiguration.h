///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.12.2018
///
#ifndef STK__SPEAKERS_CONFIGURATION__H
#define STK__SPEAKERS_CONFIGURATION__H

#include <utility>
#include <functional>

namespace stk
{
	/// <summary>
	/// The speakers configurations supported by the STK.
	/// </summary>
	enum class SpeakersConfiguration: int
	{
		Headphones = 0,
		Mono = 1,
		SpeakersStereo = 2,
		Speakers_3_1 = 3,
		Speakers_5_1 = 5,
		Speakers_7_1 = 7
	};

	/// <summary>
	/// Obtains the required number of channels for a given speakers configuration.
	/// </summary>
	/// <param name="configuration">The given speakers configuration.</param>
	/// <returns>The number of channels required by the given speakers configuration,
	/// or 0 if the configuration enumerator is invalid.</returns>
	constexpr size_t channelsCountForSpeakersConfiguration(SpeakersConfiguration configuration)
	{
		switch (configuration)
		{
		case SpeakersConfiguration::Headphones:
			return 2;
		case SpeakersConfiguration::Mono:
			return 1;
		case SpeakersConfiguration::SpeakersStereo:
			return 2;
		case SpeakersConfiguration::Speakers_3_1:
			return 4;
		case SpeakersConfiguration::Speakers_5_1:
			return 6;
		case SpeakersConfiguration::Speakers_7_1:
			return 8;
		}
		return 0;
	}

	/// <summary>
	/// Obtains the speakers configuration for the given number of channels.
	/// If number of channels is 2, either calls the given callback and returns its returned value,
	/// or prefers Headphones over SpeakersStereo, if the callback is null.
	/// </summary>
	/// <param name="channelsCount">The requested number of channels.</param>
	/// <param name="callbackForTwoChannels">The callback called when the number of channels is two.
	/// The callback must return either Headphones or SpeakersStereo, otherwise the behaviour is undefined.</param>
	/// <returns>The pair (speakers configuration which has the requested number of channels, true),
	/// if such configuration is supported by STK, or (undefined, false) otherwise.</returns>
	inline std::pair<SpeakersConfiguration, bool> speakersConfigurationForChannelsCount(size_t channelsCount,
		std::function<SpeakersConfiguration()> callbackForTwoChannels = nullptr)
	{
		switch (channelsCount)
		{
		case 1:
			return std::make_pair(stk::SpeakersConfiguration::Mono, true);
		case 2:
			return std::make_pair(callbackForTwoChannels ? callbackForTwoChannels() : SpeakersConfiguration::Headphones, true);
		case 4:
			return std::make_pair(stk::SpeakersConfiguration::Speakers_3_1, true);
		case 6:
			return std::make_pair(stk::SpeakersConfiguration::Speakers_5_1, true);
		case 8:
			return std::make_pair(stk::SpeakersConfiguration::Speakers_7_1, true);
		}
		return std::make_pair(SpeakersConfiguration::Headphones, false);
	}
}

#endif
