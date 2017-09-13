#include <assert.h>
#include <string>
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

void trim_empty_string_does_nothing(){
    std::string s;
    trim(s);
    assert(s.empty());
}

void trim_non_space_string_does_nothing(){
    std::string const orig="hello";
    auto s=orig;
    trim(s);
    assert(s==orig);
}

void trim_all_space_string_removes_everything(){
    std::string s="     ";
    trim(s);
    assert(s.empty());
}

void trim_spaces_from_left(){
    std::string const hello="hello";
    std::string s="     "+hello;
    trim(s);
    assert(s==hello);
}

void trim_spaces_from_right(){
    std::string const hello="hello";
    std::string s=hello+"     ";
    trim(s);
    assert(s==hello);
}

void trim_spaces_from_both_ends(){
    std::string const hello="hello";
    std::string s="     "+hello+"   ";
    trim(s);
    assert(s==hello);
}

void trim_spaces_from_left_only(){
    std::string const hello="hello     ";
    std::string s="     "+hello;
    trim_left(s);
    assert(s==hello);
}

void trim_spaces_from_right_only(){
    std::string const hello="     hello";
    std::string s=hello+"     ";
    trim_right(s);
    assert(s==hello);
}

void trim_copy_empty_string_does_nothing(){
    std::string orig;
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s.empty());
    assert(s2.empty());
}

void trim_copy_non_space_string_does_nothing(){
    std::string const orig="hello";
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s==orig);
    assert(s2==orig);
}

void trim_copy_all_space_string_removes_everything(){
    std::string const orig="     ";
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2.empty());
    assert(s==orig);
}

void trim_copy_spaces_from_left(){
    std::string const hello="hello";
    std::string const orig="     "+hello;
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_copy_spaces_from_right(){
    std::string const hello="hello";
    std::string const orig=hello+"     ";
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_copy_spaces_from_both_ends(){
    std::string const hello="hello";
    std::string const orig="     "+hello+"   ";
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_copy_spaces_from_left_only(){
    std::string const hello="hello     ";
    std::string const orig="     "+hello;
    auto s=orig;
    auto s2=trim_copy_left(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_copy_spaces_from_right_only(){
    std::string const hello="     hello";
    std::string const orig=hello+"     ";
    std::string s=orig;
    auto s2=trim_copy_right(s);
    assert(s2==hello);
    assert(s==orig);
}

int main(){
    trim_empty_string_does_nothing();
    trim_non_space_string_does_nothing();
    trim_all_space_string_removes_everything();
    trim_spaces_from_left();
    trim_spaces_from_right();
    trim_spaces_from_both_ends();
    trim_spaces_from_left_only();
    trim_spaces_from_right_only();
    trim_copy_empty_string_does_nothing();
    trim_copy_non_space_string_does_nothing();
    trim_copy_all_space_string_removes_everything();
    trim_copy_spaces_from_left();
    trim_copy_spaces_from_right();
    trim_copy_spaces_from_both_ends();
    trim_copy_spaces_from_left_only();
    trim_copy_spaces_from_right_only();
}
