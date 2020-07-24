#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
#include <optional>
using std::string;
using std::unordered_map;
using AttrMap = unordered_map<string, string>;
using std::optional;

class ElementData {
    private:
        string tag_name;
        AttrMap attributes;
    public:
        ElementData(string tag_name, AttrMap attributes):
        tag_name{tag_name}, attributes{attributes} {}


        optional<string> get_id() {
            auto id = attributes.find("id");
            if (id == attributes.end()) {
                return optional<string>();
            } 
            return optional<string>{id->second};
        }

        std::vector<string> get_classes() {
            std::vector<string> class_vec;
            auto classes = attributes.find("class");
            if (classes != attributes.end()) { 
                auto class_str = classes->second;
                auto space_index = class_str.find(" ");
                while (space_index != string::npos) {
                    class_vec.push_back(class_str.substr(0, space_index));
                    class_str = class_str.substr(space_index + 1, string::npos);
                    space_index = class_str.find(" ");
                }
                class_vec.push_back(class_str);
            }
            return class_vec;
        }

        string get_tag_name() {
            return tag_name;
        };
        AttrMap get_attr_map() {
            return attributes;
        }
        string get_attr_str() {
            std::stringstream ss;

            for (const auto& kv : attributes) {
                ss << kv.first << "=\"" << kv.second << "\" ";
            }
            return ss.str();
        }
};

