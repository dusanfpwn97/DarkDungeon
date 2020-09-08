//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkBlueprintFunctionLibrary.h"
#include "StkScene.h"
#include "StkLog.h"
#include "Engine/World.h"
#include "UObject/UObjectIterator.h"

namespace
{
	AStkScene* GetSceneFromPersistentLevel()
	{
		for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
		{
			if (UWorld* World = Scene->GetWorld())
			{
				if (World->WorldType == EWorldType::PIE || World->WorldType == EWorldType::Game)
				{
					if (ULevel* Level = Scene->GetLevel())
					{
						if (Level->IsPersistentLevel())
						{
							return *Scene;
						}
					}
				}
			}
		}
		STK_LOG(Error, TEXT("No actor of type '%s' on the scene. Blueprint function did not work correctly."), *AStkScene::StaticClass()->GetFName().ToString());
		return nullptr;
	}
}

void UStkBlueprintFunctionLibrary::StkSetMasterVolume(float Volume)
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Volume = FMath::Clamp(Volume, 0.0f, 4.0f);

		Scene->MasterVolume = Volume;
		Scene->OnUpdateVolumes();
	}
}

float UStkBlueprintFunctionLibrary::StkGetMasterVolume()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->MasterVolume;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkSetSpatialVolume(float Volume)
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Volume = FMath::Clamp(Volume, 0.0f, 4.0f);

		Scene->SpatialVolume = Volume;
		Scene->OnUpdateVolumes();
	}
}

float UStkBlueprintFunctionLibrary::StkGetSpatialVolume()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->SpatialVolume;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkSetReverbVolume(float Volume)
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Volume = FMath::Clamp(Volume, 0.0f, 4.0f);

		Scene->ReverbVolume = Volume;
		Scene->OnUpdateVolumes();
	}
}

float UStkBlueprintFunctionLibrary::StkGetReverbVolume()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->ReverbVolume;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkEnableHrtf()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableHRTF = true;
		Scene->OnUpdateHRTF();
	}
}

void UStkBlueprintFunctionLibrary::StkDisableHrtf()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableHRTF = false;
		Scene->OnUpdateHRTF();
	}
}

bool UStkBlueprintFunctionLibrary::StkIsHrtfEnabled()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->bEnableHRTF;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkEnableAttenuation()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableAttenuation = true;
		Scene->OnUpdateAttenuation();
	}
}

void UStkBlueprintFunctionLibrary::StkDisableAttenuation()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableAttenuation = false;
		Scene->OnUpdateAttenuation();
	}
}

bool UStkBlueprintFunctionLibrary::StkIsAttenuationEnabled()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->bEnableAttenuation;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkEnableReflection()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableReflection = true;
		Scene->OnUpdateReflection();
	}
}

void UStkBlueprintFunctionLibrary::StkDisableReflection()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableReflection = false;
		Scene->OnUpdateReflection();
	}
}

bool UStkBlueprintFunctionLibrary::StkIsReflectionEnabled()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->bEnableReflection;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkEnableTransmission()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableTransmission = true;
		Scene->OnUpdateTransmission();
	}
}

void UStkBlueprintFunctionLibrary::StkDisableTransmission()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableTransmission = false;
		Scene->OnUpdateTransmission();
	}
}

bool UStkBlueprintFunctionLibrary::StkIsTransmissionEnabled()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->bEnableTransmission;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkEnableDiffraction()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableDiffraction = true;
		Scene->OnUpdateDiffraction();
	}
}

void UStkBlueprintFunctionLibrary::StkDisableDiffraction()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableDiffraction = false;
		Scene->OnUpdateDiffraction();
	}
}

bool UStkBlueprintFunctionLibrary::StkIsDiffractionEnabled()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->bEnableDiffraction;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkSetSpeedOfSound(float SpeedOfSound)
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		SpeedOfSound = FMath::Clamp(SpeedOfSound, 100.0f, 1000.0f);

		Scene->SpeedOfSound = SpeedOfSound;
		Scene->OnUpdateSpeedOfSound();
	}
}

float UStkBlueprintFunctionLibrary::StkGetSpeedOfSound()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->SpeedOfSound;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkEnableDamping()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableDamping = true;
		Scene->OnUpdateDamping();
	}
}

void UStkBlueprintFunctionLibrary::StkDisableDamping()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		Scene->bEnableDamping = false;
		Scene->OnUpdateDamping();
	}
}

bool UStkBlueprintFunctionLibrary::StkIsDampingEnabled()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->bEnableDamping;
	}
	return {};
}

void UStkBlueprintFunctionLibrary::StkSetDampingCoefficients(FStkEffectCoefficients DampingCoefficients)
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		DampingCoefficients.Band125Hz = FMath::Clamp(DampingCoefficients.Band125Hz, 0.0f, 1.0f);
		DampingCoefficients.Band250Hz = FMath::Clamp(DampingCoefficients.Band250Hz, 0.0f, 1.0f);
		DampingCoefficients.Band500Hz = FMath::Clamp(DampingCoefficients.Band500Hz, 0.0f, 1.0f);
		DampingCoefficients.Band1000Hz = FMath::Clamp(DampingCoefficients.Band1000Hz, 0.0f, 1.0f);
		DampingCoefficients.Band2000Hz = FMath::Clamp(DampingCoefficients.Band2000Hz, 0.0f, 1.0f);
		DampingCoefficients.Band4000Hz = FMath::Clamp(DampingCoefficients.Band4000Hz, 0.0f, 1.0f);
		DampingCoefficients.Band8000Hz = FMath::Clamp(DampingCoefficients.Band8000Hz, 0.0f, 1.0f);
		DampingCoefficients.Band16000Hz = FMath::Clamp(DampingCoefficients.Band16000Hz, 0.0f, 1.0f);

		Scene->Damping = DampingCoefficients;
		Scene->OnUpdateDampingCoefficients();
	}
}

FStkEffectCoefficients UStkBlueprintFunctionLibrary::StkGetDampingCoefficients()
{
	if (AStkScene* Scene = GetSceneFromPersistentLevel())
	{
		return Scene->Damping;
	}
	return {};
}
