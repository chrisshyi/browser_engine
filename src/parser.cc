#include "../include/browser_engine/parser.h"
#include <vector>
#include <cctype>

char Parser::next_char() {
	return input.at(pos);
}

bool Parser::starts_with(const string& substr) {
	if (substr.size() > input.size()) {
		return false;
	}
	decltype(substr.size()) i = 0;
	for (; i < substr.size(); i++) {
		if (substr.at(i) != input.at(i)) return false;
	}
	return true;
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

string Parser::parse_tagname() {
	std::function<bool(char)> is_alpha_or_digit = [](char c) { return isalpha(c) || isdigit(c); };
    return this->consume_while(is_alpha_or_digit);
}
/*
Node Parser::parse_node() {
    if (this->next_char() == '<') {
        return this->parse_element();
    } else {
        return this->parse_text();
    }
}
*/

Node Parser::parse_text() {
	std::function<bool(char)> get_text = [](char c) { return c != '<'; };
	Node new_node{this->consume_while(get_text)};
	return new_node;
}            
