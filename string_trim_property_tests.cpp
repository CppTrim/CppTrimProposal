#include "string_trim.hpp"

#include <string>
#include <vector>

#include "rapidcheck.h"

std::string create_whitespace_string_of_length(unsigned int l) {
	std::string rv;
	for (unsigned int i = 0; i < l; ++i) {
		rv += *rc::gen::element(" ", "\n", " ", "\r", " ", "\f", " ", "\t");
	}
	return rv;
}

char const *const whitespace_chars = " \n\r\f\t";

bool is_whitespace(char c) {
	return c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t';
}

class whitespace_ctype: public std::ctype<char> {
	mask mask_table[std::ctype<char>::table_size];
  public:
	whitespace_ctype(): std::ctype<char>(mask_table) {
		auto const default_table = std::ctype<char>::classic_table();
		for (unsigned i = 0; i<std::ctype<char>::table_size; ++i) {
			mask_table[i] = default_table[i];
			if (is_whitespace(i)) {
				mask_table[i] |= space;
			}
		}
	}
};

void default_trim(std::string & s) { trim(s); }
void trim_with_string(std::string & s) { trim(s, whitespace_chars); }
void trim_with_predicate(std::string & s) { trim(s, is_whitespace); }
void trim_with_locale(std::string & s) { std::locale custom_locale(std::locale(), new whitespace_ctype()); trim(s, custom_locale); }
void default_trim_left(std::string & s) { trim_left(s); }
void trim_left_with_string(std::string & s) { trim_left(s, whitespace_chars); }
void trim_left_with_predicate(std::string & s) { trim_left(s, is_whitespace); }
void trim_left_with_locale(std::string & s) { std::locale custom_locale(std::locale(), new whitespace_ctype()); trim_left(s, custom_locale); }
void default_trim_right(std::string & s) { trim_right(s); }
void trim_right_with_string(std::string & s) { trim_right(s, whitespace_chars); }
void trim_right_with_predicate(std::string & s) { trim_right(s, is_whitespace); }
void trim_right_with_locale(std::string & s) { std::locale custom_locale(std::locale(), new whitespace_ctype()); trim_right(s, custom_locale); }

struct void_function {
	std::string name;
	void (*f)(std::string &);
};

void_function default_trim_spec = {"default trim", default_trim};
void_function trim_with_string_spec = {"trim with string", trim_with_string};
void_function trim_with_predicate_spec = {"trim with predicate", trim_with_predicate};
void_function trim_with_locale_spec = {"trim with locale", trim_with_locale};
void_function default_trim_left_spec = {"default trim_left", default_trim_left};
void_function trim_left_with_string_spec = {"trim_left with string", trim_left_with_string};
void_function trim_left_with_predicate_spec = {"trim_left with predicate", trim_left_with_predicate};
void_function trim_left_with_locale_spec = {"trim_left with locale", trim_left_with_locale};
void_function default_trim_right_spec = {"default trim_right", default_trim_right};
void_function trim_right_with_string_spec = {"trim_right with string", trim_right_with_string};
void_function trim_right_with_predicate_spec = {"trim_right with predicate", trim_right_with_predicate};
void_function trim_right_with_locale_spec = {"trim_right with locale", trim_right_with_locale};

void_function void_functions[] = {
	default_trim_spec,
	trim_with_string_spec,
	trim_with_predicate_spec,
	trim_with_locale_spec,
	default_trim_left_spec,
	trim_left_with_string_spec,
	trim_left_with_predicate_spec,
	trim_left_with_locale_spec,
	default_trim_right_spec,
	trim_right_with_string_spec,
	trim_right_with_predicate_spec,
	trim_right_with_locale_spec,
};

std::string default_trim_copy(std::string & s) { return trim_copy(s); }
std::string trim_copy_with_string(std::string & s) { return trim_copy(s, whitespace_chars); }
std::string trim_copy_with_predicate(std::string & s) { return trim_copy(s, is_whitespace); }
std::string trim_copy_with_locale(std::string & s) { std::locale custom_locale(std::locale(), new whitespace_ctype()); return trim_copy(s, custom_locale); }
std::string default_trim_copy_left(std::string & s) { return trim_copy_left(s); }
std::string trim_copy_left_with_string(std::string & s) { return trim_copy_left(s, whitespace_chars); }
std::string trim_copy_left_with_predicate(std::string & s) { return trim_copy_left(s, is_whitespace); }
std::string trim_copy_left_with_locale(std::string & s) { std::locale custom_locale(std::locale(), new whitespace_ctype()); return trim_copy_left(s, custom_locale); }
std::string default_trim_copy_right(std::string & s) { return trim_copy_right(s); }
std::string trim_copy_right_with_string(std::string & s) { return trim_copy_right(s, whitespace_chars); }
std::string trim_copy_right_with_predicate(std::string & s) { return trim_copy_right(s, is_whitespace); }
std::string trim_copy_right_with_locale(std::string & s) { std::locale custom_locale(std::locale(), new whitespace_ctype()); return trim_copy_right(s, custom_locale); }

struct string_function {
	std::string name;
	std::string (*f)(std::string &);
};

string_function default_trim_copy_spec = {"default trim_copy", default_trim_copy};
string_function  trim_copy_with_string_spec = {"trim_copy with string", trim_copy_with_string};
string_function  trim_copy_with_predicate_spec = {"trim_copy with predicate", trim_copy_with_predicate};
string_function  trim_copy_with_locale_spec = {"trim_copy with locale", trim_copy_with_locale};
string_function default_trim_copy_left_spec = {"default trim_copy_left", default_trim_copy_left};
string_function  trim_copy_left_with_string_spec = {"trim_copy_left with string", trim_copy_left_with_string};
string_function  trim_copy_left_with_predicate_spec = {"trim_copy_left with predicate", trim_copy_left_with_predicate};
string_function  trim_copy_left_with_locale_spec = {"trim_copy_left with locale", trim_copy_left_with_locale};
string_function default_trim_copy_right_spec = {"default trim_copy_right", default_trim_copy_right};
string_function  trim_copy_right_with_string_spec = {"trim_copy_right with string", trim_copy_right_with_string};
string_function  trim_copy_right_with_predicate_spec = {"trim_copy_right with predicate", trim_copy_right_with_predicate};
string_function  trim_copy_right_with_locale_spec = {"trim_copy_right with locale", trim_copy_right_with_locale};

string_function string_functions[] = {
	default_trim_copy_spec,
	trim_copy_with_string_spec,
	trim_copy_with_predicate_spec,
	trim_copy_with_locale_spec,
	default_trim_copy_left_spec,
	trim_copy_left_with_string_spec,
	trim_copy_left_with_predicate_spec,
	trim_copy_left_with_locale_spec,
	default_trim_copy_right_spec,
	trim_copy_right_with_string_spec,
	trim_copy_right_with_predicate_spec,
	trim_copy_right_with_locale_spec,
};

void test_whitespace_string_generator() {
	for (auto && function: void_functions) {
		rc::check("String generated is completely remove by " + function.name, [&function](uint8_t l){
				auto t = create_whitespace_string_of_length(l);
				RC_ASSERT(t.length() == l);
				function.f(t);
				RC_ASSERT(t.empty());
			});
	}
	for (auto && function: string_functions) {
		rc::check("Returned string is empty using " + function.name, [&function](uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto t = w;
				RC_ASSERT(t.length() == l);
				auto const r = function.f(t);
				RC_ASSERT(t == w);
				RC_ASSERT(r.empty());
			});
	}
}

void test_empty_string() {
	for (auto && function: void_functions) {
		rc::check("Empty string, " + function.name + " has no effect.", [&function](uint8_t l){
				std::string const s {""};
				auto t = s;
				RC_ASSERT(t.empty());
				function.f(t);
				RC_ASSERT(t.empty());
			});
	}
	for (auto && function: string_functions) {
		rc::check("Empty string, " + function.name + " returns empty string and doesn't change the original.", [&function](uint8_t l){
				std::string const s {""};
				auto t = s;
				RC_ASSERT(t.empty());
				auto const r = function.f(t);
				RC_ASSERT(t == s);
				RC_ASSERT(r.empty());
			});
	}
}

void test_string_with_no_trimable_whitespace() {
	for (auto && function: void_functions) {
		rc::check("String with no trimable whitespace, " + function.name + " has no effect.", [&function](std::string const s, uint8_t l){
				auto t = "x" + s + "x";
				auto const r = t;
				function.f(t);
				RC_ASSERT(t == r);
			});
	}
	for (auto && function: string_functions) {
		rc::check("String with no trimable whitespace, " + function.name + " returns empty string and doesn't change the original.", [&function](std::string const s, uint8_t l){
				auto const ss = "x" + s + "x";
				auto t = ss;
				auto const r = function.f(t);
				RC_ASSERT(t == ss);
				RC_ASSERT(t == r);
			});
	}
}

void test_string_with_trimable_whitespace_on_the_right() {
	void_function left_void_functions[] = {
		default_trim_left_spec,
		trim_left_with_string_spec,
		trim_left_with_predicate_spec,
		trim_left_with_locale_spec,
	};
	void_function right_void_functions[] = {
		default_trim_spec,
		trim_with_string_spec,
		trim_with_predicate_spec,
		trim_with_locale_spec,
		default_trim_right_spec,
		trim_right_with_string_spec,
		trim_right_with_predicate_spec,
		trim_right_with_locale_spec,
	};
	for (auto && function: left_void_functions) {
		rc::check("String with no whitespace on the left but whitespace to the right, " + function.name + " has no effect.", [&function](std::string const s, uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto const r = "x" + s + "x" + w + " ";
				auto t = r;
				function.f(t);
				RC_ASSERT(t == r);
			});
	}
	for (auto && function: right_void_functions) {
		rc::check("String with no whitespace on the left but whitespace to the right, " + function.name + " correctly removes whitespace from the right.", [&function](std::string const s, uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto const r = "x" + s + "x";
				auto t = r + w + " ";
				function.f(t);
				RC_ASSERT(t == r);
			});
	}
	string_function left_string_functions[] = {
		default_trim_copy_left_spec,
		trim_copy_left_with_string_spec,
		trim_copy_left_with_predicate_spec,
		trim_copy_left_with_locale_spec,
	};
	string_function right_string_functions[] = {
		default_trim_copy_spec,
		trim_copy_with_string_spec,
		trim_copy_with_predicate_spec,
		trim_copy_with_locale_spec,
		default_trim_copy_right_spec,
		trim_copy_right_with_string_spec,
		trim_copy_right_with_predicate_spec,
		trim_copy_right_with_locale_spec,
	};
	for (auto && function: left_string_functions) {
		rc::check("String with no whitespace on the left but whitespace to the right, " + function.name + " returns original string with original unchanged.", [&function](std::string const s, uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto const ss = "x" + s + "x" + w + " ";
				auto t = ss;
				auto const r = function.f(t);
				RC_ASSERT(t == ss);
				RC_ASSERT(ss == r);
			});
	}
	for (auto && function: right_string_functions) {
		rc::check("String with no whitespace on the left but whitespace to the right, " + function.name + " returns string with correctly removed whitespace from the right and original unchanged.", [&function](std::string const s, uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto const ss = "x" + s + "x";
				auto const sss = ss + w + " ";
				auto t = sss;
				auto const r = function.f(t);
				RC_ASSERT(t == sss);
				RC_ASSERT(ss == r);
			});
	}
}

void test_string_with_trimable_whitespace_on_the_left() {
	void_function left_void_functions[] = {
		default_trim_spec,
		trim_with_string_spec,
		trim_with_predicate_spec,
		trim_with_locale_spec,
		default_trim_left_spec,
		trim_left_with_string_spec,
		trim_left_with_predicate_spec,
		trim_left_with_locale_spec,
	};
	void_function right_void_functions[] = {
		default_trim_right_spec,
		trim_right_with_string_spec,
		trim_right_with_predicate_spec,
		trim_right_with_locale_spec,
	};
	for (auto && function: left_void_functions) {
		rc::check("String with no whitespace on the right but whitespace to the left, " + function.name + " correctly removes whitespace from the left.", [&function](std::string const s, uint8_t l){
			auto const w = create_whitespace_string_of_length(l);
			auto const r = "x" + s + "x";
			auto t = " " + w + r;
			function.f(t);
			RC_ASSERT(t == r);
		});
	}
	for (auto && function: right_void_functions) {
		rc::check("String with no whitespace on the right but whitespace to the left, " + function.name + " has no effect.", [&function](std::string const s, uint8_t l){
			auto const w = create_whitespace_string_of_length(l);
			auto t = " " + w + "x" + s + "x";
			auto const r = t;
			function.f(t);
			RC_ASSERT(t == r);
		});
	}
	string_function left_string_functions[] = {
		default_trim_copy_spec,
		trim_copy_with_string_spec,
		trim_copy_with_predicate_spec,
		trim_copy_with_locale_spec,
		default_trim_copy_left_spec,
		trim_copy_left_with_string_spec,
		trim_copy_left_with_predicate_spec,
		trim_copy_left_with_locale_spec,
	};
	string_function right_string_functions[] = {
		default_trim_copy_right_spec,
		trim_copy_right_with_string_spec,
		trim_copy_right_with_predicate_spec,
		trim_copy_right_with_locale_spec,
	};
	for (auto && function: left_string_functions) {
		rc::check("String with no whitespace on the right but whitespace to the left, " + function.name + " return original string with original unchanged.", [&function](std::string const s, uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto const ss = "x" + s + "x";
				auto const sss = " " + w + ss;
				auto t = sss;
				auto const r = function.f(t);
				RC_ASSERT(t == sss);
				RC_ASSERT(ss == r);
			});
	}
	for (auto && function: right_string_functions) {
		rc::check("String with no whitespace on the right but whitespace to the left, " + function.name + " returns string with correctly removed whitespace from the right, original is unchanged.", [&function](std::string const s, uint8_t l){
				auto const w = create_whitespace_string_of_length(l);
				auto const ss = " " + w + "x" + s + "x";
				auto t = ss;
				auto const r = function.f(t);
				RC_ASSERT(t == ss);
				RC_ASSERT(ss == r);
			});
	}
}

void test_string_with_trimable_whitespace_on_both_sides() {
	void_function both_void_functions[] = {
		default_trim_spec,
		trim_with_string_spec,
		trim_with_predicate_spec,
		trim_with_locale_spec,
	};
	void_function left_void_functions[] = {
		default_trim_left_spec,
		trim_left_with_string_spec,
		trim_left_with_predicate_spec,
		trim_left_with_locale_spec,
	};
	void_function right_void_functions[] = {
		default_trim_right_spec,
		trim_right_with_string_spec,
		trim_right_with_predicate_spec,
		trim_right_with_locale_spec,
	};
	for (auto && function: both_void_functions) {
		rc::check("String with whitespace on left and right, " + function.name + " correctly removes whitespace from either side.", [&function](std::string const s, uint8_t l_f, uint8_t l_b){
				auto const w_f = create_whitespace_string_of_length(l_f);
				auto const w_b = create_whitespace_string_of_length(l_b);
				auto const r = "x" + s + "x";
				auto t = " " + w_f + r + w_b + " ";
				function.f(t);
				RC_ASSERT(t == r);
			});
	}
	for (auto && function: left_void_functions) {
		rc::check("String with whitespace on left and right, " + function.name + " correctly removes whitespace from the left.", [&function](std::string const s, uint8_t l_f, uint8_t l_b){
				auto const w_f = create_whitespace_string_of_length(l_f);
				auto const w_b = create_whitespace_string_of_length(l_b);
				auto const r = "x" + s + "x" + w_b + " ";
				auto t = " " + w_f + r;
				function.f(t);
				RC_ASSERT(t == r);
			});
	}
	for (auto && function: right_void_functions) {
		rc::check("String with whitespace on left and right, " + function.name + " correctly removes whitespace from the right.", [&function](std::string const s, uint8_t l_f, uint8_t l_b){
				auto const w_f = create_whitespace_string_of_length(l_f);
				auto const w_b = create_whitespace_string_of_length(l_b);
				auto const r = " " + w_f + "x" + s + "x";
				auto t = r + w_b + " ";
				function.f(t);
				RC_ASSERT(t == r);
		});
	}
	string_function both_string_functions[] = {
		default_trim_copy_spec,
		trim_copy_with_string_spec,
		trim_copy_with_predicate_spec,
		trim_copy_with_locale_spec,
	};
	string_function left_string_functions[] = {
		default_trim_copy_left_spec,
		trim_copy_left_with_string_spec,
		trim_copy_left_with_predicate_spec,
		trim_copy_left_with_locale_spec,
	};
	string_function right_string_functions[] = {
		default_trim_copy_right_spec,
		trim_copy_right_with_string_spec,
		trim_copy_right_with_predicate_spec,
		trim_copy_right_with_locale_spec,
	};
	for (auto && function: both_string_functions) {
		rc::check("String with whitespace on left and right, " + function.name + " returns string correctly removed whitespace from either side, original remains unchanged.",[&function](std::string const s, uint8_t l_f, uint8_t l_b){
				auto const w_f = create_whitespace_string_of_length(l_f);
				auto const w_b = create_whitespace_string_of_length(l_b);
				auto const ss = "x" + s + "x";
				auto const sss = " " + w_f + ss + w_b + " ";
				auto t = sss;
				auto const r = function.f(t);
				RC_ASSERT(t == sss);
				RC_ASSERT(r == ss);
			});
	}
	for (auto && function: left_string_functions) {
		rc::check("String with whitespace on left and right, " + function.name + " return string correctly removed whitespace from the left, original remains unchanged.", [&function](std::string const s, uint8_t l_f, uint8_t l_b){
				auto const w_f = create_whitespace_string_of_length(l_f);
				auto const w_b = create_whitespace_string_of_length(l_b);
				auto const ss = "x" + s + "x" + w_b + " ";
				auto const sss = " " + w_f + ss;
				auto t = sss;
				auto const r = function.f(t);
				RC_ASSERT(t == sss);
				RC_ASSERT(r == ss);
			});
	}
	for (auto && function: right_string_functions) {
		rc::check("String with whitespace on left and right, " + function.name + " returns string with correctly removed whitespace from the right, original remains unchanged.", [&function](std::string const s, uint8_t l_f, uint8_t l_b){
				auto const w_f = create_whitespace_string_of_length(l_f);
				auto const w_b = create_whitespace_string_of_length(l_b);
				auto const ss = " " + w_f + "x" + s + "x";
				auto const sss = ss + w_b + " ";
				auto t = sss;
				auto const r = function.f(t);
				RC_ASSERT(t == sss);
				RC_ASSERT(r == ss);
		});
	}
}

int main() {
	test_whitespace_string_generator();
	test_empty_string();
	test_string_with_no_trimable_whitespace();
	test_string_with_trimable_whitespace_on_the_right();
	test_string_with_trimable_whitespace_on_the_left();
	test_string_with_trimable_whitespace_on_both_sides();
	return 0;
}
