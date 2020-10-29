#include "parser.h"

class HTMLParser : public Parser {
    public:
        HTMLParser(size_t pos, string input) : Parser {pos, input} {};
		bool starts_with(const string&);
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