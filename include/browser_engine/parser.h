#pragma once
#include <cstdio>
#include <string>
#include <functional>
#include <tuple>
#include "node.h"
using std::size_t;
using std::string;
using std::tuple;
class Parser {

	protected:
		size_t pos;
		string input;

	public:
		Parser(size_t pos, string input) : pos{pos}, input{input} {};
		char next_char();
		bool eof();
		char consume_char();
		string consume_while(std::function<bool(char)>);
        void consume_whitespace();
};
