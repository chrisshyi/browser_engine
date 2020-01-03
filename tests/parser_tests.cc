#include "catch.hpp"
#include <string>
#include "../include/browser_engine/html_parser.h"
#include "../include/browser_engine/node.h"

using std::string;

TEST_CASE("Simple HTML parsing test", "[parser]") {

    string test_str {"<html> <head foo=\"bar\"> </head> </html>"};

    Node root = parse(test_str);

    REQUIRE(root.get_children_ref().size() == 1);
    REQUIRE(root.get_node_type() == NodeType::ELEMENT);
    Node child = root.get_children_ref().at(0);
    REQUIRE(child.get_node_type() == NodeType::ELEMENT);
    auto data = std::get<ElementData>(child.get_node_data());
    auto prop_map = data.get_attr_map();
    auto search = prop_map.find("foo");
    REQUIRE(search->first == "foo");
    REQUIRE(search->second == "bar");
}