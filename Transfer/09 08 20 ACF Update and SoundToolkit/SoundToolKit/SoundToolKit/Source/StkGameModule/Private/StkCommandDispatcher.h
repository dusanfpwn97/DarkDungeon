//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

namespace SoundToolKit
{
	/// <summary>
	/// Queue that should be used to dispatch commands that can be issued not from GameThread.
	/// </summary>
	class StkCommandDispatcher
	{
	public:
		using FCommand = TFunction<void()>;

		/// <summary>
		/// Executes command if invoked from GameThread.
		/// If command is issued from different thread is it enqued to be run when ExecuteAllRemaining function is called.
		/// </summary>
		void Enqueue(FCommand Command);

		/// <summary>
		/// Forces command execution on GameThread.
		/// </summary>
		void Execute(FCommand Command) const;

		/// <summary>
		/// Executes all commands that where enqued during Enqueue function call.
		/// All commands' invokations are forced to happen on GameThread.
		/// </summary>
		void ExecuteAllRemaining();

	private:
		TQueue<FCommand, EQueueMode::Mpsc> DispatchedCommands;
	};
}
