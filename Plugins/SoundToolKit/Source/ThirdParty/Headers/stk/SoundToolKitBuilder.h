///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 20.11.2018
///
#ifndef STK__SOUND_TOOL_KIT_BUILDER__H
#define STK__SOUND_TOOL_KIT_BUILDER__H

#include <cstdint>
#include <functional>
#include <stk/SharedResource.h>
#include <stk/SeverityLevel.h>
#include <stk/ArrayView.h>
#include <stk/StringView.h>

#if !defined(STK_API)
#	if defined(_USRDLL)
#		if defined(WIN32)
#			define STK_API __declspec(dllexport)
#		elif defined(__GNUC__)
#			define STK_API __attribute__ ((visibility ("default")))
#		else
#			define STK_API
#		endif
#	elif defined(_LIB) || defined(STK_USE_LIB)
#		define STK_API
#	else
#		define STK_API /*__declspec(dllimport)*/
#	endif
#endif

namespace stk
{
	class ISoundToolKit;
	class IAllocator;
	class IThreadPool;

	/// <summary>
	/// The SoundToolKit version.
	/// The major and minor parts are used to verify headers and library versions.
	/// </summary>
	struct Version
	{
		int major{1};
		int minor{0};
		int release{0};
	};

	/// <summary>
	/// Requests either a custom allocator (if customAllocator is not nullptr),
	/// or a default allocator otherwise.
	/// </summary>
	struct AllocatorRequest
	{
		IAllocator* customAllocator;
	};

	/// <summary>
	/// Requests either a custom thread pool (if customThreadPool is not nullptr),
	/// or a default thread pool with the specified number of threads otherwise.
	/// </summary>
	struct ThreadPoolRequest
	{
		IThreadPool* customThreadPool;
		size_t numberOfThreadsInDefaultThreadPool;
	};

	/// <summary>
	/// Maximum number of worker threads supported by default thread pool.
	/// </summary>
	constexpr size_t MaximumNumberOfThreads = 16u;

	/// <summary>
	/// Default number of worker threads to request if default thread pool is used.
	/// </summary>
	constexpr size_t DefaultNumberOfThreads = 1u;

	/// <summary>
	/// Requests a default allocator.
	/// </summary>
	/// <returns>The request to create a default allocator.</returns>
	inline AllocatorRequest requestDefaultAllocator() noexcept
	{
		return AllocatorRequest{nullptr};
	}

	/// <summary>
	/// Requests a default thread pool with the specified number of threads.
	/// </summary>
	/// <param name="numberOfThreads">The requested number of threads.</param>
	/// <note>numberOfThreads equal to 0 forces STK to work in synchronous mode.</note>
	/// <returns>The request to create a default thread pool.</returns>
	inline ThreadPoolRequest requestDefaultThreadPool(
		size_t numberOfThreads = DefaultNumberOfThreads) noexcept
	{
		return ThreadPoolRequest{nullptr, numberOfThreads};
	}

	/// <summary>
	/// Returns the thread pool request which forces the STK to run in synchronous mode.
	/// </summary>
	/// <returns>The request to run STK in synchronous mode.</returns>
	inline ThreadPoolRequest requestSynchronousMode() noexcept
	{
		return ThreadPoolRequest{nullptr, 0};
	}

	/// <summary>
	/// A function used as a callback for each log entry added.
	/// </summary>
	/// <param name="level">Severity level: info, warning, or error.</param>
	/// <param name="message>Textual log message.</param>
	using LogHandler = std::function<void(SeverityLevel level, StringView message)>;

	/// <summary>
	/// A definition of setting value which overrides setting default value.
	/// </summary>
	struct SettingDefinition
	{
		StringView name;
		StringView value;
	};

	/// <summary>
	/// A list of settings with requested values to override their default values with.
	/// </summary>
	using SettingsConfiguration = ArrayView<SettingDefinition>;

	/// <summary>
	/// Creates the SoundToolKit - a master STK resource.
	/// </summary>
	/// <param name="allocatorRequest">The allocator request for custom handling all allocations.</param>
	/// <param name="threadPoolRequest">The thread pool request for custom thread management.</param>
	/// <param name="logHandler">The optional callback which receives all log messages.</param>
	/// <param name="configuration">The optional override of default values of selected settings.</param>
	/// <param name="version">Used to verify if library version matches the headers version.</param>
	/// <returns>The created master STK resource or nullptr in case of an error.</returns>
	STK_API SharedResource<ISoundToolKit> createSoundToolKit(
		AllocatorRequest allocatorRequest = requestDefaultAllocator(),
		ThreadPoolRequest threadPoolRequest = requestDefaultThreadPool(),
		LogHandler logHandler = LogHandler{},
		SettingsConfiguration configuration = SettingsConfiguration{},
		Version version = Version{});
}

#endif
