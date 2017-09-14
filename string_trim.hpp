#pragma once

#include <cctype>
#include <type_traits>
#include <iterator>

template<typename Iterator>
Iterator find_first_non_whitespace(Iterator begin,Iterator end){
    auto pos=begin;
    for(;(pos!=end) && std::isspace(*pos);++pos);
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

