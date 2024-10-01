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
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;

inline size_t LeafSize(const size_t size) {
	if (size == 0) return 0;
	size_t temp = size;
	while ((temp - 1) & temp) {
		temp = (temp - 1) & temp;
	}

	return temp;
}

inline size_t ToWidth(const int val) {
	string str = ToString(val);
	return str.size();
}

inline size_t findMaxWidth(std::vector<int> &a) {
	size_t maxwidth = 0;
	for (auto &v : a) {
		size_t width = ToWidth(v);
		maxwidth = max(maxwidth, width);
	}
	return maxwidth;
}

inline void DisplayHeap(std::vector<int> &a) {
	size_t n = a.size();
	size_t width = findMaxWidth(a) + 2;
	size_t leafsize = LeafSize(n);
	size_t currwidth = width * leafsize;
	size_t currcount = 1;
	size_t i = 0;

	DisplayString(string("Heap Tree"), currwidth);
	cout << endl;
	while (i < n) {
		for (size_t j = 0; j < currcount && i < n; ++j, ++i) {
			DisplayString(a[i], currwidth);
		}
		cout << endl;
		currcount <<= 1;
		currwidth >>= 1;
	}
}

template <typename StoreType, typename Compare>
inline void Heapify(std::vector<StoreType> &a, const size_t root, const size_t last) {
	size_t parent = root;
	auto val = a[root];
	size_t leftchild = parent * 2 + 1;

	while (leftchild <= last) {
		const size_t rightchild = leftchild + 1;
		const size_t selected = leftchild == last || a[leftchild] > a[rightchild] ?
			leftchild : rightchild;
		if (!Compare::compare(val, a[selected])) break;
		a[parent] = a[selected];
		parent = selected;
		leftchild = parent * 2 + 1;
	}

	a[parent] = val;
}

template <typename StoreType, typename Compare>
inline void CreateHeap(std::vector<StoreType> &a) {
	size_t last = a.size() - 1;
	for (size_t i = (last / 2) + 1; i > 0; i--) {
		Heapify<StoreType, Compare>(a, i - 1, last);
	}
}

inline void HeapSort(std::vector<int> &a, bool bDisplayHeap = false) {
	size_t n = a.size();
	CreateHeap<int,  testless<int>>(a);
	if (bDisplayHeap) {
		TestClass::Display<int>(a, "Heap array", false);
		DisplayHeap(a);
	}
	for (size_t i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		Heapify<int, testless<int>>(a, 0, i - 1);
	}
}

inline void TestHeapSort() {
	std::vector<int> a{ 3, 4, 6, 9, 20, 88, 34, 5, 56, 32, 33, 83, 74, 17, 27, 7, 1, 2, 93, 31, 16, 43, 63, 68 };

	auto start = std::chrono::high_resolution_clock::now();

	TestClass::Display<int>(a, "Original", false);
	HeapSort(a, true);
	TestClass::Display<int>(a, "After HeapSort", true);

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;

	std::cout << "HeapSort Elapsed time: " << elapsed.count() << " s\n";
}

inline void TestHeapSort(std::vector<vector<int>> manyarray) {
	vector<int> a{ 3, 4, 6, 9, 20, 88, 34, 5, 56, 32, 33, 83, 74, 17, 27, 7, 1, 2, 93, 31, 16, 43, 63, 68 };

	auto start = std::chrono::high_resolution_clock::now();

	/*Display(a, "Original");
	HeapSort(a);
	Display(a, "After HeapSort"); */
	for (auto arr : manyarray) {
		HeapSort(arr);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;

	std::cout << "HeapSort Elapsed time: " << elapsed.count() << " s\n";
}

class HeapSortTester : public TestClass {
public:
	static constexpr const std::string_view name { "HeapSort" };
	using TestClass::TestClass;

	const std::string_view &GetBaseName() const override { return name; }

	static void HeapSortAlgorithm(std::vector<int> &a) {
		HeapSort(a);
	}

	static const std::vector<size_t> AllSortProperties;
	static auto &GetAllSortProperties() { return AllSortProperties; }

private:
	static const std::unordered_map<size_t, SortingFunction> sortmaps;
	const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const override { return sortmaps; }
};
