#pragma once
#include <vector>
#include <string>
#include <iostream>

std::string ToString(const int val);

enum DisplayAlignment {
	DisplayCenter,
	DisplayLeft,
	DisplayRight
};

void DisplayString(const std::string &str, const size_t size, const DisplayAlignment alignment = DisplayCenter);
void DisplayString(const int val, const size_t size, const DisplayAlignment alignment = DisplayCenter);