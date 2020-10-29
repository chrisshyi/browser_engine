#include "selector.h"
#include "declaration.h"
#include <vector>

class Rule {
    std::vector<Selector> selectors;
    std::vector<Declaration> declarations;
};