#include <string>
#include <variant>

class Declaration {
    public:
        enum class Unit {
            px // Can add other units
        };
        struct Length {
            double len;
            Unit unit;
        };
        struct Color {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        };
        using Value = std::variant<std::string, Length, Color>;
        std::string name;
        Value value;
};