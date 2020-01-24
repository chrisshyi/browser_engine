#pragma once
#include <optional>
#include <string>
#include <vector>

using std::optional;
using std::string;
class Selector {

};

class SimpleSelector :  public Selector {
    private:
        optional<string> tag_name;
        optional<string> id;
        std::vector<string> class_names;
        
    public:
        SimpleSelector(optional<string> tag, optional<string> id) :
        tag_name{tag}, id{id}, class_names{} {};

        void set_tag_name(string new_tag_name) {
        	tag_name = new_tag_name;
        }

        void set_id(string new_id) {
        	id = new_id;
        }

        void add_class_name(string new_class_name) {
        	class_names.push_back(new_class_name);
        }

        optional<string> get_tag_name() {
            return tag_name;
        }

        optional<string> get_id() {
            return id;
        }

        std::vector<string> get_class_names() {
            return class_names;
        }
};