#pragma once

#include <cctype>
#include <type_traits>
#include <iterator>
#include <algorithm>

#ifdef __cpp_concepts
template <typename T> concept bool Iterator= requires(T it, T it2) {
    typename std::iterator_traits<T>::value_type;
    *it;
    ++it;
    it == it2;
    it != it2;
};

template <typename T>
concept bool BidirectionalIterator= Iterator<T> &&requires(T it, T it2) {
    --it;
};

template <typename T> concept bool BasicContainer= requires(T s, T const cs) {
    { std::begin(s) } ->Iterator;
    { std::end(s) } ->Iterator;
    { std::begin(cs) } ->Iterator;
    { std::end(cs) } ->Iterator;
    requires std::is_same_v<decltype(std::begin(s)), decltype(std::end(s))>;
    requires std::is_same_v<decltype(std::begin(cs)), decltype(std::end(cs))>;
};

template <typename T>
concept bool StringContainer= BasicContainer<T> &&requires(
    T s, T const cs, decltype(std::begin(s)) start,
    decltype(std::begin(s)) end) {
    s.erase(start, end);
    typename T::value_type;
    requires std::is_same_v<
        typename T::value_type,
        typename std::iterator_traits<decltype(std::begin(s))>::value_type>;
    requires std::is_same_v<
        typename T::value_type,
        typename std::iterator_traits<decltype(std::begin(cs))>::value_type>;
};

template <typename T>
concept bool
    CopyableStringContainer= StringContainer<std::remove_reference_t<T>> &&
    requires(T s, decltype(std::begin(s)) start, decltype(std::begin(s)) end) {
    std::remove_reference_t<T>(start, end);
};

template <typename Predicate, typename CharacterType>
concept bool WhitespacePredicate=
    requires(Predicate predicate, CharacterType character) {
    { predicate(character) } ->bool;
};

#define REQUIRES(x) requires x
#define ENABLE_IF_RETURN(expr, return_type) return_type
#else
template <
    typename Predicate, typename CharacterType,
    bool= std::is_invocable_v<Predicate, CharacterType>>
struct is_whitespace_predicate_impl {
    static constexpr bool value= false;
};

template <typename Predicate, typename CharacterType>
struct is_whitespace_predicate_impl<Predicate, CharacterType, true> {
    static constexpr bool value= std::is_convertible_v<
        decltype(std::declval<Predicate>()(std::declval<CharacterType>())),
        bool>;
};

template <typename Predicate, typename CharacterType>
constexpr bool is_whitespace_predicate=
    is_whitespace_predicate_impl<Predicate, CharacterType>::value;
#define REQUIRES(x)
#define ENABLE_IF_RETURN(expr, return_type)                                    \
    typename std::enable_if<(expr), return_type>::type
#endif

template <typename Iter>
REQUIRES(
    (Iterator<Iter> &&
     std::is_same_v<
         std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
         char>))
ENABLE_IF_RETURN(
    (std::is_same_v<
        std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
        char>),
    Iter) find_first_non_whitespace(Iter begin, Iter end) {
    auto pos= begin;
    for(; (pos != end) && std::isspace(*pos); ++pos)
        ;
    return pos;
}

template <typename Iter>
REQUIRES(
    (Iterator<Iter> &&
     std::is_same_v<
         std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
         wchar_t>))
ENABLE_IF_RETURN(
    (std::is_same_v<
        std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
        wchar_t>),
    Iter) find_first_non_whitespace(Iter begin, Iter end) {
    auto pos= begin;
    for(; (pos != end) && std::iswspace(*pos); ++pos)
        ;
    return pos;
}

template <typename Iter, typename CharacterList>
REQUIRES((Iterator<Iter> && BasicContainer<CharacterList>))
ENABLE_IF_RETURN(
    (!is_whitespace_predicate<
        CharacterList, typename std::iterator_traits<Iter>::value_type>),
    Iter)
    find_first_non_whitespace(
        Iter begin, Iter end, CharacterList &&space_chars) {
    auto pos= begin;
    auto begin_of_chars= std::begin(space_chars);
    auto end_of_chars= std::end(space_chars);
    for(; (pos != end) &&
          (std::find(begin_of_chars, end_of_chars, *pos) != end_of_chars);
        ++pos)
        ;
    return pos;
}

template <typename Iter, typename Predicate>
REQUIRES(
    (Iterator<Iter> &&
     WhitespacePredicate<
         Predicate, typename std::iterator_traits<Iter>::value_type>))
ENABLE_IF_RETURN(
    (is_whitespace_predicate<
        Predicate, typename std::iterator_traits<Iter>::value_type>),
    Iter)
find_first_non_whitespace(
    Iter begin, Iter end, Predicate &&is_white_space) {
    auto pos= begin;
    for(; (pos != end) && is_white_space(*pos); ++pos)
        ;
    return pos;
}

template <typename Iter>
REQUIRES(
    (BidirectionalIterator<Iter> &&
     std::is_same_v<
         std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
         char>))
ENABLE_IF_RETURN(
    (std::is_same_v<
        std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
        char>),
    Iter)
find_last_non_whitespace(Iter begin, Iter end) {
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && std::isspace(*endpos); ++endpos)
        ;
    return endpos.base();
}

template <typename Iter>
REQUIRES(
    (BidirectionalIterator<Iter> &&
     std::is_same_v<
         std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
         wchar_t>))
ENABLE_IF_RETURN(
    (std::is_same_v<
        std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
        wchar_t>),
    Iter)
find_last_non_whitespace(Iter begin, Iter end) {
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && std::iswspace(*endpos); ++endpos)
        ;
    return endpos.base();
}

template <typename Iter, typename CharacterList>
REQUIRES((Iterator<Iter> && BasicContainer<CharacterList>))
ENABLE_IF_RETURN(
    (!is_whitespace_predicate<
        CharacterList, typename std::iterator_traits<Iter>::value_type>),
    Iter)
find_last_non_whitespace(
    Iter begin, Iter end, CharacterList &&space_chars) {
    auto endpos= std::make_reverse_iterator(end);
    auto begin_of_chars= std::begin(space_chars);
    auto end_of_chars= std::end(space_chars);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) &&
        (std::find(begin_of_chars, end_of_chars, *endpos) != end_of_chars);
        ++endpos)
        ;
    return endpos.base();
}

template <typename Iter, typename Predicate>
REQUIRES(
    (BidirectionalIterator<Iter> &&
     WhitespacePredicate<
         Predicate, typename std::iterator_traits<Iter>::value_type>))
ENABLE_IF_RETURN(
    (is_whitespace_predicate<
        Predicate, typename std::iterator_traits<Iter>::value_type>),
    Iter)
find_last_non_whitespace(Iter begin, Iter end, Predicate &&is_white_space) {
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && is_white_space(*endpos); ++endpos)
        ;
    return endpos.base();
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim_left(Container &s) {
    s.erase(
        std::begin(s), find_first_non_whitespace(std::begin(s), std::end(s)));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim_right(Container &s) {
    s.erase(find_last_non_whitespace(std::begin(s), std::end(s)), std::end(s));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim(Container &s) {
    trim_left(s);
    trim_right(s);
}

template <typename Container, typename CharacterListOrPredicate>
REQUIRES(
    (StringContainer<Container> &&
     (WhitespacePredicate<
          CharacterListOrPredicate, typename Container::value_type> ||
      BasicContainer<CharacterListOrPredicate>)))
void trim_left(
    Container &s, CharacterListOrPredicate &&space_chars_or_predicate) {
    s.erase(
        std::begin(s),
        find_first_non_whitespace(
            std::begin(s), std::end(s), space_chars_or_predicate));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim_left(
    Container &s, typename Container::value_type const *space_chars) {
    trim_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim_left(Container &s, typename Container::value_type *space_chars) {
    trim_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container, typename CharacterListOrPredicate>
REQUIRES(
    (StringContainer<Container> &&
     (WhitespacePredicate<
          CharacterListOrPredicate, typename Container::value_type> ||
      BasicContainer<CharacterListOrPredicate>)))
void trim_right(
    Container &s, CharacterListOrPredicate &&space_chars_or_predicate) {
    s.erase(
        find_last_non_whitespace(
            std::begin(s), std::end(s), space_chars_or_predicate),
        std::end(s));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim_right(
    Container &s, typename Container::value_type const *space_chars) {
    trim_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim_right(Container &s, typename Container::value_type *space_chars) {
    trim_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container, typename CharacterListOrPredicate>
REQUIRES(
    (StringContainer<Container> &&
     (WhitespacePredicate<
          CharacterListOrPredicate, typename Container::value_type> ||
      BasicContainer<CharacterListOrPredicate>)))
void trim(Container &s, CharacterListOrPredicate &&space_chars_or_predicate) {
    trim_left(s, space_chars_or_predicate);
    trim_right(s, space_chars_or_predicate);
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim(Container &s, typename Container::value_type const *space_chars) {
    trim(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((StringContainer<Container>))
void trim(Container &s, typename Container::value_type *space_chars) {
    trim(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy_left(Container &&s) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(
        find_first_non_whitespace(std::begin(s), std::end(s)), std::end(s));
}

template <typename Container, typename CharacterListOrPredicate>
REQUIRES(
    (CopyableStringContainer<Container> &&
     (WhitespacePredicate<
          CharacterListOrPredicate,
          typename std::remove_reference_t<Container>::value_type> ||
      BasicContainer<CharacterListOrPredicate>)))
std::remove_reference_t<Container> trim_copy_left(
    Container &&s, CharacterListOrPredicate &&space_chars_or_predicate) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(
        find_first_non_whitespace(
            std::begin(s), std::end(s), space_chars_or_predicate),
        std::end(s));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy_left(
    Container &s, typename Container::value_type const *space_chars) {
    return trim_copy_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy_left(
    Container &s, typename Container::value_type *space_chars) {
    return trim_copy_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy_right(Container &&s) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(
        std::begin(s), find_last_non_whitespace(std::begin(s), std::end(s)));
}

template <typename Container, typename CharacterListOrPredicate>
REQUIRES(
    (CopyableStringContainer<Container> &&
     (WhitespacePredicate<
          CharacterListOrPredicate,
          typename std::remove_reference_t<Container>::value_type> ||
      BasicContainer<CharacterListOrPredicate>)))
std::remove_reference_t<Container> trim_copy_right(
    Container &&s, CharacterListOrPredicate &&space_chars_or_predicate) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(
        std::begin(s),
        find_last_non_whitespace(
            std::begin(s), std::end(s), space_chars_or_predicate));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy_right(
    Container &s, typename Container::value_type const *space_chars) {
    return trim_copy_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy_right(
    Container &s, typename Container::value_type *space_chars) {
    return trim_copy_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy(Container &&s) {
    using string_type= std::remove_reference_t<Container>;
    auto const begin= std::begin(s);
    auto const end= std::end(s);
    auto const copy_begin= find_first_non_whitespace(begin, end);
    return (copy_begin == end) ?
               string_type(end, end) :
               string_type(copy_begin, find_last_non_whitespace(begin, end));
}

template <typename Container, typename CharacterListOrPredicate>
REQUIRES(
    (CopyableStringContainer<Container> &&
     (WhitespacePredicate<
          CharacterListOrPredicate,
          typename std::remove_reference_t<Container>::value_type> ||
      BasicContainer<CharacterListOrPredicate>)))
std::remove_reference_t<Container> trim_copy(
    Container &&s, CharacterListOrPredicate &&space_chars_or_predicate) {
    using string_type= std::remove_reference_t<Container>;
    auto const begin= std::begin(s);
    auto const end= std::end(s);
    auto const copy_begin=
        find_first_non_whitespace(begin, end, space_chars_or_predicate);
    return (copy_begin == end) ?
               string_type(end, end) :
               string_type(
                   copy_begin, find_last_non_whitespace(
                                   begin, end, space_chars_or_predicate));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy(
    Container &s, typename Container::value_type const *space_chars) {
    return trim_copy(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
REQUIRES((CopyableStringContainer<Container>))
std::remove_reference_t<Container> trim_copy(
    Container &s, typename Container::value_type *space_chars) {
    return trim_copy(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}
