#include "string_trim.hpp"

#include <string>

#include "rapidcheck.h"

int main() {
	rc::check("Empty string means trim has no effect.", [](){
			std::string const s {""};
			auto t = s;
			trim(t);
			RC_ASSERT(t.empty());
		});
	rc::check("Empty string means trim_left has no effect.", [](){
			std::string const s {""};
			auto t = s;
			trim_left(t);
			RC_ASSERT(t.empty());
		});
	rc::check("Empty string means trim_right has no effect.", [](){
			std::string const s {""};
			auto t = s;
			trim_right(t);
			RC_ASSERT(t.empty());
		});
	rc::check("With no white space trim has no effect.", [](std::string const s){
			auto t = "x" + s + "x";
			auto const r = t;
			trim(t);
			RC_ASSERT(t == r);
		});
	rc::check("With no white space trim_left has no effect.", [](std::string const s){
			auto t = "x" + s + "x";
			auto r = t;
			trim_left(t);
			RC_ASSERT(t == r);
		});
	rc::check("With no white space trim_right has no effect.", [](std::string const s){
			auto t = "x" + s + "x";
			auto const r = t;
			trim_right(t);
			RC_ASSERT(t == r);
		});
	rc::check("With no white space on the left but whitespace to the right trim_left has no effect.", [](std::string const s, uint8_t i){
			std::string const w (i, ' ');
			auto t = "x" + s + w + " ";
			auto const r = t;
			trim_left(t);
			RC_ASSERT(t == r);
		});
	rc::check("With no white space on the right but whitespace to the left trim_right has no effect.", [](std::string const s, uint8_t i){
			std::string const w (i, ' ');
			auto t = " " + w + s + "x";
			auto const r = t;
			trim_right(t);
			RC_ASSERT(t == r);
		});
	rc::check("trim correctly removes random amounts of space from either side.", [](std::string const s, uint8_t i_f, uint8_t i_b){
			std::string const w_f (i_f, ' ');
			std::string const w_b (i_b, ' ');
			auto const r = "x" + s + "x";
			auto t = w_f + r + w_b;
			trim(t);
			RC_ASSERT(t == r);
		});
	rc::check("trim_left correctly removes random amounts of space from the left.", [](std::string const s, uint8_t i){
			std::string const w (i, ' ');
			auto const r = "x" + s;
			auto t = w + r;
			trim_left(t);
			RC_ASSERT(t == r);
		});
	rc::check("trim_right correctly removes random amounts of space from the right.", [](std::string const s, uint8_t i){
			std::string const w (i, ' ');
			auto const r = s + "x";
			auto t = r + w;
			trim_right(t);
			RC_ASSERT(t == r);
		});
	return 0;
}
