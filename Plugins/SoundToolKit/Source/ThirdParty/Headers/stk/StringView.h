///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.09.2018
///
#ifndef STK__STRING_VIEW__H
#define STK__STRING_VIEW__H

#include <cstddef>
#include <cstring>
#include <iterator>
#include <ostream>

namespace stk
{
	/// <summary>
	/// A lightweight wrapper for an immutable c-string, used to pass the character data to/from STK.
	/// Thus the StringView is not equivalent of std::string_view. The latter one stores begin and end pointers,
	/// and its content is not guaranteed to be null terminated. StringView interface is similar to string and
	/// string_view, but not identical. The exposed methods produce identical result as their std::string counterparts,
	/// but the complexity order of some of them differs.
	/// StringView does not own the data. Never store the copy of any StringView instance for future usage.
	/// Its contents may become invalid when asynchronous callback returns or any other synchronous STK function is called.
	/// Store the data itself (not an StringView instance) using a string, if the data is needed in future.
	/// </summary>
	class StringView
	{
		// public sub-types
	public:
		using value_type = char;

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

		static constexpr size_type npos = static_cast<size_type>(-1);

		// public construction and destruction methods
	public:
		constexpr StringView(): m_data(nullptr) {}
		constexpr StringView(std::nullptr_t): m_data(nullptr) {}
		constexpr StringView(const char* data): m_data(data) {}

		template<class String>
		constexpr explicit StringView(const String& s): m_data(s.c_str()) {}

		StringView(const StringView&) = default;
		StringView(StringView&&) = default;

		StringView& operator=(const StringView&) = default;
		StringView& operator=(StringView&&) = default;

		~StringView() = default;

		// public methods
	public:
		/// <summary>
		/// Converts the StringView to equivalent C-string.
		/// Useful for assignment of StringView to other strings.
		/// </summary>
		/// <returns>C-string contained inside StringView.</summary>
		operator const char*() const {return m_data;}

		/// <summary>
		/// Checks if StringView contains a C-string inside.
		/// </summary>
		/// <returns>True if C-string is not nullptr, false otherwise.</summary>
		explicit operator bool() const {return m_data != nullptr;}

		const char& operator[](size_type ix) const {return m_data[ix];}

		size_type size() const {return m_data ? std::strlen(m_data) : 0u;}
		size_type length() const {return m_data ? std::strlen(m_data) : 0u;}
		bool empty() const {return !m_data || *m_data == '\0';}

		const char* data() const {return m_data;}
		const char* c_str() const {return m_data;}

		const char& front() const {return *m_data;}
		const char& back() const {return *(m_data + std::strlen(m_data) - 1);}

		const_iterator cbegin() const {return m_data;}
		const_iterator cend() const {return m_data + length();}

		const_iterator begin() const {return m_data;}
		const_iterator end() const {return m_data + length();}

		const_reverse_iterator crbegin() const {return const_reverse_iterator(m_data + length());}
		const_reverse_iterator crend() const {return const_reverse_iterator(m_data);}

		const_reverse_iterator rbegin() const {return const_reverse_iterator(m_data + length());}
		const_reverse_iterator rend() const {return const_reverse_iterator(m_data);}

		size_type find(char ch, size_type pos = 0) const;
		size_type find(const char* str, size_type pos = 0) const;
		size_type find(const StringView& str, size_type pos = 0) const;
		size_type rfind(char ch, size_type pos = 0) const;

		StringView substr(size_type pos) const;

		// private properties
	private:
		const char* m_data;
	};

	inline bool operator==(const stk::StringView& lhv, const stk::StringView& rhv) {return std::strcmp(lhv.data(), rhv.data()) == 0;}
	inline bool operator!=(const stk::StringView& lhv, const stk::StringView& rhv) {return std::strcmp(lhv.data(), rhv.data()) != 0;}
	inline bool operator< (const stk::StringView& lhv, const stk::StringView& rhv) {return std::strcmp(lhv.data(), rhv.data()) <  0;}
	inline bool operator> (const stk::StringView& lhv, const stk::StringView& rhv) {return std::strcmp(lhv.data(), rhv.data()) >  0;}
	inline bool operator<=(const stk::StringView& lhv, const stk::StringView& rhv) {return std::strcmp(lhv.data(), rhv.data()) <= 0;}
	inline bool operator>=(const stk::StringView& lhv, const stk::StringView& rhv) {return std::strcmp(lhv.data(), rhv.data()) >= 0;}

	inline bool operator==(const stk::StringView& lhv, const char* rhv) {return std::strcmp(lhv.data(), rhv) == 0;}
	inline bool operator!=(const stk::StringView& lhv, const char* rhv) {return std::strcmp(lhv.data(), rhv) != 0;}
	inline bool operator< (const stk::StringView& lhv, const char* rhv) {return std::strcmp(lhv.data(), rhv) <  0;}
	inline bool operator> (const stk::StringView& lhv, const char* rhv) {return std::strcmp(lhv.data(), rhv) >  0;}
	inline bool operator<=(const stk::StringView& lhv, const char* rhv) {return std::strcmp(lhv.data(), rhv) <= 0;}
	inline bool operator>=(const stk::StringView& lhv, const char* rhv) {return std::strcmp(lhv.data(), rhv) >= 0;}

	inline bool operator==(const char* lhv, const stk::StringView& rhv) {return std::strcmp(lhv, rhv.data()) == 0;}
	inline bool operator!=(const char* lhv, const stk::StringView& rhv) {return std::strcmp(lhv, rhv.data()) != 0;}
	inline bool operator< (const char* lhv, const stk::StringView& rhv) {return std::strcmp(lhv, rhv.data()) <  0;}
	inline bool operator> (const char* lhv, const stk::StringView& rhv) {return std::strcmp(lhv, rhv.data()) >  0;}
	inline bool operator<=(const char* lhv, const stk::StringView& rhv) {return std::strcmp(lhv, rhv.data()) <= 0;}
	inline bool operator>=(const char* lhv, const stk::StringView& rhv) {return std::strcmp(lhv, rhv.data()) >= 0;}
}

#include "StringView.inl"

inline std::ostream& operator<<(std::ostream& stream, stk::StringView string)
{
	return stream << string.c_str();
}

#endif
