///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 11.10.2018
///
#ifndef STK__I_THREAD_POOL__H
#define STK__I_THREAD_POOL__H

#include <cstddef>

namespace stk
{
	/// <summary>
	/// Interface for thread pools. A thread pool can contain any number of threads,
	/// which are used to asynchronous execution of tasks.
	/// </summary>
	class IThreadPool
	{
	public:
		virtual ~IThreadPool() = default;

		/// <summary>
		/// The abstract interface for objects which represent tasks to be executed.
		/// Any task-representing object must inherit from IRunnable and implement the execute()
		/// method, which would be called by the IThreadPool implementation.
		/// </summary>
		class IRunnable
		{
		public:
			virtual ~IRunnable() = default;
			virtual void execute() noexcept = 0;
		};

		/// <summary>
		/// Call this method to schedule a task execution.
		/// If the thread pool contains no threads, the runnable->execute() is called immediately,
		/// on the same thread.
		/// Otherwise, thread pool implementation is encouraged (but does not have to) schedule the task
		/// to be executed, and return as soon as possible. Any thread pool however must guarantee
		/// that the task eventually would be executed, after a finite wait time in the queue.
		/// The schedule() caller has to be careful with deleting runnable, since runnable->execute()
		/// could still be running on a thread pool managed thread. The safe way to free runnable is
		/// to use either 'wait/signal' with signal as the last operation of runnable->execute(),
		/// or 'delete this' at the end of runnable->execute().
		/// The runnable->execute() must catch all exceptions, since any uncaught exception on separate
		/// thread terminates the program in the same way as on main thread. Note that it is *not* enough
		/// to surround schedule() call with try/catch block.
		/// </summary>
		/// <returns>
		/// Either the number of tasks which are currently in queue, including this one (the return value is
		/// larger than 0), or 0 if the task was already executed on the same thread on which schedule was called.
		/// </returns>
		virtual size_t schedule(IRunnable& task) = 0;
	};
}

#endif
