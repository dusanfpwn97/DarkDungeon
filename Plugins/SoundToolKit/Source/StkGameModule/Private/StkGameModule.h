//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Tickable.h"

#include "IStkGameModule.h"
#include "StkOcclusion.h"
#include "StkSpatialization.h"
#include "StkReverb.h"
#include "StkSoundSourceManager.h"
#include "StkAudioOutput.h"
#include "StkListenerManager.h"
#include "StkControl.h"
#include "StkCommandDispatcher.h"
#include "StkScene.h"

THIRD_PARTY_INCLUDES_START
#pragma warning(disable:4310)
#include <stk/ISoundToolKit.h>
#include <stk/IMaterial.h>
#include <stk/IModel.h>
#include <stk/IScene.h>
#pragma warning(default:4310)
THIRD_PARTY_INCLUDES_END

class AStkScene;
class UStkAcousticModel;

namespace SoundToolKit
{
	/// <summary>
	/// Core STK plugin module.
	/// </summary>
	class STKGAMEMODULE_API FStkGameModule : public IStkGameModule, public FTickableGameObject
	{
	public:
		using SceneInitializationCallback = TFunction<void(AStkScene*)>;

	public:
		/// <summary>
		/// Default constructor of the module.
		/// </summary>
		FStkGameModule();

	public:
		// FTickableGameObject interface
		virtual void Tick(float DeltaTime) override;
		virtual TStatId GetStatId() const override;
		virtual bool IsTickableInEditor() const override;
		// End of FTickableGameObject interface

	public:
		
		/// <summary>
		/// Used to retrieve reference to the Audio interface of SoundToolKit engine.
		/// </summary>
		/// <returns>stk::Audio interface</returns>
		stk::SharedResource<stk::ISoundToolKit> GetAudio();
		
		/// <summary>
		/// Called when the module is being started.
		/// </summary>
		virtual void StartupModule() override;

		/// <summary>
		/// Called when the module is being shutdown.
		/// </summary>
		virtual void ShutdownModule() override;

		/// <summary>
		/// Used to get access to parameters of audio output.
		/// </summary>
		FStkAudioOutput& GetAudioOutput();

		/// <summary>
		/// Creates a mesh instance used within SoundToolKit engine.
		/// </summary>
		/// <returns>Created mesh</returns>
		TUniquePtr<class FStkMesh> CreateMesh();

		/// <summary>
		/// Creates an FStkMaterial instance used within SoundToolKit engine.
		/// </summary>
		/// <returns>Created material</returns>
		TUniquePtr<class FStkMaterial> CreateMaterial();

		/// <summary>
		/// Creates a FStkModel instance used within SoundToolKit engine.
		/// </summary>
		/// <returns>Created model</returns>
		stk::SharedResource<stk::IModel> CreateModel(TArray<SoundToolKit::FStkMesh*> Meshes);

		/// <summary>
		/// Asynchronously adds a StkModel to the scene.
		/// </summary>
		/// <note>Only Models added to scene participate in sound processing.</note>
		/// <param name="Model">The model to add.</param>
		void AddModel(stk::SharedResource<stk::IModel> Model);

		/// <summary>
		/// Asynchronously removes a StkModel from the scene.
		/// </summary>
		/// <note>Only Models added to scene participate in sound processing.</note>
		/// <param name="Model">The StkModel to remove</param>
		void RemoveModel(stk::SharedResource<stk::IModel> Model);

		/// <summary>
		/// Asynchronously calls the provided callback with a view on all scene models.
		/// </summary>
		/// <param name="Callback">The callback to be called with a view on scene models.</param>
		void GetModels(stk::IScene::GetModelsCallback Callback);

		/// <summary>
		/// Asynchronously clears the scene state:
		/// - resets the receiver to default values
		/// - resets the acoustic medium to default values
		/// - removes all models from the scene.
		/// </summary>
		void Clear();

		// IStkGameModule interface
		/// <summary>
		/// Updates sound paths, which connect sound sources with receiver through variety of acoustic phenomena,
		/// like reflection, transmission, or diffraction.
		/// </summary>
		virtual void ComputeSoundFrame() override;

		/// <summary>
		/// Propagates all the commands issued to the engine.
		/// </summary>
		virtual void Flush() override;

		/// <summary>
		/// Propagates all the commands issued to the engine and waits until all of them are executed.
		/// </summary>
		virtual void Finish() override;

		/// <returns>The number of sound sources that are currently processed by SoundToolKit engine.</returns>
		virtual int32 GetSoundSourcesNum() override;

		/// <returns>Interface used to query for the diagnositcs data.</returns>
		virtual stk::UniqueResource<stk_ex::diagnostics::ISoundPathsCache> CreateSoundPathsCache() override;
		// End of IStkGameModule interface

		/// <summary>
		/// Used to retrieve command queue.
		/// </summary>
		/// <returns>The command dispatcher</returns>
		StkCommandDispatcher& GetCommandDispatcher();

		/// <summary>
		/// Used to get access to StkStatus.
		/// </summary>
		FStkControl& GetControl();

		/// <returns>
		/// Manager used for adding new sound sources or removing them.
		/// </returns>
		FStkSoundSourceManager& GetSoundSourceManager();

		/// <returns>
		/// Display name of specified audio plugin type.
		/// </returns>
		FString GetAudioPluginDisplayName(EAudioPlugin PluginType);

	public:
		void ConnectOnSceneInitialized(SceneInitializationCallback SceneInitializationCallaback);
		void NotifyOnSceneInitialized(AStkScene* Scene);

	private:
		/// <summary>
		/// Main STK engine object.
		/// </summary>
		stk::SharedResource<stk::ISoundToolKit> StkAudio;

		/// <summary>
		/// Audio output controller.
		/// </summary>
		FStkAudioOutput StkAudioOutput;

		/// <summary>
		/// Manager of STK sound sources.
		/// </summary>
		FStkSoundSourceManager StkSoundSourceManager;

		/// <summary>
		/// Manager of STK listeners.
		/// </summary>
		FStkListenerManager StkListenerManager;

		/// <summary>
		/// A Queue used to synchronize all commands issued not from game thread.
		/// </summary>
		StkCommandDispatcher CommandDispatcher;

		/// <summary>
		/// Occlusion, Reverb and Spatialization factories.
		/// </summary>
		FStkOcclusionFactory StkOcclusionFactory;
		FStkSpatializationFactory StkSpatializationFactory;
		FStkReverbFactory StkReverbFactory;

		/// <summary>
		/// Provides runtime information about STK by indicators.
		/// </summary>
		FStkControl StkControl;

		SceneInitializationCallback OnSceneInitializationCallback;
	};
}
