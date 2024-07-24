#include "TestClassContainer.h"
#include <iostream>
#include <sstream>

using namespace std;

std::string ToString(const int val) {
	ostringstream buffer;
	buffer << val;
	return buffer.str();
}

void DisplayString(const int val, const size_t size, const DisplayAlignment alignment) {
	DisplayString(ToString(val), size, alignment);
}

void DisplayString(const std::string &str, const size_t size, const DisplayAlignment alignment) {
	size_t strsize = str.size();

	size_t leftpad = 0;
	size_t rightpad = 0;

	switch (alignment)
	{
	case DisplayCenter:
	default:
		leftpad = (size - strsize) / 2;
		rightpad = (size - strsize + 1) / 2;
		break;

	case DisplayLeft:
		leftpad = size - strsize;
		break;

	case DisplayRight:
		rightpad = size - strsize;
		break;
	}

	if (leftpad > 0) {
		cout << string(leftpad,  ' ');
	}

	cout << str;

	if (rightpad > 0) {
		cout << string(rightpad, ' ');
	}
}

