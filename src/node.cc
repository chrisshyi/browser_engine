#include "../include/browser_engine/node.h"
#include <algorithm>

Node::Node(string data) : children{}, node_type{NodeType::TEXT}, node_data{data}
{
}

Node::Node(string name, AttrMap attributes, vector<Node> children) : children{children}, node_type{NodeType::ELEMENT}, node_data{ElementData{name, attributes}}
{
}

Node::Node(const Node&& node_ref) {
    node_type = node_ref.node_type;
    node_data = std::move(node_ref.node_data);
    children = std::move(node_ref.children);
}

Node& Node::operator=(const Node&& node_ref) {
    node_type = node_ref.node_type;
    node_data = std::move(node_ref.node_data);
    children = std::move(node_ref.children);
    return *this;
}

Node::Node(const Node& other_node) {
    node_type = other_node.node_type;
    node_data = other_node.node_data;
    children = other_node.children;
}

Node& Node::operator=(const Node& node_ref) {
    node_type = node_ref.node_type;
    node_data = node_ref.node_data;
    children = node_ref.children;
    return *this;
}

void Node::print_node(string indent, bool last) {
    using std::cout;
    using std::endl;
    
    
    cout << indent;
    if (last) {
        cout << "\\-";
        indent += "   "; 
    } else {
        cout << "|-";
        indent += "| ";
    }
    if (node_type == NodeType::TEXT) {
        cout << std::get<string>(node_data) << endl;
    } else {
        cout << std::get<ElementData>(node_data).get_tag_name() << endl;
    }
    for (int i = 0; i < children.size(); i++) {
        children[i].print_node(indent, i == children.size() - 1);
    }
};