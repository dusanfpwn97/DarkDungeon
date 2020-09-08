///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.05.2019
///
#ifndef STK_EX__DIAGNOSTICS__I_DIAGNOSTICS__H
#define STK_EX__DIAGNOSTICS__I_DIAGNOSTICS__H

#include <functional>
#include <stk/UniqueResource.h>
#include <stk/SharedResource.h>
#include <stk/ArrayView.h>
#include <stk/StringView.h>
#include <stk/IConnection.h>

namespace stk
{
	class ISoundToolKit;
}

namespace stk_ex::diagnostics
{
	/// <summary>
	/// An interface containing various diagnostics methods.
	/// </summary>
	class IDiagnostics
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called by diagnosticsGetMemoryInfo function.
		/// </summary>
		/// <param name="block">The address of the allocated block.</param>
		/// <param name="size">The size of the allocated block.</param>
		/// <param name="alignment">The alignment of the allocated block.</param>
		/// <param name="file">File in which the allocation occured.</param>
		/// <param name="line">Line at which the allocation occured.</param>
		using OnDiagnosticsBlockInfo = std::function<void(
			void* block, size_t size, size_t alignment, stk::StringView file, int line)>;

		/// <summary>
		/// A handler called with samples on diagnostics output.
		/// </summary>
		/// <param name="samples">A view to the diagnostics data.</param>
		using DiagnosticsOutputHandler = std::function<void(stk::ArrayView<float> samples)>;

		// public construction and destruction methods
	public:

		/// <summary>
		/// Creates the diagnostics interface.
		/// </summary>
		/// <param name="stk">The main STK interface used to query for the diagnositcs data.</param>
		/// <returns>The newly created Diagnostics or NULL pointer in case of an error.</param>
		static stk::UniqueResource<IDiagnostics> create(stk::SharedResource<stk::ISoundToolKit> stk);

		// public methods
	public:

		/// <summary>
		/// Releases the Diagnostics.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Calls the given callback for each STK-allocated block.
		/// This method is active if and only if STK is created with DefaultAllocator and MEMORY_DIAGNOSTICS is enabled.
		/// </summary>
		/// <param name="callback">A callback called for each block.</param>
		/// <note>As memory management is still work in progress, not all STK-allocated memory would be listed.</note>
		virtual void getMemoryInfo(OnDiagnosticsBlockInfo callback) = 0;

		/// <summary>
		/// Connects a handler which would be called with diagnostics output samples.
		/// </summary>
		/// <param name="outputName">The name of the diagnostics output.</param>
		/// <param name="handler">The handler called repeatedly with diagnostics samples.</param>
		virtual stk::UniqueResource<stk::IConnection> connectToDiagnosticsOutput(
			stk::StringView outputName, DiagnosticsOutputHandler handler) = 0;

		/// <summary>
		/// Disconnects all diagnostics handlers fron the given diagnostics output.
		/// </summary>
		/// <param name="outputName">The name of the diagnostics output.</param>
		virtual void disconnectAllDiagnosticsHandlers(stk::StringView outputName) = 0;

		// protected construction and destruction methods
	protected:

		~IDiagnostics() = default;
	};
}

#endif
