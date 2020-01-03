#include <optional>
#include <string>
#include <vector>
class Selector {

};

class SimpleSelector :  public Selector {
    std::optional<std::string> tag_name;
    std::optional<std::string> id;
    std::vector<std::string> class_names;
};