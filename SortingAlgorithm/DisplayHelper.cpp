#include "SortHelper.h"
#include <iostream>
#include <sstream>

using namespace std;

std::pair<bool, bool> IsSorted(std::vector<int> &a) {
	size_t n = a.size();
	bool bAsc = true;
	bool bDesc = true;

	for (size_t i = 1; i < n; i++) {
		if (a[i - 1] > a[i]) bAsc = false;
		if (a[i - 1] < a[i]) bDesc = false;
	}

	return make_pair(bAsc, bDesc);
}

void Display(std::vector<int> &a, const char *str, bool bDispSorted) {
	bool bDispColon;
	bool bDispBracket;
	if (str != nullptr && str != "\0") {
		cout << str;
		bDispColon = true;
		bDispBracket = true;
	}

	if (bDispSorted) {
		auto bSorted = IsSorted(a);
		bDispColon = true;
		if (bDispBracket) cout << " (";
		if (bSorted.first == true && bSorted.second == true) {
			if (a.empty()) cout << "Empty";
			else if (a.size() == 1) cout << "One element";
			else {
				cout << "All equal";
			}
		}
		else if (bSorted.first == false && bSorted.second == false) {
			cout << "Unsorted";
		}
		else if (bSorted.first == true) {
			cout << "Ascending";
		}
		else if (bSorted.second == true) {
			cout << "Descending";
		}

		if (bDispBracket) cout << ")";
	}

	if (bDispColon && !a.empty()) {
		cout << ": ";
	}

	if (!a.empty()) {
		cout << a[0];
		for (size_t i = 1; i < a.size(); i++) {
			cout << ", " << a[i];
		}
	}
	
	cout << endl;
}

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

