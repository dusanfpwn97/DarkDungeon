///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 20.11.2018
///
#ifndef STK__I_SOUND_TOOL_KIT__H
#define STK__I_SOUND_TOOL_KIT__H

#include <cstddef>
#include "IResource.h"
#include "ArrayView.h"
#include "UniqueResource.h"

namespace stk
{
	class IControl;
	class IResourcesFactory;
	class IAudioOutput;
	class IScene;
	class IFence;

	/// <summary>
	/// The main interface for controlling the SoundToolKit Audio Engine. It is responsible for:
	/// - creating other STK resources, which are different scene building blocks,
	/// - obtaining the output sound,
	/// - configuring the overall engine behavior,
	/// - querying the engine state, communicated through events ans status indicators.
	/// </summary>
	class ISoundToolKit: public IResource
	{
		// public methods
	public:
		/// <summary>
		/// Obtains the reference for Control, which allows to adjust STK Settings, observe Indicators, and receive Logs.
		/// </summary>
		/// <returns>The reference for STK control interface.</returns>
		virtual IControl& control() = 0;

		/// <summary>
		/// Obtains the reference for Resources Factory, which is responsible for creating all STK managed resources.
		/// </summary>
		/// <returns>The reference for Resources Factory interface.</returns>
		virtual IResourcesFactory& resourcesFactory() = 0;

		/// <summary>
		/// Obtains the reference for Audio Output, which controls audio output and provides the output sound data.
		/// </summary>
		/// <returns>The reference for Audio Output interface.</returns>
		virtual IAudioOutput& audioOutput() = 0;

		/// <summary>
		/// Obtains the reference for Scene, which controls Receiver and Models.
		/// </summary>
		/// <returns>The reference for Scene interface.</returns>
		virtual IScene& scene() = 0;

		/// <summary>
		/// Sets the diffraction data. Must be called before first diffraction effect is created.
		/// </summary>
		virtual void setDiffractionData(ArrayView<std::byte> data) = 0;

		/// <summary>
		/// Updates sound paths, which connect sound sources with receiver through variety of acoustic phenomena,
		/// like reflection, transmission, or diffraction.
		/// </summary>
		virtual void computeSoundFrame() = 0;

		/// <summary>
		/// If the engine works in asynchronous mode, starts execution of all the commands issued
		/// to the STK engine so far and returns. Otherwise, actually executes all of these commands.
		/// </summary>
		virtual void flush() = 0;

		/// <summary>
		/// Starts commands execution and blocks (does not return) until all commands issued before finish() are executed.
		/// </summary>
		virtual void finish() = 0;

		/// <summary>
		/// Appends a fence to the engine commands stream.
		/// The fence allows to wait until all commands issued before the fence are finished.
		/// The fence must be released when is no longer needed.
		/// </summary>
		/// <returns>The fence on which wait can be performed.</returns>
		virtual UniqueResource<IFence> fenceSynchronize() = 0;

		/// <returns>
		/// False if the engine is in an error state.
		/// </returns>
		virtual bool good() const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ISoundToolKit() = default;
	};
}

#endif
