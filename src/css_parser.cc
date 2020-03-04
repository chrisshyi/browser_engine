#include "../include/browser_engine/css_parser.h"
#include <optional>
#include <algorithm>
#include <cassert>

bool valid_identifier_char(char);

SimpleSelector CSSParser::parse_simple_selector() {
    SimpleSelector selector{std::nullopt, std::nullopt};
    bool selector_ended = false;
    while (!eof() && !selector_ended) {
    	auto next_c = next_char();
        switch(next_c) {
            case '#': 
                consume_char();
                selector.set_id(parse_identifier());
                break;
            case '.':
            	consume_char();
            	selector.add_class_name(parse_identifier());
            	break;
            case '*':
            	consume_char();
            	break;
            default:
            	if (valid_identifier_char(next_c)) {
					selector.set_tag_name(parse_identifier());
				} else {
					selector_ended = true;
					break;
				}
        }
    }
    return selector;
}

bool valid_identifier_char(char c) {
	return isalnum(c) || (c == '-') || (c == '_');
}

std::string CSSParser::parse_identifier() {
	std::function<bool(char)> func {valid_identifier_char};
	return consume_while(func);
}

std::vector<unique_ptr<Selector>> CSSParser::parse_selectors() {
	std::vector<unique_ptr<Selector>> selectors;
	while (true) {
		selectors.push_back(std::make_unique<SimpleSelector>(parse_simple_selector()));
		consume_whitespace();
		auto next_c = next_char();
		if (next_c == ',') {
			consume_char();
			consume_whitespace();
		} else if (next_c == '{') { // start of declarations
			break;
		} // omit error handling
	}
	using Selector_ptr = unique_ptr<Selector>; 
	std::sort(selectors.begin(), selectors.end(), [] (Selector_ptr& a, Selector_ptr& b) {
		return a->calc_specificity() < b->calc_specificity();
	});
	return selectors;
}

Declaration CSSParser::parse_declaration() {
    auto property_name = parse_identifier();
    consume_whitespace();
    assert(consume_char() == ':');
    consume_whitespace();
    auto val = parse_value();
    consume_whitespace();
    assert(consume_char() == ';');

    return Declaration{property_name, val};
}

Declaration::Value CSSParser::parse_value() {
    auto next_c = next_char();
    if (isdigit(next_c)) {
        return parse_length();
    } else if (next_c == '#') {
        return parse_color();
    } else {
        return parse_identifier();
    }
}

Declaration::Value CSSParser::parse_length() {
    Declaration::Value{Declaration::Length{parse_float(), parse_unit()}};
}

Declaration::Value CSSParser::parse_color() {
    assert(consume_char() == '#');
    auto r = parse_hex_pair();
    auto g = parse_hex_pair();
    auto b = parse_hex_pair();

    Declaration::Value{Declaration::Color{r, g, b, 255}};
}

// parse two hexidecimal digits
uint8_t CSSParser::parse_hex_pair() {
    auto hex_substr = input.substr(pos, 2);
    pos += 2;
    return (uint8_t) std::stoi(hex_substr, nullptr, 16);
}