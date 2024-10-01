
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

#pragma once

#include "SortHelper.h"

using namespace std;

inline void SelectionSortRange(std::vector<int> &a, size_t start, size_t end) {
	if (start >= end) return;

	for (size_t i = start; i <= end - 1; i++) {
		size_t lowest = i;
		for (size_t j = i + 1; j <= end; j++) {
			if (a[j] < a[lowest]) lowest = j;
		}

		swap(a[i], a[lowest]);
	}
}

inline void SelectionSort(std::vector<int> &a) {
	SelectionSortRange(a, 0, a.size() - 1);
}

class SelectionSortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Selection Sort" };
	
	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

private:
	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};