#pragma once
#include <vector>
#include "element_data.h"
#include <variant>
#include <iostream>
using std::vector;
enum class NodeType {
    TEXT,
    ELEMENT
};

class Node {
    private:
        vector<Node> children;        
        NodeType node_type;
        std::variant<string, ElementData> node_data;
    public:
        Node(string);
        Node(string, AttrMap, vector<Node>);
        Node(const Node&&);
        Node(const Node&);
        Node& operator=(const Node&&);
        Node& operator=(const Node&);
        NodeType get_node_type() {
            return node_type;
        };
        std::variant<string, ElementData> get_node_data() {
            return node_data;
        }
        vector<Node>& get_children_ref() {
            return children;
        }

        void print_node(string, bool);
};
