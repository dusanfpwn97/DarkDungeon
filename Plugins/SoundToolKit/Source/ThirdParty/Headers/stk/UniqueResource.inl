///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 08.11.2018
///

namespace stk
{
	template<class Resource>
	UniqueResource<Resource>::UniqueResource() noexcept: m_resource(nullptr)
	{
	}

	template<class Resource>
	UniqueResource<Resource>::UniqueResource(Resource* resource) noexcept: m_resource(resource)
	{
	}

	template<class Resource>
	UniqueResource<Resource>::~UniqueResource()
	{
		if (m_resource)
		{
			m_resource->release();
		}
	}

	template<class Resource>
	UniqueResource<Resource>::UniqueResource(UniqueResource&& other) noexcept: m_resource(other.releaseOwnership())
	{
	}

	template<class Resource>
	template<class OtherResource>
	UniqueResource<Resource>::UniqueResource(UniqueResource<OtherResource>&& other) noexcept: m_resource(other.releaseOwnership())
	{
	}

	template<class Resource>
	UniqueResource<Resource>& UniqueResource<Resource>::operator=(UniqueResource&& other) noexcept
	{
		if (m_resource)
		{
			m_resource->release();
		}
		m_resource = other.releaseOwnership();
		return *this;
	}

	template<class Resource>
	template<class OtherResource>
	UniqueResource<Resource>& UniqueResource<Resource>::operator=(UniqueResource<OtherResource>&& other) noexcept
	{
		if (m_resource)
		{
			m_resource->release();
		}
		m_resource = other.releaseOwnership();
		return *this;
	}

	template<class Resource>
	UniqueResource<Resource>& UniqueResource<Resource>::operator=(std::nullptr_t) noexcept
	{
		if (m_resource)
		{
			m_resource->release();
			m_resource = nullptr;
		}
		return *this;
	}

	template<class Resource>
	Resource* UniqueResource<Resource>::releaseOwnership() noexcept
	{
		Resource* result = m_resource;
		m_resource = nullptr;
		return result;
	}

	template<class OtherResource, class Resource>
	inline UniqueResource<OtherResource> staticResourceCast(UniqueResource<Resource>&& resource)
	{
		return UniqueResource<OtherResource>(static_cast<OtherResource*>(resource.releaseOwnership()));
	}

	template<class OtherResource, class Resource>
	inline UniqueResource<OtherResource> dynamicResourceCast(UniqueResource<Resource>&& resource)
	{
		return UniqueResource<OtherResource>(dynamic_cast<OtherResource*>(resource.releaseOwnership()));
	}

	template<class OtherResource, class Resource>
	inline UniqueResource<OtherResource> reinterpretResourceCast(UniqueResource<Resource>&& resource)
	{
		return UniqueResource<OtherResource>(reinterpret_cast<OtherResource*>(resource.releaseOwnership()));
	}
}
