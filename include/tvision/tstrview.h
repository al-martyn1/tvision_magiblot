/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TSTRVIEW.H                                                            */
/*                                                                         */
/*   Defines the class TStringView and its member functions.               */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TVISION_TSTRVIEW_H
#define TVISION_TSTRVIEW_H

#include <string.h>
#include <tvision/compat/borland/iosfwd.h>

#include <cstddef>

#ifdef TVISION_STL
#include <string>
#include <iterator>

#if __cplusplus >= 201703L || __cpp_lib_string_view
#include <string_view>
#endif

#endif // TVISION_STL

class TStringView
{

    // This class exists only to compensate for the lack of std::string_view
    // in Borland C++. Unless you are programming for that compiler, you should
    // always use std::string_view.
    // Unlike std::string_view, TStringView can be constructed from a null pointer,
    // for backward compatibility.
    // TStringView is intercompatible with std::string_view, std::string and
    // TSpan<const char>.

    const char _FAR *str;
    size_t len;

public:

    constexpr static const size_t npos = (size_t)-1;

#ifdef TVISION_STL
    using traits_type            = std::char_traits<char>;
#endif
    using value_type             = char;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using pointer                = char*;
    using const_pointer          = const char*;
    using reference              = char&;
    using const_reference        = const char&;
    using iterator               = char*;
    using const_iterator         = const char*;
#ifdef TVISION_STL
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
#endif


    constexpr TStringView();
#if defined(TVISION_STL) && (__cplusplus >= 201703L || __cpp_lib_constexpr_char_traits)
    constexpr
#endif
              TStringView(const char _FAR *str);
    constexpr TStringView(const char _FAR *str, size_t len);
    constexpr TStringView(TSpan<char> span);
    constexpr TStringView(TSpan<const char> span);
#ifdef TVISION_STL
#if __cplusplus >= 201703L || __cpp_lib_string_view
    constexpr TStringView(std::string_view text);
    constexpr operator std::string_view() const;
#endif
    TStringView(const std::string &text);
    operator std::string() const;
#endif // TVISION_STL
    constexpr operator TSpan<const char>() const;

    constexpr const char _FAR * data() const;
    constexpr size_t size() const;
    constexpr Boolean empty() const;
    constexpr const char _FAR & operator[](size_t pos) const;
    constexpr const char _FAR & front() const;
    constexpr const char _FAR & back() const;

    constexpr TStringView substr(size_t pos) const;
    constexpr TStringView substr(size_t pos, size_t n) const;

    constexpr const char _FAR * begin() const;
    constexpr const char _FAR * cbegin() const;
    constexpr const char _FAR * end() const;
    constexpr const char _FAR * cend() const;

// #ifdef TVISION_STL
    constexpr size_t find( TStringView v, size_t pos = 0 ) const noexcept;
    constexpr size_t find( char ch, size_t pos = 0 ) const noexcept;
    constexpr size_t find( const char* s, size_t pos, size_t count ) const;
#if defined(TVISION_STL) && (__cplusplus >= 201703L || __cpp_lib_constexpr_char_traits)
    constexpr
#endif
    size_t find( const char* s, size_type pos = 0 ) const;
// #endif

};

inline constexpr TStringView::TStringView() :
    str(0),
    len(0)
{
}

#if defined(TVISION_STL) && (__cplusplus >= 201703L || __cpp_lib_constexpr_char_traits)
constexpr
inline TStringView::TStringView(const char _FAR *str) :
    str(str),
    len(str ? std::char_traits<char>::length(str) : 0)
{
}
#else
inline TStringView::TStringView(const char _FAR *str) :
    str(str),
    len(str ? strlen(str) : 0)
{
}
#endif

inline constexpr TStringView::TStringView(const char _FAR *str, size_t len) :
    str(str),
    len(len)
{
}

inline constexpr TStringView::TStringView(TSpan<char> span) :
    str(span.data()),
    len(span.size())
{
}

inline constexpr TStringView::TStringView(TSpan<const char> span) :
    str(span.data()),
    len(span.size())
{
}

#ifdef TVISION_STL
#if __cplusplus >= 201703L || __cpp_lib_string_view
inline constexpr TStringView::TStringView(std::string_view text) :
    str(text.data()),
    len(text.size())
{
}

inline constexpr TStringView::operator std::string_view() const
{
    return {str, len};
}
#endif

inline TStringView::TStringView(const std::string &text) :
    str(text.data()),
    len(text.size())
{
}

inline TStringView::operator std::string() const
{
    return {str, len};
}
#endif // TVISION_STL

inline constexpr TStringView::operator TSpan<const char>() const
{
    return TSpan<const char>(str, len);
}

inline constexpr const char _FAR * TStringView::data() const
{
    return str;
}

inline constexpr size_t TStringView::size() const
{
    return len;
}

inline constexpr Boolean TStringView::empty() const
{
    return Boolean( size() == 0 );
}

inline constexpr const char _FAR & TStringView::operator[](size_t pos) const
{
    return str[pos];
}

inline constexpr const char _FAR & TStringView::front() const
{
    return str[0];
}

inline constexpr const char _FAR & TStringView::back() const
{
    return str[len - 1];
}

inline constexpr TStringView TStringView::substr(size_t pos) const
{
    return TStringView(str + pos, len - pos);
}

inline constexpr TStringView TStringView::substr(size_t pos, size_t n) const
{
    return TStringView(str + pos, n <= len - pos ? n : len - pos);
}

inline constexpr const char _FAR * TStringView::begin() const
{
    return &str[0];
}

inline constexpr const char _FAR * TStringView::cbegin() const
{
    return &str[0];
}

inline constexpr const char _FAR * TStringView::end() const
{
    return &str[len];
}

inline constexpr const char _FAR * TStringView::cend() const
{
    return &str[len];
}

#if defined(TVISION_STL) && (__cplusplus >= 201703L || __cpp_lib_constexpr_char_traits)
inline constexpr Boolean operator==(TStringView a, TStringView b)
{
    if (a.size() == b.size())
        return Boolean( std::char_traits<char>::compare(a.data(), b.data(), b.size()) == 0 );
    return False;
}
#else
inline Boolean operator==(TStringView a, TStringView b)
{
    if (a.size() == b.size())
        return Boolean( b.size() == 0 || memcmp(a.data(), b.data(), b.size()) == 0 );
    return False;
}
#endif

#if defined(TVISION_STL) && (__cplusplus >= 201703L || __cpp_lib_constexpr_char_traits)
constexpr
#endif
inline Boolean operator!=(TStringView a, TStringView b)
{
    return Boolean( !(a == b) );
}

#if defined(TVISION_STL) && __cplusplus >= 201103L

#include <typeindex>

namespace std {
#if __cplusplus >= 201703L || __cpp_lib_string_view
    template<>
    struct hash<TStringView> : public std::hash<std::string_view>
    {
    };
#else
    template<>
    struct hash<TStringView> : public std::hash<std::string>
    {
    };
#endif
} // namespace std

#endif // TVISION_STL && __cplusplus >= 201103L



//#ifdef TVISION_STL

// https://en.cppreference.com/w/cpp/algorithm/search

template<class ForwardIt1, class ForwardIt2>
constexpr
ForwardIt1 search_impl( ForwardIt1 first, ForwardIt1 last
                      , ForwardIt2 s_first, ForwardIt2 s_last
                      )
{
    while (true)
    {
        ForwardIt1 it = first;
        for (ForwardIt2 s_it = s_first; ; ++it, ++s_it)
        {
            if (s_it == s_last)
                return first;
            if (it == last)
                return last;
            if (!(*it == *s_it))
                break;
        }
        ++first;
    }
}


inline constexpr size_t TStringView::find( const TStringView v, size_t pos ) const noexcept
{
    if (pos>=size())
        return npos;

    auto itRes = search_impl(cbegin()+pos, cend(), v.cbegin(), v.cend());
    if (itRes==cend())
        return npos;

    return (size_t)(itRes-cbegin());
}

inline constexpr size_t TStringView::find( const char* s, size_t pos, size_t count ) const
{
    return find( TStringView(s, count), pos);
}

inline constexpr size_t TStringView::find( char ch, size_t pos ) const noexcept
{
    return find( &ch, pos, 1 );
}

inline 
#if defined(TVISION_STL) && (__cplusplus >= 201703L || __cpp_lib_constexpr_char_traits)
    constexpr
#endif
size_t TStringView::find( const char* s, size_t pos ) const
{
    return find( TStringView(s), pos);
}

//#endif



#endif // TVISION_TSTRVIEW_H
