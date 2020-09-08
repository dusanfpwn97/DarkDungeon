///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 08.11.2018
///
#ifndef STK__UNIQUE_RESOURCE__H
#define STK__UNIQUE_RESOURCE__H

#include <cstddef>

namespace stk
{
	/// <summary>
	/// A class which manages the ownership of some of STK-created resources.
	/// The resource must implement release() method to be used with UniqueResource.
	/// </summary>
	template<class Resource>
	class UniqueResource
	{
		// public sub-types
	public:
		using ElementType = Resource;
		using Pointer = Resource*;

		// public construction and destruction methods
	public:
		UniqueResource() noexcept;
		UniqueResource(Resource* resource) noexcept;
		~UniqueResource();

		UniqueResource(const UniqueResource&) = delete;
		UniqueResource& operator=(const UniqueResource&) = delete;

		UniqueResource(UniqueResource&& other) noexcept;

		template<class OtherResource>
		UniqueResource(UniqueResource<OtherResource>&& other) noexcept;

		UniqueResource& operator=(UniqueResource&& other) noexcept;

		template<class OtherResource>
		UniqueResource& operator=(UniqueResource<OtherResource>&& other) noexcept;

		UniqueResource& operator=(std::nullptr_t) noexcept;

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

	template<class Resource1, class Resource2> inline bool operator==(const UniqueResource<Resource1>& lhv, const UniqueResource<Resource2>& rhv) {return lhv.get() == rhv.get();}
	template<class Resource1, class Resource2> inline bool operator!=(const UniqueResource<Resource1>& lhv, const UniqueResource<Resource2>& rhv) {return lhv.get() != rhv.get();}
	template<class Resource1, class Resource2> inline bool operator< (const UniqueResource<Resource1>& lhv, const UniqueResource<Resource2>& rhv) {return lhv.get() <  rhv.get();}
	template<class Resource1, class Resource2> inline bool operator> (const UniqueResource<Resource1>& lhv, const UniqueResource<Resource2>& rhv) {return lhv.get() >  rhv.get();}
	template<class Resource1, class Resource2> inline bool operator<=(const UniqueResource<Resource1>& lhv, const UniqueResource<Resource2>& rhv) {return lhv.get() <= rhv.get();}
	template<class Resource1, class Resource2> inline bool operator>=(const UniqueResource<Resource1>& lhv, const UniqueResource<Resource2>& rhv) {return lhv.get() >= rhv.get();}

	template<class Resource> inline bool operator==(const UniqueResource<Resource>& lhv, std::nullptr_t) {return lhv.get() == nullptr;}
	template<class Resource> inline bool operator!=(const UniqueResource<Resource>& lhv, std::nullptr_t) {return lhv.get() != nullptr;}
	template<class Resource> inline bool operator< (const UniqueResource<Resource>& lhv, std::nullptr_t) {return lhv.get() <  nullptr;}
	template<class Resource> inline bool operator> (const UniqueResource<Resource>& lhv, std::nullptr_t) {return lhv.get() >  nullptr;}
	template<class Resource> inline bool operator<=(const UniqueResource<Resource>& lhv, std::nullptr_t) {return lhv.get() <= nullptr;}
	template<class Resource> inline bool operator>=(const UniqueResource<Resource>& lhv, std::nullptr_t) {return lhv.get() >= nullptr;}

	template<class Resource> inline bool operator==(std::nullptr_t, const UniqueResource<Resource>& rhv) {return nullptr == rhv.get();}
	template<class Resource> inline bool operator!=(std::nullptr_t, const UniqueResource<Resource>& rhv) {return nullptr != rhv.get();}
	template<class Resource> inline bool operator< (std::nullptr_t, const UniqueResource<Resource>& rhv) {return nullptr <  rhv.get();}
	template<class Resource> inline bool operator> (std::nullptr_t, const UniqueResource<Resource>& rhv) {return nullptr >  rhv.get();}
	template<class Resource> inline bool operator<=(std::nullptr_t, const UniqueResource<Resource>& rhv) {return nullptr <= rhv.get();}
	template<class Resource> inline bool operator>=(std::nullptr_t, const UniqueResource<Resource>& rhv) {return nullptr >= rhv.get();}

	// The resource casts have functionality equivalent to std::static_pointer_cast, dynamic_pointer_cast, and std::reinterpret_pointer_cast

	template<class OtherResource, class Resource>
	inline UniqueResource<OtherResource> staticResourceCast(UniqueResource<Resource>&& resource);

	template<class OtherResource, class Resource>
	inline UniqueResource<OtherResource> dynamicResourceCast(UniqueResource<Resource>&& resource);

	template<class OtherResource, class Resource>
	inline UniqueResource<OtherResource> reinterpretResourceCast(UniqueResource<Resource>&& resource);
}

#include "UniqueResource.inl"

#endif
