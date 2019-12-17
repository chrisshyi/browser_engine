#include <cstdio>
#include <string>
#include <functional>
#include "node.h"
using std::size_t;
using std::string;
class Parser {

	private:
		size_t pos;
		string input;

	public:
		Parser(size_t pos, string input) : pos{pos}, input{input} {};
		char next_char();
		bool starts_with(const string&);
		bool eof();
		char consume_char();
		string consume_while(std::function<bool(char)>);
        void consume_whitespace();
        string parse_tagname();
        Node parse_node();
        Node parse_text();
        Node parse_element();
};
