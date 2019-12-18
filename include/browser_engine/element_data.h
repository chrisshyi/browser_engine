#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
using std::string;
using std::unordered_map;
using AttrMap = unordered_map<string, string>;

class ElementData {
    private:
        string tag_name;
        AttrMap attributes;
    public:
        ElementData(string tag_name, AttrMap attributes):
        tag_name{tag_name}, attributes{attributes} {}

        string get_tag_name() {
            return tag_name;
        };
        AttrMap get_attr_map() {
            return attributes;
        }
        string get_attr_str() {
            std::stringstream ss;

            for (auto& kv : attributes) {
                ss << kv.first << "=\"" << kv.second << "\" ";
            }
            return ss.str();
        }
};

