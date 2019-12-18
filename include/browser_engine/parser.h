#include <cstdio>
#include <string>
#include <functional>
#include <tuple>
#include "node.h"
using std::size_t;
using std::string;
using std::tuple;
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
        size_t get_pos();
        string parse_tagname();
        Node parse_node();
        vector<Node> parse_nodes();
        Node parse_text();
        Node parse_element();
        AttrMap parse_attributes();
        tuple<string, string> parse_attr();
        string parse_attr_value();
};

Node parse(string);