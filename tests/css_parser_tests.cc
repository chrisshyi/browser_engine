#include "catch.hpp"
#include <string>
#include "../include/browser_engine/css_parser.h"

const double EPSILON = 0.001;

bool isclose(double a, double b, double epsilon) {
    const double abs_a = abs(a);
    const double abs_b = abs(b);
    const double diff = abs(a - b);
    const double min_double = std::numeric_limits<double>::min();
    const double max_double = std::numeric_limits<double>::max();

    if (a == b) {
        return true;
    } else if (a == 0 || b == 0 
    || ((abs_a + abs_b) < min_double)
    ) {
        return diff < (epsilon * min_double);
    } else {
        return diff / std::min<double>((abs_a + abs_b), max_double) < epsilon; 
    }
}

TEST_CASE("Simple selector parsing", "[css_parser]") {
	SECTION("Parsing an id selector by itself") {
		CSSParser parser(0, "#my-div");
		auto selector = parser.parse_simple_selector();

		REQUIRE(selector.get_id().has_value());
		REQUIRE(selector.get_id().value() == "my-div");
		REQUIRE(!selector.get_tag_name().has_value());
		REQUIRE(selector.get_class_names().size() == 0);
	}

	SECTION("Parsing a class selector with one class") {
		CSSParser parser(0, ".my-class-name");
		auto selector = parser.parse_simple_selector();

		REQUIRE(!selector.get_id().has_value());
		REQUIRE(!selector.get_tag_name().has_value());
		REQUIRE(selector.get_class_names().size() == 1);
		REQUIRE(selector.get_class_names()[0] == "my-class-name");
	}

	SECTION("Parsing a class selector with multiple classes") {
		CSSParser parser(0, ".class1.class2.class3.class4");
		auto selector = parser.parse_simple_selector();

		REQUIRE(!selector.get_id().has_value());
		REQUIRE(!selector.get_tag_name().has_value());
		REQUIRE(selector.get_class_names().size() == 4);
		for (int i = 0; i < 4; i++) {
			auto class_name = "class" + std::to_string(i + 1);
			REQUIRE(selector.get_class_names()[i] == class_name);
		}
	}

	SECTION("Parsing a tag selector with one tag") {
		CSSParser parser(0, "div");
		auto selector = parser.parse_simple_selector();

		REQUIRE(!selector.get_id().has_value());
		REQUIRE(selector.get_tag_name().has_value());
		REQUIRE(selector.get_tag_name().value() == "div");
		REQUIRE(selector.get_class_names().size() == 0);
	}

	SECTION("Parsing a mixed selector with an id, classes, and a tag name") {
		CSSParser parser(0, "div#my-div.class1.class2.class3.class4");
		auto selector = parser.parse_simple_selector();

		REQUIRE(selector.get_id().has_value());
		REQUIRE(selector.get_id().value() == "my-div");
		REQUIRE(selector.get_tag_name().has_value());
		REQUIRE(selector.get_tag_name().value() == "div");
		REQUIRE(selector.get_class_names().size() == 4);
		for (int i = 0; i < 4; i++) {
			auto class_name = "class" + std::to_string(i + 1);
			REQUIRE(selector.get_class_names()[i] == class_name);
		}
	}
	SECTION("Parsing multiple selectors") {
		CSSParser parser(0, "div#my-div1.class1 div#my-div2.class2 {}");
		auto selectors = parser.parse_selectors();
		REQUIRE(selectors.size() == 2);
	}
}
TEST_CASE("CSS declaration parsing") {
    SECTION("Parse keyword value") {
        CSSParser parser(0, "margin: auto;");
        auto dec = parser.parse_declaration();
        REQUIRE(dec.name == "margin");
        REQUIRE(std::holds_alternative<std::string>(dec.value));
        REQUIRE(std::get<std::string>(dec.value) == "auto");
    }
    SECTION("Parse length") {
        CSSParser parser(0, "width: 5px;");
        auto dec = parser.parse_declaration();
        REQUIRE(dec.name == "width");
        REQUIRE(std::holds_alternative<Declaration::Length>(dec.value));
        auto len = std::get<Declaration::Length>(dec.value);
        REQUIRE(isclose(len.len, 5.0, EPSILON));
        REQUIRE(len.unit == Declaration::Unit::px);
    }
    SECTION("Parse color") {
        CSSParser parser(0, "background: #ff103B;");
        auto dec = parser.parse_declaration();
        REQUIRE(dec.name == "background");
        REQUIRE(std::holds_alternative<Declaration::Color>(dec.value));
        auto color = std::get<Declaration::Color>(dec.value);
        REQUIRE(color.r == 255);
        REQUIRE(color.g == 16);
        REQUIRE(color.b == 59);
        REQUIRE(color.a == 255);
    }
}
