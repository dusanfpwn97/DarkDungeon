///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.12.2018
///
#ifndef STK__I_AUDIO_OUTPUT__H
#define STK__I_AUDIO_OUTPUT__H

#include <cstddef>
#include "ArrayView.h"
#include "Math.h"
#include "AudioBufferInterleavedView.h"
#include "AudioBufferDeinterleavedView.h"
#include "SpeakersConfiguration.h"

namespace stk
{
	class ISourceAmbientSeparatelyOutput;
	class ISourceSpatialSeparatelyOutput;

	/// <summary>
	/// Allows to retrieve rendered audio samples as well as control how samples are rendered.
	/// </summary>
	class IAudioOutput
	{
		// public methods
	public:

		/// <summary>
		/// Sets speakers configuration of the STK. The speakers configuration determines the number of channels
		/// of the STK audio output and spatialization method: stereo, VBAP, or Surround.
		/// </summary>
		/// <param name="configuration">The speakers configuration to set.</param>
		virtual void setSpeakersConfiguration(SpeakersConfiguration configuration) = 0;

		/// <summary>
		/// Gets the current speakers channel configuration.
		/// </summary>
		/// <returns>The currently used speakers configuration.</returns>
		virtual SpeakersConfiguration speakersConfiguration() const = 0;

		/// <summary>
		/// Overrides the default directions from listener to speakers in surround sound speakers configuration.
		/// </summary>
		/// <param name="directions">The directions to set (not necessarily normalized).</param>
		/// <note>The valid sizes of directions array must match the SpeakersConfiguration Speakers* enumerators,
		/// i.e. the sizes are 2, 3, 5, or 7, for Stereo, 3.1, 5.1, or 7.1, respectively.</note>
		/// <note>The default values are defined to achieve the surround speakers setup recommended by Dolby.</note>
		virtual void setSpeakersDirections(ArrayView<vec3> directions) = 0;

		/// <summary>
		/// Resets the directions from listener to speakers to default values for requested speakers configuration.
		/// The default values are defined to achieve the surround speakers setup recommended by Dolby.
		/// </summary>
		/// <param name="speakersCount">The number of high frequency speakers in configuration, e.g. 7 for 7.1.</param>
		/// <note>The valid values of speakersCount must match the SpeakersConfiguration Speakers* enumerators,
		/// i.e. the sizes are 2, 3, 5, or 7, for Stereo, 3.1, 5.1, or 7.1, respectively.</note>
		virtual void resetSpeakersDirections(size_t speakersCount) = 0;

		/// <summary>
		/// Retruns the speakers directions for the requested speakers configuration, identified by speakersCount,
		/// either the default or the overridden one.
		/// </summary>
		/// <param name="speakersCount">The number of high frequency speakers in configuration, e.g. 7 for 7.1.</param>
		/// <returns>The directions to speakers or null view if requested configuration is not supported.</param>
		/// <note>The valid values of speakersCount must match the SpeakersConfiguration Speakers* enumerators,
		/// i.e. the sizes are 2, 3, 5, or 7, for Stereo, 3.1, 5.1, or 7.1, respectively.</note>
		/// <note>The default values are defined to achieve the surround speakers setup recommended by Dolby.</note>
		virtual ArrayView<vec3> speakersDirections(size_t speakersCount) const = 0;

		/// <summary>
		/// Sets the boundary for frequencies - frequencies above the boundary are spatialized, and frequencies below
		/// are not - signal containing those is passed to low-frequency output channel as is. The configuration is
		/// active only if surround sound is selected as speakers configuration, i.e. for Speakers 3.1, 5.1, and 7.1.
		/// </summary>
		/// <param name="frequency">The frequency to set, in 20Hz-20kHz range, with 80Hz being default.</param>
		virtual void setCrossoverFrequency(float frequency) = 0;

		/// <summary>
		/// Gets the frequency boundary for frequencies which are spatialized and not in x.1 speakers configurations.
		/// </summary>
		/// <returns>The obtainted crossover frequency.</summary>
		virtual float crossoverFrequency() const = 0;

		/// <summary>
		/// Enables HRTF support.
		/// </summary>
		/// <note>This setting is active if and only if speakers configuration is configured to headphones.</note>
		/// <note>The HRTF data must be set before enabling HRTF, otherwise no sound output would be produced.</note>
		virtual void enableHrtf() = 0;

		/// <summary>
		/// Disables HRTF support.
		/// </summary>
		virtual void disableHrtf() = 0;

		/// <summary>
		/// Checks if HRTF support is enabled.
		/// </summary>
		/// <returns>True if HRTF support is enabled, false otherwise.</summary>
		virtual bool isHrtfEnabled() const = 0;

		/// <summary>
		/// Sets the HRTF data. Must be called before enabling HRTF.
		/// </summary>
		/// <param name="data">The HRTF data to set.</param>
		virtual void setHrtfData(ArrayView<std::byte> data) = 0;

		/// <summary>
		/// Sets the sampling rate of the audio output.
		/// </summary>
		/// <param name="rate">Sampling rate to set, in Hz.</param>
		virtual void setSamplingRate(float rate) = 0;

		/// <summary>
		/// Gets the current sampling rate of the audio output.
		/// </summary>
		/// <returns>The currently used sampling rate on the audio output, in Hz.</returns>
		virtual float samplingRate() const = 0;

		/// <summary>
		/// Sets master volume of the audio output. The STK engine uses hierarchical volume representation,
		/// i.e. master, sound source class, sound source, and playback. The final volume to scale the sound in a
		/// specific playback is affected by multiplication of the volume at all of these four volumes.
		/// </summary>
		/// <param name="volume">The volume to set. Must be a finite, non-negative value.</param>
		virtual void setMasterVolume(float volume) = 0;

		/// <summary>
		/// Gets the master STK volume.
		/// </summary>
		/// <returns>The current master STK volume.</returns>
		virtual float masterVolume() const = 0;

		/// <summary>
		/// Prepares the synthesis engine for rendering: allocates internal resources, buffers etc. This method
		/// should be called before first call to render() with sufficient number of samples specified to
		/// ensure no memory allocations will occur during rendering.
		/// </summary>
		/// <note>If not called prior or length of the buffer requested from renderSamples() is larger than
		/// maxExpectedBufferLength, then prepareForRender would be called internally.</note>
		/// <param name="maximumNumberOfSamples">Maximum number of samples requested in calls to renderSamples().</param>
		virtual void prepareForRender(size_t maximumNumberOfSamples) = 0;

		/// <summary>
		/// Request STK to render given number of samples.
		/// Rendered samples can be obtained via getSamples() or getSamplesInterleaved() method.
		/// </summary>
		/// <param name="numberOfSamples">The number of samples per channel that is requested to be rendered.</param>
		virtual void render(size_t numberOfSamples) = 0;

		/// <summary>
		/// Obtaines view for internal buffer of samples rendered via render() method. Sound emitted from all
		/// active and audible sound sources is mixed according to the speakers configuration and other settings.
		/// </summary>
		/// <returns>The view on internal non-interleaved buffer containing the rendered samples.
		/// The view is valid until the next render() call.</returns>
		virtual AudioBufferDeinterleavedView getSamples() const = 0;

		/// <summary>
		/// Obtaines view for internal buffer of samples rendered via render() method. Sound emitted from all
		/// active and audible sound sources is mixed according to the speakers configuration and other settings.
		/// </summary>
		/// <returns>The view on internal interleaved buffer containing the rendered samples.
		/// The view is valid until the next render() call.</returns>
		virtual AudioBufferInterleavedView getSamplesInterleaved() const = 0;

		/// <summary>
		/// Obtaines view for internal buffer of samples rendered via render() method for specified ambient sound source.
		/// </summary>
		/// <param name="separatelyOutputAmbientSource">The ambient sound source for which samples should be returned.</param>
		/// <returns>The view on internal non-interleaved buffer containing the source's rendered samples.
		/// The view is valid until the next render() call.</returns>
		virtual AudioBufferDeinterleavedView getSamples(const ISourceAmbientSeparatelyOutput& separatelyOutputAmbientSource) const = 0;

		/// <summary>
		/// Obtaines view for internal buffer of samples rendered via render() method for specified ambient sound source.
		/// </summary>
		/// <param name="separatelyOutputAmbientSource">The ambient sound source for which samples should be returned.</param>
		/// <returns>The view on internal interleaved buffer containing the source's rendered samples.
		/// The view is valid until the next render() call.</returns>
		virtual AudioBufferInterleavedView getSamplesInterleaved(const ISourceAmbientSeparatelyOutput& separatelyOutputAmbientSource) const = 0;

		/// <summary>
		/// Obtaines view for internal buffer of samples rendered via render() method for specified spatial sound source.
		/// </summary>
		/// <param name="separatelyOutputSpatialSource">The spatial sound source for which samples should be returned.</param>
		/// <returns>The view on internal non-interleaved buffer containing the source's rendered samples.
		/// The view is valid until the next render() call.</returns>
		virtual AudioBufferDeinterleavedView getSamples(const ISourceSpatialSeparatelyOutput& separatelyOutputSpatialSource) const = 0;

		/// <summary>
		/// Obtaines view for internal buffer of samples rendered via render() method for specified spatial sound source.
		/// </summary>
		/// <param name="separatelyOutputSpatialSource">The spatial sound source for which samples should be returned.</param>
		/// <returns>The view on internal interleaved buffer containing the source's rendered samples.
		/// The view is valid until the next render() call.</returns>
		virtual AudioBufferInterleavedView getSamplesInterleaved(const ISourceSpatialSeparatelyOutput& separatelyOutputSpatialSource) const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IAudioOutput() = default;
	};
}

#endif
