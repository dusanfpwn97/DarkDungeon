///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 15.11.2018
///
#ifndef STK__I_RESOURCE__H
#define STK__I_RESOURCE__H

#include <cstddef>

namespace stk
{
	template<class T> class UniqueResource;
	template<class T> class SharedResource;

	/// <summary>
	/// A base interface for any resource which can be either unique or shared, using reference counting.
	/// The class is designed to cooperate with automatic resource management: Unique- and SharedResource.
	/// </summary>
	class IResource
	{
		// public methods
	public:

		/// <summary>
		/// Releases the resource manually.
		/// Never call this method if the resource is managed by either Unique- or by SharedResource.
		/// </summary>
		inline void manualRelease() {release();}

		/// <summary>
		/// Increments the usage counter manually.
		/// Never call this method if the resource is managed by either Unique- or by SharedResource.
		/// </summary>
		/// <returns>The current number of references to the resource.</returns>
		inline size_t manualAddReference() {return addReference();}

		// protected construction and destruction methods
	protected:

		virtual ~IResource() = default;

		// protected methods
	protected:

		/// <summary>
		/// Releases the resource. Any further usage leads to undefined results.
		/// Called automatically by either UniqueResource or SharedResource.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Increments the usage counter.
		/// Called automatically when copying SharedResources.
		/// </summary>
		/// <returns>The current number of references to the resource.</returns>
		virtual size_t addReference() = 0;

		template<class T> friend class UniqueResource;
		template<class T> friend class SharedResource;
	};
}

#endif
