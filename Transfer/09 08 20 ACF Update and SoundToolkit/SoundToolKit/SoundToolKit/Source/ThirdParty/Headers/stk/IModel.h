///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 18.03.2019
///
#ifndef STK__I_MODEL__H
#define STK__I_MODEL__H

#include <cstddef>
#include <functional>
#include "SharedResource.h"
#include "ArrayView.h"
#include "IResource.h"
#include "ITransformable.h"
#include "IMesh.h"

namespace stk
{
	/// <summary>
	/// Controls models for grouping meshes.
	/// A Model allows manipulating its meshes together, and independently of any other meshes.
	/// </summary>
	class IModel: public virtual IResource, public virtual ITransformable
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called with a view on obtained model's meshes.
		/// </summary>
		/// <param name="meshes">The obtained view on all model's meshes.</param>
		using GetMeshesCallback = std::function<void(ArrayView<SharedResource<IMesh>> meshes)>;

		/// <summary>
		/// A callback called with model's binary serialized geometry data.
		/// </summary>
		/// <param name="data">The view on a serialized binary representation of geometry.</param>
		using GeometrySavedCallback = std::function<void(ArrayView<std::byte> data)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously replaces the content of the model with the given meshes.
		/// </summary>
		/// <param name="meshes">The meshes to set.</param>
		virtual void setMeshes(ArrayView<SharedResource<IMesh>> meshes) = 0;

		/// <summary>
		/// Asynchronously calls the provided callback with a view on all model's meshes.
		/// </summary>
		/// <param name="callback">The callback to be called with a view on model's meshes.</param>
		virtual void getMeshes(GetMeshesCallback callback) = 0;

		/// <summary>
		/// Asyncrhronously saves all model's geometry data to a binary stream, and calls
		/// the specified callback with a view to the stream. The binary data can be later used
		/// as the argument of restoreGeometry() call.
		/// </summary>
		/// <note>
		/// The restoreGeometry() is much faster than calling setFaces() on each mesh individually.
		/// </note>
		/// <param name="callback">The callback to be called with a view on binary geometry data.</param>
		virtual void saveGeometry(GeometrySavedCallback callback) = 0;

		/// <summary>
		/// Asynchronously restores the model's geometry from the binary data
		/// created by a saveGeometry() call.
		/// </summary>
		/// <note>
		/// To ensure correctness of geometry restoration, the model should have been created using
		/// the same meshes in the same order as the one used to saveGeometry() call. The setFaces()
		/// needs not be called on any of these meshes. However, it is not an error to do so, since
		/// restoreGeometry() overwrite faces provided by getFaces() and vice versa.
		/// </note>
		/// <note>
		/// The restoreGeometry() is much faster than calling setFaces() on each mesh individually.
		/// </note>
		/// <param name="data">The binary data created by saveGeometry() call.</param>
		virtual void restoreGeometry(ArrayView<std::byte> data) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IModel() = default;
	};
}

#endif
