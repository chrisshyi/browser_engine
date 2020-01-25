#include "rule.h"
#include <string>
#include "selector.h"
#include "parser.h"	

class CSSParser : public Parser {
    private:
        size_t pos;
        std::string input;
    public:
        CSSParser(size_t pos, std::string input) : Parser{pos, input} {};
        std::string parse_identifier();
        SimpleSelector parse_simple_selector(); 
        // can't create a vector of Selectors since it is abstract
        // can replace this with std::vector<unique_ptr<Selector>> instead
        std::vector<SimpleSelector> parse_selectors();
        std::vector<Declaration> parse_declarations();
        Rule parse_rule();
};