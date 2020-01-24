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
};