#pragma once

#include <cctype>
#include <type_traits>

template<typename Container>
void trim_left(Container& s){
    auto pos=s.begin();
    for(auto end=s.end();(pos!=end) && std::isspace(*pos);++pos);
    s.erase(s.begin(),pos);
}

template<typename Container>
void trim_right(Container& s){
    auto endpos=s.rbegin();
    for(auto end=s.rend();(endpos!=end) && std::isspace(*endpos);++endpos);
    s.erase(endpos.base(),s.end());
}

template<typename Container>
void trim(Container& s){
    trim_left(s);
    trim_right(s);
}

template<typename Container>
std::remove_reference_t<Container> trim_copy_left(Container&& s){
    using string_type=std::remove_reference_t<Container>;
    auto pos=s.begin();
    for(auto end=s.end();(pos!=end) && std::isspace(*pos);++pos);
    return string_type(pos,s.end());
}

template<typename Container>
std::remove_reference_t<Container> trim_copy_right(Container&& s){
    using string_type=std::remove_reference_t<Container>;
    auto endpos=s.rbegin();
    for(auto end=s.rend();(endpos!=end) && std::isspace(*endpos);++endpos);
    return string_type(s.begin(),endpos.base());
}

template<typename Container>
std::remove_reference_t<Container> trim_copy(Container&& s){
    auto temp=trim_copy_left(s);
    trim_right(temp);
    return temp;
}
