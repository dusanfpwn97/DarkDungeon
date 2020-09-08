//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkCommandDispatcher.h"
#include "StkCommon.h"

namespace SoundToolKit
{
	void StkCommandDispatcher::Enqueue(FCommand Command)
	{
		if (IsInGameThread())
		{
			Command();
		}
		else
		{
			DispatchedCommands.Enqueue(Command);
		}
	}

	void StkCommandDispatcher::Execute(FCommand Command) const
	{
		if (IsInGameThread())
		{
			Command();
		}
		else
		{
			auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady([&Command]
			{
				Command();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
			FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
		}
	}

	void StkCommandDispatcher::ExecuteAllRemaining()
	{
		auto Execute = [&DispatchedCommands{ DispatchedCommands }]
		{
			while (!DispatchedCommands.IsEmpty())
			{
				TFunction<void()> Command;
				DispatchedCommands.Dequeue(Command);
				Command();
			}
		};

		if (IsInGameThread())
		{
			Execute();
		}
		else
		{
			auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady([&Execute]
			{
				Execute();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
			FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
		}
	}
}
