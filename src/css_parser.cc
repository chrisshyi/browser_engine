#include "../include/browser_engine/css_parser.h"
#include <optional>

bool valid_identifier_char(char);

SimpleSelector CSSParser::parse_simple_selector() {
    SimpleSelector selector{std::nullopt, std::nullopt};
    while (!eof()) {
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
					break;
				}
        }
    }
    return selector;
}

bool valid_identifier_char(char c) {
	return isalpha(c) || (c == '-') || (c == '_') || isdigit(c);
}

std::string CSSParser::parse_identifier() {
	std::function<bool(char)> func {valid_identifier_char};
	return consume_while(func);
}
