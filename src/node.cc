#include "../include/browser_engine/node.h"

Node::Node(string data) : children{}, node_type{NodeType::TEXT}, node_data{data}
{
}

Node::Node(string name, AttrMap attributes, vector<Node> children) : children{children}, node_type{NodeType::ELEMENT}, node_data{ElementData{name, attributes}}
{
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