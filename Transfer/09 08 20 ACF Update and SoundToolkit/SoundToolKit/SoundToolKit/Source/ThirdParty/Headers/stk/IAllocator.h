///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 10.07.2018
///
#ifndef STK__I_ALLOCATOR__H
#define STK__I_ALLOCATOR__H

#include <cstddef>

namespace stk
{
	/// <summary>
	/// Interface for memory allocation routines. All implementations of this interface have to be thread safe.
	/// </summary>
	class IAllocator
	{
	public:
		virtual ~IAllocator() = default;

		/// <summary>
		/// Allocates a block of memory with at least a given size and with a given alignment.
		/// If the size is not the multiplicity of the alignment, the result is undefined.
		/// If the size is 0, the function returns a valid non-dereferencable pointer, which must be freed later.
		/// Implementations have to be thread-safe and must not throw.
		/// </summary>
		/// <param name="size">The size of the block to be allocated. Allocated block has to be at least this size.</param>
		/// <param name="alignment">The required alignment of the allocated block. Alignment is always a power of 2. Size has to be a multiplicity of the alignment.</param>
		/// <param name="file">Diagnostic information, file name where allocation occurs. STK calls this with __FILE__.</param>
		/// <param name="line">Diagnostic information, line number where allocation occurs. STK calls this with __LINE__.</param>
		/// <returns>The allocated block, or nullptr in case of a failure.</returns>
		virtual void* alloc(size_t size, size_t alignment, const char* file, int line) noexcept = 0;

		/// <summary>
		/// Frees the given allocated block.
		/// Implementations have to be thread-safe and must not throw.
		/// </summary>
		/// <param name="block">The block to be freed. Must be previously allocated by alloc(), and must not be nullptr.</param>
		virtual void free(void* block) noexcept = 0;
	};
}

#endif
