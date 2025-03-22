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

#include "TestClass.h"
class BubbleSortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Bubble Sort" };
	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static void BubbleSortAlgorithm(std::vector<int> &a) {
		auto n = a.size();
		bool bSorted = false;
		for (auto i = n - 1; i >= 1 && !bSorted; --i) {
			bSorted = true;
			for (size_t j = 0; j < i; j++) {
				if (a[j + 1] < a[j]) {
					std::swap(a[j], a[j + 1]);
					bSorted = false;
				}
			}
		}
	}

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

private:
	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};

