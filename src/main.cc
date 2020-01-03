#include "../include/browser_engine/node.h"
#include "../include/browser_engine/html_parser.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
	/*
    Node child1{"child1"};
    Node child2{"child2"};
    Node child3{"child3"};
    Node grand_child1{"grandchild1"};
    Node grand_child2{"grandchild2"};
    Node child4{"child4", AttrMap(), vector<Node>{grand_child1, grand_child2}};
    vector<Node> children {child1, child2, child4, child3};
    Node root{"root", AttrMap(), children};
    root.print_node("", true);
    Parser parser{0, "    hello"};
    parser.consume_whitespace();
    cout << parser.next_char() << endl;
    cout << parser.starts_with("hell") << endl;
    cout << parser.get_pos() << endl;
    */

   	Node root_node = parse("<html> <head foo=\"bar\" style=\"color5\"> <body> </body> </head> </html>");
   	root_node.print_node("", true);
}