//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkGameModule.h"
#include "StkCommon.h"
#include "StkMesh.h"
#include "StkMaterial.h"
#include "StkAcousticModel.h"
#include "StkProjectData.h"

THIRD_PARTY_INCLUDES_START
#include <stk/SoundToolKitBuilder.h>
#include <stk/ArrayView.h>
#include <stk/IAudioOutput.h>
#include <stk/IResourcesFactory.h>
#include <stk/IMesh.h>
#include <stk/IControl.h>
#include <stk/IScene.h>
THIRD_PARTY_INCLUDES_END

#include "Features/IModularFeatures.h"
#include "Landscape.h"

IMPLEMENT_MODULE(SoundToolKit::FStkGameModule, StkGameModule)

namespace
{
	void LogHandler(stk::SeverityLevel level, stk::StringView message)
	{
		const FString MessageFString(ANSI_TO_TCHAR(message.c_str()));
		switch (level)
		{
		case stk::SeverityLevel::Info:
			STK_LOG(Display, TEXT("%s"), *MessageFString);
			break;
		case stk::SeverityLevel::Warning:
			STK_LOG(Warning, TEXT("%s"), *MessageFString);
			break;
		case stk::SeverityLevel::Error:
			STK_LOG(Error, TEXT("%s"), *MessageFString);
			break;
		}
	}
}

namespace SoundToolKit
{
	FStkGameModule::FStkGameModule()
		: StkAudio(stk::createSoundToolKit(stk::requestDefaultAllocator(), stk::requestDefaultThreadPool(), LogHandler))
		, StkAudioOutput(StkAudio->audioOutput())
		, StkSoundSourceManager(CommandDispatcher, StkAudio)
		, StkListenerManager(CommandDispatcher, StkAudio)
		, StkOcclusionFactory(StkAudioOutput, StkSoundSourceManager, StkListenerManager)
		, StkSpatializationFactory(StkAudioOutput, StkSoundSourceManager, StkListenerManager)
		, StkReverbFactory(StkAudioOutput, StkSoundSourceManager, StkListenerManager)
		, StkControl(StkAudio->control())
	{
		TArray<std::byte> diffractionData = Utils::LoadDiffractionData(StkAudio);
		TArray<std::byte> hrtfData = Utils::LoadHrtfData(StkAudio);
		StkAudio->setDiffractionData(stk::ArrayView<std::byte>{diffractionData.GetData(), (size_t)diffractionData.Num()});
		StkAudio->audioOutput().setHrtfData(stk::ArrayView<std::byte>{hrtfData.GetData(), (size_t)hrtfData.Num()});
	}

	void FStkGameModule::Tick(float DeltaTime)
	{
		ComputeSoundFrame();
		Flush();
	}

	TStatId FStkGameModule::GetStatId() const
	{
		return TStatId{};
	}

	bool FStkGameModule::IsTickableInEditor() const
	{
		return true;
	}

	void FStkGameModule::StartupModule()
	{
		IModularFeatures::Get().RegisterModularFeature(FStkOcclusionFactory::GetModularFeatureName(), &StkOcclusionFactory);
		IModularFeatures::Get().RegisterModularFeature(FStkSpatializationFactory::GetModularFeatureName(), &StkSpatializationFactory);
		IModularFeatures::Get().RegisterModularFeature(FStkReverbFactory::GetModularFeatureName(), &StkReverbFactory);

		UStkProjectData::Init();
	}

	void FStkGameModule::ShutdownModule()
	{
		IModularFeatures::Get().UnregisterModularFeature(FStkOcclusionFactory::GetModularFeatureName(), &StkOcclusionFactory);
		IModularFeatures::Get().UnregisterModularFeature(FStkSpatializationFactory::GetModularFeatureName(), &StkSpatializationFactory);
		IModularFeatures::Get().UnregisterModularFeature(FStkReverbFactory::GetModularFeatureName(), &StkReverbFactory);
	}

	FStkAudioOutput& FStkGameModule::GetAudioOutput()
	{
		return StkAudioOutput;
	}

	TUniquePtr<FStkMesh> FStkGameModule::CreateMesh()
	{
		return MakeUnique<FStkMesh>(StkAudio->resourcesFactory().createMesh());
	}

	TUniquePtr<FStkMaterial> FStkGameModule::CreateMaterial()
	{
		return MakeUnique<FStkMaterial>(StkAudio->resourcesFactory().createMaterial());
	}

	stk::SharedResource<stk::IModel> FStkGameModule::CreateModel(TArray<SoundToolKit::FStkMesh*> Meshes)
	{
		std::vector<stk::SharedResource<stk::IMesh>> NativeMeshesVector;

		for (int i = 0; i < Meshes.Num(); i++)
		{
			NativeMeshesVector.push_back(Meshes[i]->Native());
		}

		return StkAudio->resourcesFactory().createModel(stk::ArrayView<stk::SharedResource<stk::IMesh>>{NativeMeshesVector});
	}

	void FStkGameModule::AddModel(stk::SharedResource<stk::IModel> Model)
	{
		StkAudio->scene().addModel(Model);
	}

	void FStkGameModule::RemoveModel(stk::SharedResource<stk::IModel> Model)
	{
		StkAudio->scene().removeModel(Model.get());
	}

	void FStkGameModule::GetModels(stk::IScene::GetModelsCallback Callback)
	{
		StkAudio->scene().getModels(Callback);
	}

	void FStkGameModule::Clear()
	{
		StkAudio->scene().clear();
	}

	void FStkGameModule::ComputeSoundFrame()
	{
		StkAudio->computeSoundFrame();
	}

	void FStkGameModule::Flush()
	{
		STK_CHECK(IsInGameThread(), Error, TEXT("Flushing the commands must happen in the GameThread."));

		CommandDispatcher.ExecuteAllRemaining();

		StkAudio->flush();
	}

	void FStkGameModule::Finish()
	{
		STK_CHECK(IsInGameThread(), Error, TEXT("Flushing the commands must happen in the GameThread."));

		CommandDispatcher.ExecuteAllRemaining();

		StkAudio->finish();
	}

	int32 FStkGameModule::GetSoundSourcesNum()
	{
		return StkSoundSourceManager.Num();
	}

	stk::UniqueResource<stk_ex::diagnostics::ISoundPathsCache> FStkGameModule::CreateSoundPathsCache()
	{
		return stk_ex::diagnostics::ISoundPathsCache::create(StkAudio);
	}

	stk::SharedResource<stk::ISoundToolKit> FStkGameModule::GetAudio()
	{
		return StkAudio;
	}

	StkCommandDispatcher& FStkGameModule::GetCommandDispatcher()
	{
		return CommandDispatcher;
	}

	FStkControl& FStkGameModule::GetControl()
	{
		return StkControl;
	}

	FStkSoundSourceManager& FStkGameModule::GetSoundSourceManager()
	{
		return StkSoundSourceManager;
	}

	FString FStkGameModule::GetAudioPluginDisplayName(EAudioPlugin PluginType)
	{
		switch (PluginType)
		{
		case EAudioPlugin::SPATIALIZATION:
			return StkSpatializationFactory.GetDisplayName();
		case EAudioPlugin::REVERB:
			return StkReverbFactory.GetDisplayName();
		case EAudioPlugin::OCCLUSION:
			return StkOcclusionFactory.GetDisplayName();
		default:
			return TEXT("");
		}
	}

	void FStkGameModule::ConnectOnSceneInitialized(SceneInitializationCallback SceneInitializationCallaback)
	{
		OnSceneInitializationCallback = SceneInitializationCallaback;
	}

	void FStkGameModule::NotifyOnSceneInitialized(AStkScene* Scene)
	{
		if (OnSceneInitializationCallback)
		{
			OnSceneInitializationCallback(Scene);
		}
	}
}
