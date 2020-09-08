///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 25.11.2018
///
#ifndef STK__I_SAMPLE_STREAMING__H
#define STK__I_SAMPLE_STREAMING__H

#include "AudioBufferInterleavedView.h"
#include "AudioBufferDeinterleavedView.h"
#include "ISample.h"

namespace stk
{
	/// <summary>
	/// Implements a streaming sample data source. Contrary to the StaticSample, which represents an immutable
	/// buffer of raw samples data, the StreamingSample consumes sample data as they are provided to the interface.
	/// </summary>
	class ISampleStreaming: public virtual ISample
	{
		// public methods
	public:
		/// <summary>
		/// Streams (enqueues) samples.
		/// </summary>
		/// <param name="samples">View on an interleaved buffer of samples.</param>
		virtual void enqueueSamples(AudioBufferInterleavedView audioBufferView) = 0;

		/// <summary>
		/// Streams (enqueues) samples.
		/// </summary>
		/// <param name="samples">View on buffers of samples.</param>
		virtual void enqueueSamples(AudioBufferDeinterleavedView audioBufferView) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ISampleStreaming() = default;
	};
}

#endif
