#include "string_trim.hpp"
#include <assert.h>
#include <string>
#include <vector>

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

void trim_spaces_and_tabs_from_both_ends(){
    std::string const hello="hello";
    std::string s="    \t \t \t   \t "+hello+"  \t \t\t\t\t ";
    trim(s);
    assert(s==hello);
}

void trim_empty_vector_does_nothing(){
    std::vector<char> s;
    trim(s);
    assert(s.empty());
}

void trim_non_space_vector_does_nothing(){
    std::vector<char> const orig{'h','e','l','l','o'};
    auto s=orig;
    trim(s);
    assert(s==orig);
}

void trim_all_space_vector_removes_everything(){
    std::vector<char> s(5,' ');
    trim(s);
    assert(s.empty());
}

void trim_vector_spaces_from_left(){
    std::vector<char> const hello{'h','e','l','l','o'};
    std::vector<char> s(5,' ');
    s.insert(s.end(),hello.begin(),hello.end());
    trim(s);
    assert(s==hello);
}

void trim_vector_spaces_from_right(){
    std::vector<char> const hello{'h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> s=hello;
    s.insert(s.end(),spaces.begin(),spaces.end());
    trim(s);
    assert(s==hello);
}

void trim_vector_spaces_from_both_ends(){
    std::vector<char> const hello{'h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> s=spaces;
    s.insert(s.end(),hello.begin(),hello.end());
    s.insert(s.end(),spaces.begin(),spaces.end());
    trim(s);
    assert(s==hello);
}

void trim_vector_spaces_from_left_only(){
    std::vector<char> const hello{'h','e','l','l','o',' ',' ',' '};
    std::vector<char> spaces(5,' ');
    std::vector<char> s=spaces;
    s.insert(s.end(),hello.begin(),hello.end());
    trim_left(s);
    assert(s==hello);
}

void trim_vector_spaces_from_right_only(){
    std::vector<char> const hello{' ',' ',' ',' ',' ','h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> s;
    s.insert(s.end(),hello.begin(),hello.end());
    s.insert(s.end(),spaces.begin(),spaces.end());
    trim_right(s);
    assert(s==hello);
}

void trim_vector_copy_empty_string_does_nothing(){
    std::vector<char> orig;
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s.empty());
    assert(s2.empty());
}

void trim_vector_copy_non_space_string_does_nothing(){
    std::vector<char> const orig{'h','e','l','l','o'};
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s==orig);
    assert(s2==orig);
}

void trim_vector_copy_all_space_string_removes_everything(){
    std::vector<char> const orig(6,' ');
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2.empty());
    assert(s==orig);
}

void trim_vector_copy_spaces_from_left(){
    std::vector<char> const hello{'h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> orig=spaces;
    orig.insert(orig.end(),hello.begin(),hello.end());
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_vector_copy_spaces_from_right(){
    std::vector<char> const hello{'h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> orig;
    orig.insert(orig.end(),hello.begin(),hello.end());
    orig.insert(orig.end(),spaces.begin(),spaces.end());
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_vector_copy_spaces_from_both_ends(){
    std::vector<char> const hello{'h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> orig=spaces;
    orig.insert(orig.end(),hello.begin(),hello.end());
    orig.insert(orig.end(),spaces.begin(),spaces.end());
    auto s=orig;
    auto s2=trim_copy(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_vector_copy_spaces_from_left_only(){
    std::vector<char> const hello{'h','e','l','l','o',' ',' ',' '};
    std::vector<char> spaces(5,' ');
    std::vector<char> orig=spaces;
    orig.insert(orig.end(),hello.begin(),hello.end());
    auto s=orig;
    auto s2=trim_copy_left(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_vector_copy_spaces_from_right_only(){
    std::vector<char> const hello{' ',' ',' ','h','e','l','l','o'};
    std::vector<char> spaces(5,' ');
    std::vector<char> orig;
    orig.insert(orig.end(),hello.begin(),hello.end());
    orig.insert(orig.end(),spaces.begin(),spaces.end());
    std::vector<char> s=orig;
    auto s2=trim_copy_right(s);
    assert(s2==hello);
    assert(s==orig);
}

void trim_left_with_specified_characters(){
    std::string const hello="hello";
    std::string const orig="aaabbabab"+hello;
    auto s=orig;
    trim_left(s,"ab");
    assert(s==hello);
}

void trim_left_with_specified_characters_via_char_pointer(){
    std::string const hello="hello";
    std::string const orig="aaabbabab"+hello;
    auto s=orig;
    char const* space_chars="ab";
    trim_left(s,space_chars);
    assert(s==hello);
}

void trim_left_with_specified_characters_via_non_const_char_pointer(){
    std::string const hello="hello";
    std::string const orig="aaabbabab"+hello;
    auto s=orig;
    char space_chars[]="ab";
    char* space_chars_ptr=space_chars;
    trim_left(s,space_chars_ptr);
    assert(s==hello);
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
    trim_spaces_and_tabs_from_both_ends();
    trim_empty_vector_does_nothing();
    trim_non_space_vector_does_nothing();
    trim_all_space_vector_removes_everything();
    trim_vector_spaces_from_left();
    trim_vector_spaces_from_right();
    trim_vector_spaces_from_both_ends();
    trim_vector_spaces_from_left_only();
    trim_vector_spaces_from_right_only();
    trim_vector_copy_empty_string_does_nothing();
    trim_vector_copy_non_space_string_does_nothing();
    trim_vector_copy_all_space_string_removes_everything();
    trim_vector_copy_spaces_from_left();
    trim_vector_copy_spaces_from_right();
    trim_vector_copy_spaces_from_both_ends();
    trim_vector_copy_spaces_from_left_only();
    trim_vector_copy_spaces_from_right_only();
    trim_left_with_specified_characters();
    trim_left_with_specified_characters_via_char_pointer();
    trim_left_with_specified_characters_via_non_const_char_pointer();
}
