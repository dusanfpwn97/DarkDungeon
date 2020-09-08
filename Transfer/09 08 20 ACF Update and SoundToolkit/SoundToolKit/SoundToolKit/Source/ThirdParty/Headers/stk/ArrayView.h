///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 24.07.2018
///
#ifndef STK__ARRAY_VIEW__H
#define STK__ARRAY_VIEW__H

#include <cstddef>
#include <iterator>
#include <algorithm>

namespace stk
{
	/// <summary>
	/// An immutable collection of arbitrary data stored in contiguous memory, used to pass the data to/from STK.
	/// The interface is similar to array and vector containers, but without possibility to modify ArrayView's content.
	/// That is, the methods exposed by ArrayView behave identically as their array/vector counterparts.
	/// ArrayView does not own the data. Never store the copy of any ArrayView instance for future usage.
	/// Its contents may become invalid when asynchronous callback returns or any other synchronous STK function is called.
	/// Store the data itself (not an ArrayView instance) using a container, if the data is needed in future.
	/// </summary>
	template<class T>
	class ArrayView
	{
		// public sub-types
	public:
		using value_type = T;

		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

		using const_iterator = const_pointer;
		using iterator = const_iterator;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using reverse_iterator = const_reverse_iterator;

		using size_type = size_t;
		using difference_type = ptrdiff_t;

		// public construction and destruction methods
	public:
		ArrayView(): m_begin(nullptr), m_end(nullptr) {}
		ArrayView(const T* begin, const T* end): m_begin(begin), m_end(end) {}
		ArrayView(const T* begin, size_t size): m_begin(begin), m_end(begin + size) {}

		template<class Container>
		explicit ArrayView(const Container& c):
			m_begin(c.data()),
			m_end(c.data() + c.size()) {}

		ArrayView(const ArrayView&) = default;
		ArrayView(ArrayView&&) = default;

		ArrayView& operator=(const ArrayView&) = default;
		ArrayView& operator=(ArrayView&&) = default;

		~ArrayView() = default;

		// public methods
	public:
		const T& operator[](size_type ix) const {return m_begin[ix];}

		size_type size() const {return m_end - m_begin;}
		bool empty() const {return m_begin == m_end;}

		const T* data() const {return m_begin;}
		const T& front() const {return *m_begin;}
		const T& back() const {return *(m_end - 1);}

		const_iterator cbegin() const {return m_begin;}
		const_iterator cend() const {return m_end;}

		const_iterator begin() const {return m_begin;}
		const_iterator end() const {return m_end;}

		const_reverse_iterator crbegin() const {return const_reverse_iterator(m_end);}
		const_reverse_iterator crend() const {return const_reverse_iterator(m_begin);}

		const_reverse_iterator rbegin() const {return const_reverse_iterator(m_end);}
		const_reverse_iterator rend() const {return const_reverse_iterator(m_begin);}

		// private properties
	private:
		const T* m_begin;
		const T* m_end;
	};

	template<typename T>
	inline bool operator==(const stk::ArrayView<T>& lhv, const stk::ArrayView<T>& rhv) { return std::equal(lhv.begin(), lhv.end(), rhv.begin(), rhv.end()); }
	template<typename T>
	inline bool operator!=(const stk::ArrayView<T>& lhv, const stk::ArrayView<T>& rhv) { return !(lhv == rhv); }
	template<typename T>
	inline bool operator< (const stk::ArrayView<T>& lhv, const stk::ArrayView<T>& rhv) { return std::lexicographical_compare(lhv.begin(), lhv.end(), rhv.begin(), rhv.end()); }
	template<typename T>
	inline bool operator> (const stk::ArrayView<T>& lhv, const stk::ArrayView<T>& rhv) { return rhv < lhv; }
	template<typename T>
	inline bool operator<=(const stk::ArrayView<T>& lhv, const stk::ArrayView<T>& rhv) { return !(lhv > rhv); }
	template<typename T>
	inline bool operator>=(const stk::ArrayView<T>& lhv, const stk::ArrayView<T>& rhv) { return !(lhv < rhv); }
}

#endif
