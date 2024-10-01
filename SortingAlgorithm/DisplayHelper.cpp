//////////////////////////////////////////////////////////////////////////
// Copyright (C) 2024  Rohit Jairaj Singh (rohit@singh.org.in)          //
//                                                                      //
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//                                                                      //
// You should have received a copy of the GNU General Public License    //
// along with this program.  If not, see <https://www.gnu.org/licenses/ //
//////////////////////////////////////////////////////////////////////////

#include "TestClassContainer.h"
#include <iostream>
#include <string>

using namespace std;

void DisplayString(const int val, const size_t size, const DisplayAlignment alignment) {
	DisplayString(std::to_string(val), size, alignment);
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

