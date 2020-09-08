///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.09.2018
///

namespace stk
{
	inline StringView::size_type StringView::find(char ch, size_type pos) const
	{
		const char* found = std::strchr(m_data + pos, ch);
		return found ? (found - m_data) : npos;
	}

	inline StringView::size_type StringView::find(const char* str, size_type pos) const
	{
		const char* found = std::strstr(m_data + pos, str);
		return found ? (found - m_data) : npos;
	}

	inline StringView::size_type StringView::find(const StringView& str, size_type pos) const
	{
		const char* found = std::strstr(m_data + pos, str.data());
		return found ? (found - m_data) : npos;
	}

	inline StringView::size_type StringView::rfind(char ch, size_type pos) const
	{
		const char* found = std::strrchr(m_data + pos, ch);
		return found ? (found - m_data) : npos;
	}

	inline StringView StringView::substr(size_type pos) const
	{
		return StringView{m_data + pos};
	}
}
