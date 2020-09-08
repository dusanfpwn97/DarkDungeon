///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 11.01.2019
///
#ifndef STK_EX__SCENE__MODELS_IMPORTER__H
#define STK_EX__SCENE__MODELS_IMPORTER__H

#include <functional>
#include <stk/StringView.h>
#include <stk/SharedResource.h>

namespace stk
{
	class ISoundToolKit;
	class IMesh;
	class IModel;
}

namespace stk_ex::scene
{
	/// <summary>
	/// The callback called for each loaded mesh with the mesh name, material name, and the mesh itself.
	/// </summary>
	/// <param name="meshName">The name of the mesh, or null view if no name is present.</param>
	/// <param name="materialName">The name of material which should be applied to the mesh, or null pointer if no such material is defined.</param>
	/// <param name="mesh">The created mesh, with no material assigned.</param>
	/// <note>The callback can be used to set the mesh material.</note>
	using MeshMaterialCallback = std::function<void(stk::StringView meshName, stk::StringView materialName, stk::SharedResource<stk::IMesh> mesh)>;

	/// <summary>
	/// Imports meshes in some well-known formats and creates a model from them.
	/// The implementation is based on Open Asset Import Library.
	/// </summary>
	/// <param name="stk">The SoundToolKit interface used to create resources.</param>
	/// <param name="filePath">A path to the file containing the definitions of model's meshes.</param>
	/// <param name="callback">A callback called for each loaded and created mesh.</param>
	/// <returns>The created model or null pointer in case of critical error.</returns>
	/// <note>
	/// Supported formats:
	/// - Collada (*.dae;*.xml)
	/// - Blender (*.blend)
	/// - Biovision BVH (*.bvh)
	/// - 3D Studio Max 3DS (*.3ds)
	/// - 3D Studio Max ASE (*.ase)
	/// - Wavefront Object (*.obj)
	/// - Stanford Polygon Library (*.ply)
	/// - AutoCAD DXF (*.dxf)
	/// - IFC-STEP, Industry Foundation Classes (*.ifc)
	/// - Neutral File Format (*.nff)
	/// - Sense8 WorldToolkit (*.nff)
	/// - Valve Model (*.smd,*.vta)
	/// - Quake I (*.mdl)
	/// - Quake II (*.md2)
	/// - Quake III (*.md3)
	/// - Quake 3 BSP (*.pk3)
	/// - RtCW (*.mdc)
	/// - Doom 3 (*.md5mesh;*.md5anim;*.md5camera)
	/// - DirectX X (*.x)
	/// - Quick3D (*.q3o;q3s)
	/// - Raw Triangles (.raw)
	/// - AC3D (*.ac)
	/// - Stereolithography (*.stl)
	/// - Autodesk DXF (*.dxf)
	/// - Irrlicht Mesh (*.irrmesh;*.xml)
	/// - Irrlicht Scene (*.irr;*.xml)
	/// - Object File Format (*.off)
	/// - Terragen Terrain (*.ter)
	/// - 3D GameStudio Model (*.mdl)
	/// - 3D GameStudio Terrain (*.hmp)
	/// - Ogre (*.mesh.xml, *.skeleton.xml, *.material)
	/// - Milkshape 3D (*.ms3d)
	/// - LightWave Model (*.lwo)
	/// - LightWave Scene (*.lws)
	/// - Modo Model (*.lxo)
	/// - CharacterStudio Motion (*.csm)
	/// - Stanford Ply (*.ply)
	/// - TrueSpace (*.cob, *.scn)
	/// - XGL (*.xgl, *.zgl)
	/// </note>
	stk::SharedResource<stk::IModel> importModel(stk::ISoundToolKit& stk,
		stk::StringView filePath, MeshMaterialCallback callback);
}

#endif
