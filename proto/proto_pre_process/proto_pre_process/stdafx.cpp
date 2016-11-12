#include "stdafx.h"

std::string ToUppercaseUnderscore(std::string target) {
	std::string ret;
	for (std::size_t i = 0; i < target.length(); i++) {
		auto current_char = target[i];
		ret.push_back(std::toupper(current_char));

		if (i + 1 < target.length()) {
			auto next_char = target[i + 1];
			if ('A' <= next_char && next_char <= 'Z') {
				ret.push_back('_');
			}
		}
	}
	return ret;
}

std::string ToLowercaseUnderscore(std::string target) {
	std::string ret;
	for (std::size_t i = 0; i < target.length(); i++) {
		auto current_char = target[i];
		ret.push_back(std::tolower(current_char));

		if (i + 1 < target.length()) {
			auto next_char = target[i + 1];
			if ('A' <= next_char && next_char <= 'Z') {
				ret.push_back('_');
			}
		}
	}
	return ret;
}