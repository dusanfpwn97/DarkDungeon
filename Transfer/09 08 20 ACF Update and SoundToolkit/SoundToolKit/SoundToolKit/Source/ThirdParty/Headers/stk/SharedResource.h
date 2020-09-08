///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 08.11.2018
///
#ifndef STK__SHARED_RESOURCE__H
#define STK__SHARED_RESOURCE__H

#include <cstddef>
#include "UniqueResource.h"

namespace stk
{
	/// <summary>
	/// A class which manages the ownership of some of STK-created resources.
	/// The resource must implement release() and addReference() methods to be used with SharedResource.
	/// </summary>
	template<class Resource>
	class SharedResource
	{
		// public sub-types
	public:
		using ElementType = Resource;
		using Pointer = Resource*;

		// public construction and destruction methods
	public:
		SharedResource() noexcept;
		SharedResource(Resource* resource) noexcept;
		~SharedResource();

		SharedResource(const SharedResource& other) noexcept;

		template<class OtherResource>
		SharedResource(const SharedResource<OtherResource>& other) noexcept;

		SharedResource(SharedResource&& other) noexcept;

		template<class OtherResource>
		SharedResource(SharedResource<OtherResource>&& other) noexcept;

		SharedResource& operator=(const SharedResource&) noexcept;

		template<class OtherResource>
		SharedResource& operator=(const SharedResource<OtherResource>&) noexcept;

		SharedResource& operator=(SharedResource&& other) noexcept;

		template<class OtherResource>
		SharedResource& operator=(SharedResource<OtherResource>&& other) noexcept;

		template<class OtherResource>
		SharedResource(UniqueResource<OtherResource>&& other) noexcept;

		template<class OtherResource>
		SharedResource& operator=(UniqueResource<OtherResource>&& other) noexcept;

		SharedResource& operator=(std::nullptr_t) noexcept;

		// public methods
	public:
		explicit operator bool() const noexcept {return m_resource != nullptr;}

		Resource& operator*() const {return *m_resource;}
		Resource* operator->() const noexcept {return m_resource;}

		Resource* get() const noexcept {return m_resource;}

		Resource* releaseOwnership() noexcept;

		// private properites
	private:
		Resource* m_resource;
	};

	template<class Resource1, class Resource2> inline bool operator==(const SharedResource<Resource1>& lhv, const SharedResource<Resource2>& rhv) {return lhv.get() == rhv.get();}
	template<class Resource1, class Resource2> inline bool operator!=(const SharedResource<Resource1>& lhv, const SharedResource<Resource2>& rhv) {return lhv.get() != rhv.get();}
	template<class Resource1, class Resource2> inline bool operator< (const SharedResource<Resource1>& lhv, const SharedResource<Resource2>& rhv) {return lhv.get() <  rhv.get();}
	template<class Resource1, class Resource2> inline bool operator> (const SharedResource<Resource1>& lhv, const SharedResource<Resource2>& rhv) {return lhv.get() >  rhv.get();}
	template<class Resource1, class Resource2> inline bool operator<=(const SharedResource<Resource1>& lhv, const SharedResource<Resource2>& rhv) {return lhv.get() <= rhv.get();}
	template<class Resource1, class Resource2> inline bool operator>=(const SharedResource<Resource1>& lhv, const SharedResource<Resource2>& rhv) {return lhv.get() >= rhv.get();}

	template<class Resource> inline bool operator==(const SharedResource<Resource>& lhv, std::nullptr_t) {return lhv.get() == nullptr;}
	template<class Resource> inline bool operator!=(const SharedResource<Resource>& lhv, std::nullptr_t) {return lhv.get() != nullptr;}
	template<class Resource> inline bool operator< (const SharedResource<Resource>& lhv, std::nullptr_t) {return lhv.get() <  nullptr;}
	template<class Resource> inline bool operator> (const SharedResource<Resource>& lhv, std::nullptr_t) {return lhv.get() >  nullptr;}
	template<class Resource> inline bool operator<=(const SharedResource<Resource>& lhv, std::nullptr_t) {return lhv.get() <= nullptr;}
	template<class Resource> inline bool operator>=(const SharedResource<Resource>& lhv, std::nullptr_t) {return lhv.get() >= nullptr;}

	template<class Resource> inline bool operator==(std::nullptr_t, const SharedResource<Resource>& rhv) {return nullptr == rhv.get();}
	template<class Resource> inline bool operator!=(std::nullptr_t, const SharedResource<Resource>& rhv) {return nullptr != rhv.get();}
	template<class Resource> inline bool operator< (std::nullptr_t, const SharedResource<Resource>& rhv) {return nullptr <  rhv.get();}
	template<class Resource> inline bool operator> (std::nullptr_t, const SharedResource<Resource>& rhv) {return nullptr >  rhv.get();}
	template<class Resource> inline bool operator<=(std::nullptr_t, const SharedResource<Resource>& rhv) {return nullptr <= rhv.get();}
	template<class Resource> inline bool operator>=(std::nullptr_t, const SharedResource<Resource>& rhv) {return nullptr >= rhv.get();}

	// The resource casts have functionality equivalent to std::static_pointer_cast and std::reinterpret_pointer_cast

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> staticResourceCast(const SharedResource<Resource>& resource);
	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> staticResourceCast(SharedResource<Resource>&& resource);

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> dynamicResourceCast(const SharedResource<Resource>& resource);
	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> dynamicResourceCast(SharedResource<Resource>&& resource);

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> reinterpretResourceCast(const SharedResource<Resource>& resource);
	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> reinterpretResourceCast(SharedResource<Resource>&& resource);

	// The sharedFromResource functions are equivalent to std::shared_from_this

	template<class Resource>
	inline SharedResource<Resource> sharedFromResource(Resource* resourcePointer);
	template<class Resource>
	inline SharedResource<Resource> sharedFromResource(Resource& resourceReference);
}

#include "SharedResource.inl"

#endif
