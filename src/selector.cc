#include "../include/browser_engine/selector.h"


Selector::Specificity SimpleSelector::calc_specificity() {
	size_t a = 0, b = 0;
	if (id.has_value()) {
		a = 1;
	}
	if (tag_name.has_value()) {
		b = 1;
	}
	size_t c = static_cast<size_t>(class_names.size());
	return std::make_tuple(a, b, c);
}