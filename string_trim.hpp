#pragma once

#include <cctype>
#include <type_traits>
#include <iterator>
#include <algorithm>

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

template <typename Iterator>
typename std::enable_if<
    std::is_same_v<
        char,
        std::remove_cv_t<typename std::iterator_traits<Iterator>::value_type>>,
    Iterator>::type
find_first_non_whitespace(Iterator begin, Iterator end) {
    auto pos= begin;
    for(; (pos != end) && std::isspace(*pos); ++pos)
        ;
    return pos;
}

template <typename Iterator>
typename std::enable_if<
    std::is_same_v<
        wchar_t,
        std::remove_cv_t<typename std::iterator_traits<Iterator>::value_type>>,
    Iterator>::type
find_first_non_whitespace(Iterator begin, Iterator end) {
    auto pos= begin;
    for(; (pos != end) && std::iswspace(*pos); ++pos)
        ;
    return pos;
}

template <typename Iterator, typename CharacterList>
typename std::enable_if<
    !is_whitespace_predicate<
        CharacterList, typename std::iterator_traits<Iterator>::value_type>,
    Iterator>::type
find_first_non_whitespace(
    Iterator begin, Iterator end, CharacterList &&space_chars) {
    auto pos= begin;
    auto begin_of_chars= std::begin(space_chars);
    auto end_of_chars= std::end(space_chars);
    for(; (pos != end) &&
          (std::find(begin_of_chars, end_of_chars, *pos) != end_of_chars);
        ++pos)
        ;
    return pos;
}

template <typename Iterator, typename Predicate>
typename std::enable_if<
    is_whitespace_predicate<
        Predicate, typename std::iterator_traits<Iterator>::value_type>,
    Iterator>::type
find_first_non_whitespace(
    Iterator begin, Iterator end, Predicate &&is_white_space) {
    auto pos= begin;
    for(; (pos != end) && is_white_space(*pos); ++pos)
        ;
    return pos;
}

template <typename Iterator>
typename std::enable_if<
    std::is_same_v<
        char,
        std::remove_cv_t<typename std::iterator_traits<Iterator>::value_type>>,
    Iterator>::type
find_last_non_whitespace(Iterator begin, Iterator end) {
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && std::isspace(*endpos); ++endpos)
        ;
    return endpos.base();
}

template <typename Iterator>
typename std::enable_if<
    std::is_same_v<
        wchar_t,
        std::remove_cv_t<typename std::iterator_traits<Iterator>::value_type>>,
    Iterator>::type
find_last_non_whitespace(Iterator begin, Iterator end) {
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && std::iswspace(*endpos); ++endpos)
        ;
    return endpos.base();
}

template <typename Iterator, typename CharacterList>
typename std::enable_if<
    !is_whitespace_predicate<
        CharacterList, typename std::iterator_traits<Iterator>::value_type>,
    Iterator>::type
find_last_non_whitespace(
    Iterator begin, Iterator end, CharacterList &&space_chars) {
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

template <typename Iterator, typename Predicate>
typename std::enable_if<
    is_whitespace_predicate<
        Predicate, typename std::iterator_traits<Iterator>::value_type>,
    Iterator>::type
find_last_non_whitespace(
    Iterator begin, Iterator end, Predicate &&is_white_space) {
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && is_white_space(*endpos); ++endpos)
        ;
    return endpos.base();
}

template <typename Container> void trim_left(Container &s) {
    s.erase(s.begin(), find_first_non_whitespace(s.begin(), s.end()));
}

template <typename Container> void trim_right(Container &s) {
    s.erase(find_last_non_whitespace(s.begin(), s.end()), s.end());
}

template <typename Container> void trim(Container &s) {
    trim_left(s);
    trim_right(s);
}

template <typename Container, typename CharacterListOrPredicate>
void trim_left(
    Container &s, CharacterListOrPredicate &&space_chars_or_predicate) {
    s.erase(
        s.begin(), find_first_non_whitespace(
                       s.begin(), s.end(), space_chars_or_predicate));
}

template <typename Container>
void trim_left(
    Container &s, typename Container::value_type const *space_chars) {
    trim_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
void trim_left(Container &s, typename Container::value_type *space_chars) {
    trim_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container, typename CharacterListOrPredicate>
void trim_right(
    Container &s, CharacterListOrPredicate &&space_chars_or_predicate) {
    s.erase(
        find_last_non_whitespace(s.begin(), s.end(), space_chars_or_predicate),
        s.end());
}

template <typename Container>
void trim_right(
    Container &s, typename Container::value_type const *space_chars) {
    trim_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
void trim_right(Container &s, typename Container::value_type *space_chars) {
    trim_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container, typename CharacterList>
void trim(Container &s, CharacterList &&space_chars) {
    trim_left(s, space_chars);
    trim_right(s, space_chars);
}

template <typename Container>
void trim(Container &s, typename Container::value_type const *space_chars) {
    trim(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
void trim(Container &s, typename Container::value_type *space_chars) {
    trim(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
std::remove_reference_t<Container> trim_copy_left(Container &&s) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(find_first_non_whitespace(s.begin(), s.end()), s.end());
}

template <typename Container, typename CharacterListOrPredicate>
std::remove_reference_t<Container> trim_copy_left(
    Container &&s, CharacterListOrPredicate &&space_chars_or_predicate) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(
        find_first_non_whitespace(s.begin(), s.end(), space_chars_or_predicate),
        s.end());
}

template <typename Container>
std::remove_reference_t<Container> trim_copy_left(
    Container &s, typename Container::value_type const *space_chars) {
    return trim_copy_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
std::remove_reference_t<Container>
trim_copy_left(Container &s, typename Container::value_type *space_chars) {
    return trim_copy_left(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
std::remove_reference_t<Container> trim_copy_right(Container &&s) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(s.begin(), find_last_non_whitespace(s.begin(), s.end()));
}

template <typename Container, typename CharacterListOrPredicate>
std::remove_reference_t<Container> trim_copy_right(
    Container &&s, CharacterListOrPredicate &&space_chars_or_predicate) {
    using string_type= std::remove_reference_t<Container>;
    return string_type(
        s.begin(),
        find_last_non_whitespace(s.begin(), s.end(), space_chars_or_predicate));
}

template <typename Container>
std::remove_reference_t<Container> trim_copy_right(
    Container &s, typename Container::value_type const *space_chars) {
    return trim_copy_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
std::remove_reference_t<Container>
trim_copy_right(Container &s, typename Container::value_type *space_chars) {
    return trim_copy_right(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
std::remove_reference_t<Container> trim_copy(Container &&s) {
    using string_type= std::remove_reference_t<Container>;
    auto const begin= s.begin();
    auto const end= s.end();
    auto const copy_begin= find_first_non_whitespace(begin, end);
    return (copy_begin == end) ?
               string_type(end, end) :
               string_type(copy_begin, find_last_non_whitespace(begin, end));
}

template <typename Container, typename CharacterListOrPredicate>
std::remove_reference_t<Container>
trim_copy(Container &&s, CharacterListOrPredicate &&space_chars_or_predicate) {
    using string_type= std::remove_reference_t<Container>;
    auto const begin= s.begin();
    auto const end= s.end();
    auto const copy_begin=
        find_first_non_whitespace(begin, end, space_chars_or_predicate);
    return (copy_begin == end) ?
               string_type(end, end) :
               string_type(
                   copy_begin, find_last_non_whitespace(
                                   begin, end, space_chars_or_predicate));
}

template <typename Container>
std::remove_reference_t<Container>
trim_copy(Container &s, typename Container::value_type const *space_chars) {
    return trim_copy(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}

template <typename Container>
std::remove_reference_t<Container>
trim_copy(Container &s, typename Container::value_type *space_chars) {
    return trim_copy(
        s, std::basic_string_view<typename Container::value_type>(space_chars));
}
