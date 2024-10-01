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

class MergeSortTester : public TestClass {
public:
	static constexpr const std::string_view name { "Merge Sort" };
	const std::string_view &GetBaseName() const override { return name; }

private:
	std::vector<int> buffer { };

	// Merge from start to mid and mid + 1 to end

	void Merge(std::vector<int> &a, const size_t start, const size_t mid, const size_t end) {
		size_t n = end - start + 1; size_t n1 = mid - start + 1; size_t n2 = end - mid;
		size_t i = 0; size_t i1 = 0; size_t i2 = 0;
		
		while (i < n && i1 < n1 && i2 < n2) {
			int val1 = a[i1 + start];
			int val2 = a[i2 + mid + 1];
			if (val1 < val2) {
				buffer[i] = val1;
				i1++;
			}
			else {
				buffer[i] = val2;
				i2++;
			}
			i++;
		}

		while (i1 < n1) {
			int val1 = a[i1 + start];
			buffer[i] = val1;
			i1++;
			i++;
		}

		while (i2 < n2) {
			int val2 = a[i2 + mid + 1];
			buffer[i] = val2;
			i2++;
			i++;
		}

		for (size_t i = 0; i < n; ++i) {
			a[start + i] = buffer[i];
		}

		return;
	}

	void MergeSortHelper(std::vector<int> &a, size_t start, size_t end) {
		size_t mid = start + (end - start) / 2;
		if (start < mid) MergeSortHelper(a, start, mid);
		if (mid + 1 < end) MergeSortHelper(a, mid + 1, end);
		Merge(a, start, mid, end);
	}

public:
	using TestClass::TestClass;

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

	static void MergeSortAlgorithm(std::vector<int> &a) {
		std::sort(a.begin(), a.end());
	}

private:
	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};
