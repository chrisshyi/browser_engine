#include <string>
#include <variant>

class Declaration {
    struct Length {
        enum class Unit {
            px // Can add other units
        };
        double len;
        Unit unit;
    };
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    std::string name;
    std::variant<std::string, Length, Color> value;
};