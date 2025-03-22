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
#include <chrono>
#include <algorithm>
#include <iostream>

class LibrarySortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Library Sort" };

	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

	static void LibrarySortAlgorithm(std::vector<int> &a) {
		std::sort(a.begin(), a.end());
	}

private:

	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};
