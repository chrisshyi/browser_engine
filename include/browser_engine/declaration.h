#include <string>
#include <variant>

class Declaration {
    public:
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
        using Value = std::variant<std::string, Length, Color>;
    private:
        std::string name;
        Value value;
};