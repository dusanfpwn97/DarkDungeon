///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 08.11.2018
///

namespace stk
{
	template<class Resource>
	SharedResource<Resource>::SharedResource() noexcept: m_resource(nullptr)
	{
	}

	template<class Resource>
	SharedResource<Resource>::SharedResource(Resource* resource) noexcept: m_resource(resource)
	{
	}

	template<class Resource>
	SharedResource<Resource>::~SharedResource()
	{
		if (m_resource)
		{
			m_resource->release();
		}
	}

	template<class Resource>
	SharedResource<Resource>::SharedResource(const SharedResource& other) noexcept: m_resource(other.get())
	{
		if (m_resource)
		{
			m_resource->addReference();
		}
	}

	template<class Resource>
	template<class OtherResource>
	SharedResource<Resource>::SharedResource(const SharedResource<OtherResource>& other) noexcept: m_resource(other.get())
	{
		if (m_resource)
		{
			m_resource->addReference();
		}
	}

	template<class Resource>
	SharedResource<Resource>::SharedResource(SharedResource&& other) noexcept: m_resource(other.releaseOwnership())
	{
	}

	template<class Resource>
	template<class OtherResource>
	SharedResource<Resource>::SharedResource(SharedResource<OtherResource>&& other) noexcept: m_resource(other.releaseOwnership())
	{
	}

	template<class Resource>
	template<class OtherResource>
	SharedResource<Resource>::SharedResource(UniqueResource<OtherResource>&& other) noexcept: m_resource(other.releaseOwnership())
	{
	}

	template<class Resource>
	SharedResource<Resource>& SharedResource<Resource>::operator=(const SharedResource& other) noexcept
	{
		if (m_resource != other.get())
		{
			if (m_resource)
			{
				m_resource->release();
			}
			m_resource = other.get();
			if (m_resource)
			{
				m_resource->addReference();
			}
		}
		return *this;
	}

	template<class Resource>
	template<class OtherResource>
	SharedResource<Resource>& SharedResource<Resource>::operator=(const SharedResource<OtherResource>& other) noexcept
	{
		if (m_resource != other.get())
		{
			if (m_resource)
			{
				m_resource->release();
			}
			m_resource = other.get();
			if (m_resource)
			{
				m_resource->addReference();
			}
		}
		return *this;
	}

	template<class Resource>
	SharedResource<Resource>& SharedResource<Resource>::operator=(SharedResource&& other) noexcept
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
	SharedResource<Resource>& SharedResource<Resource>::operator=(SharedResource<OtherResource>&& other) noexcept
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
	SharedResource<Resource>& SharedResource<Resource>::operator=(UniqueResource<OtherResource>&& other) noexcept
	{
		if (m_resource)
		{
			m_resource->release();
		}
		m_resource = other.releaseOwnership();
		return *this;
	}

	template<class Resource>
	SharedResource<Resource>& SharedResource<Resource>::operator=(std::nullptr_t) noexcept
	{
		if (m_resource)
		{
			m_resource->release();
			m_resource = nullptr;
		}
		return *this;
	}

	template<class Resource>
	Resource* SharedResource<Resource>::releaseOwnership() noexcept
	{
		Resource* result = m_resource;
		m_resource = nullptr;
		return result;
	}

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> staticResourceCast(const SharedResource<Resource>& resource)
	{
		auto casted = static_cast<OtherResource*>(resource.get());
		casted->addReference();
		return SharedResource<OtherResource>(casted);
	}

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> staticResourceCast(SharedResource<Resource>&& resource)
	{
		return SharedResource<OtherResource>(static_cast<OtherResource*>(resource.releaseOwnership()));
	}

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> dynamicResourceCast(const SharedResource<Resource>& resource)
	{
		auto casted = dynamic_cast<OtherResource*>(resource.get());
		casted->addReference();
		return SharedResource<OtherResource>(casted);
	}

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> dynamicResourceCast(SharedResource<Resource>&& resource)
	{
		return SharedResource<OtherResource>(dynamic_cast<OtherResource*>(resource.releaseOwnership()));
	}

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> reinterpretResourceCast(const SharedResource<Resource>& resource)
	{
		auto casted = reinterpret_cast<OtherResource*>(resource.get());
		casted->addReference();
		return SharedResource<OtherResource>(casted);
	}

	template<class OtherResource, class Resource>
	inline SharedResource<OtherResource> reinterpretResourceCast(SharedResource<Resource>&& resource)
	{
		return SharedResource<OtherResource>(reinterpret_cast<OtherResource*>(resource.releaseOwnership()));
	}

	template<class Resource>
	inline SharedResource<Resource> sharedFromResource(Resource* resourcePointer)
	{
		if (resourcePointer)
		{
			resourcePointer->manualAddReference();
		}
		return SharedResource<Resource>(resourcePointer);
	}

	template<class Resource>
	inline SharedResource<Resource> sharedFromResource(Resource& resourceReference)
	{
		resourceReference.manualAddReference();
		return SharedResource<Resource>(&resourceReference);
	}
}
