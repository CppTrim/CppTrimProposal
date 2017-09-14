#pragma once

#include <cctype>
#include <type_traits>
#include <iterator>
#include <algorithm>

template<typename Iterator>
Iterator find_first_non_whitespace(Iterator begin,Iterator end){
    auto pos=begin;
    for(;(pos!=end) && std::isspace(*pos);++pos);
    return pos;
}

template<typename Iterator,typename CharacterList>
Iterator find_first_non_whitespace(Iterator begin,Iterator end,CharacterList&& space_chars){
    auto pos=begin;
    auto begin_of_chars=std::begin(space_chars);
    auto end_of_chars=std::end(space_chars);
    for(;(pos!=end) && (std::find(begin_of_chars,end_of_chars,*pos)!=end_of_chars);++pos);
    return pos;
}

template<typename Iterator>
Iterator find_last_non_whitespace(Iterator begin,Iterator end){
    auto endpos= std::make_reverse_iterator(end);
    for(auto start= std::make_reverse_iterator(begin);
        (endpos != start) && std::isspace(*endpos); ++endpos);
    return endpos.base();
}

template<typename Container>
void trim_left(Container& s){
    s.erase(s.begin(),find_first_non_whitespace(s.begin(),s.end()));
}

template<typename Container>
void trim_right(Container& s){
    s.erase(find_last_non_whitespace(s.begin(),s.end()),s.end());
}

template<typename Container>
void trim(Container& s){
    trim_left(s);
    trim_right(s);
}

template<typename Container,typename CharacterList>
void trim_left(Container& s,CharacterList&& space_chars){
    s.erase(s.begin(),find_first_non_whitespace(s.begin(),s.end(),space_chars));
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

template<typename Container>
std::remove_reference_t<Container> trim_copy_left(Container&& s){
    using string_type=std::remove_reference_t<Container>;
    return string_type(find_first_non_whitespace(s.begin(),s.end()),s.end());
}

template<typename Container>
std::remove_reference_t<Container> trim_copy_right(Container&& s){
    using string_type=std::remove_reference_t<Container>;
    return string_type(s.begin(),find_last_non_whitespace(s.begin(),s.end()));
}

template<typename Container>
std::remove_reference_t<Container> trim_copy(Container&& s){
    using string_type=std::remove_reference_t<Container>;
    auto const begin=s.begin();
    auto const end=s.end();
    auto const copy_begin=find_first_non_whitespace(begin,end);
    return (copy_begin==end)?string_type(end,end):
        string_type(
        copy_begin,
        find_last_non_whitespace(begin,end));
}

