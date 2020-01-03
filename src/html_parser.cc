#include "../include/browser_engine/html_parser.h"
#include <cctype>
#include <cassert>
#include <utility>

bool HTMLParser::starts_with(const string& substr) {
	if (substr.size() > input.size() - pos) {
		return false;
	}
	decltype(substr.size()) i = 0;
	for (; i < substr.size(); i++) {
		if (substr.at(i) != input.at(i + pos)) {
		    return false;
		}
	}
	return true;
}
size_t HTMLParser::get_pos() {
	return pos;
}
string HTMLParser::parse_tagname() {
	std::function<bool(char)> is_alpha_or_digit = [](char c) { return isalpha(c) || isdigit(c); };
    return this->consume_while(is_alpha_or_digit);
}

Node HTMLParser::parse_node() {
    if (this->next_char() == '<') {
        return this->parse_element();
    } else {
        return this->parse_text();
    }
}


Node HTMLParser::parse_text() {
	std::function<bool(char)> get_text = [](char c) { return c != '<'; };
	Node new_node{this->consume_while(get_text)};
	return new_node;
}            

Node HTMLParser::parse_element() {
	using std::cout;
	using std::endl;
	assert(this->consume_char() == '<');
	auto tag_name = this->parse_tagname();
	auto attrs = this->parse_attributes();
	assert(this->consume_char() == '>');

	auto children = this->parse_nodes();
	assert(this->consume_char() == '<');
	assert(this->consume_char() == '/');
	assert(this->parse_tagname() == tag_name);
	assert(this->consume_char() == '>');
	return Node{tag_name, attrs, children};
}

tuple<string, string> HTMLParser::parse_attr() {
	auto name = this->parse_tagname();
	assert(this->consume_char() == '=');
	auto value = this->parse_attr_value();
	return tuple{name, value};
}

string HTMLParser::parse_attr_value() {
	auto open_quote = this->consume_char();
	assert(open_quote == '\'' || open_quote == '\"');
	// std::function<bool(char)> not_eq_open_quote = 
	auto value = this->consume_while([open_quote](char c) { return c != open_quote; });
	assert(this->consume_char() == open_quote);
	return value;
}

AttrMap HTMLParser::parse_attributes() {
	AttrMap map;
	while (true) {
		this->consume_whitespace();
		if (this->next_char() == '>') {
			break;
		}
		auto attr = this->parse_attr();
		auto key = std::get<0>(attr);
		auto value = std::get<1>(attr);
		map.insert(std::make_pair(key, value));
	}
	return map;
}

vector<Node> HTMLParser::parse_nodes() {
	vector<Node> nodes;
	while (true) {
		this->consume_whitespace();
		if (this->eof() || this->starts_with("</")) {
			break;
		}
		nodes.push_back(this->parse_node());
	}
	return nodes;
}

Node parse(string source) {
	HTMLParser parser {0, source};
	auto nodes = parser.parse_nodes();

	if (nodes.size() == 1) {
		Node root = nodes[0];
		nodes.pop_back();
		return root;
	} else {
		Node root = Node("html", AttrMap(), nodes);
		return root;
	}
}