#include "catch.hpp"
#include <string>
#include "../include/browser_engine/css_parser.h"

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
}