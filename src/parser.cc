#include "../include/browser_engine/parser.h"
#include <vector>
#include <cctype>
#include <cassert>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;

char Parser::next_char() {
	return input.at(pos);
}


bool Parser::eof() {
	return (pos == input.size());
}

char Parser::consume_char() {
	auto cur_char = input.at(pos);
	pos++;
	return cur_char;
}

/**
 * Consumes characters while func(char) evaluates to true
 * , outputs the consumed characters as a string
 */
string Parser::consume_while(std::function<bool(char)> func) {
    string result;
    while ((!this->eof()) && func(this->next_char())) {
       result.push_back(this->consume_char());
    }
   return result; 
}


void Parser::consume_whitespace() {
	std::function<bool(char)> is_space = [](char c) { return isspace(c); };
    this->consume_while(is_space);
}
