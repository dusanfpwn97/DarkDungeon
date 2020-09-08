///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 15.02.2019
///
#ifndef STK__I_MESH__H
#define STK__I_MESH__H

#include <functional>
#include "Math.h"
#include "ArrayView.h"
#include "SharedResource.h"
#include "IResource.h"

namespace stk
{
	class IMaterial;

	/// <summary>
	/// Controls a mesh. All the updates are recorded and executed after an engine flush.
	/// STK mesh is a collection of triangles, which have a common acoustic material.
	/// </summary>
	class IMesh: public virtual IResource
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called with enabled/disabled status after isEnabled() call.
		/// </summary>
		using IsEnabledCallback = std::function<void(bool isEnabled)>;

		/// <summary>
		/// A callback called with the mesh faces after getFaces() call.
		/// </summary>
		using GetFacesCallback = std::function<void(stk::ArrayView<face>)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously enables mesh to be taken into account during sound propagation - i.e. it blocks, reflects,
		/// or transmits sound. All meshes are enabled by default.
		/// </summary>
		virtual void enable() = 0;

		/// <summary>
		/// Asynchronously disables mesh to be ignored during sound propagation.
		/// </summary>
		virtual void disable() = 0;

		/// <summary>
		/// Checks if the mesh acts as an obstacle in sound propagation.
		/// </summary>
		/// <param name="callback">A callback called with true if the mesh is enabled, with false otherwise.</param>
		virtual void isEnabled(IsEnabledCallback callback) = 0;

		/// <summary>
		/// Sets the mesh geometrical representation - its faces.
		/// Changing geometrical representation of a mesh will result in a rebuild of internal structures.
		/// This is a computationally expensive task - it is recommended to set faces only on engine startup or when the STK is paused.
		/// </summary>
		/// <param name="faces">The list of mesh faces to set.</param>
		virtual void setFaces(const ArrayView<face>& faces) = 0;

		/// <summary>
		/// Gets geometrical representation of a mesh - a list of triangles from which the mesh is built.
		/// The call is asynchronous, and the STK calls the callback when the faces are ready.
		/// </summary>
		/// <param name="callback">A callback which is called with the mesh faces.</param>
		virtual void getFaces(GetFacesCallback callback) = 0;

		/// <summary>
		/// Sets the material from which the mesh is built.
		/// </summary>
		/// <param name="material">The material to set.</param>
		virtual void setMaterial(SharedResource<IMaterial> material) = 0;

		/// <summary>
		/// Gets the material from which the mesh is built.
		/// </summary>
		/// <returns>The material.</returns>
		// TODO issue #732: the call should be asynchronous, the SharedResource should be a callback argument
		virtual SharedResource<IMaterial> material() const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IMesh() = default;
	};
}

#endif
