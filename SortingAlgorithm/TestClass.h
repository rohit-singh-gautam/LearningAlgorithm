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
#include <string>
#include <limits>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <ranges>


enum class SortOrder {
	Ascending,
	Descending,
	Random
};

class TestProperties {
	const size_t properties;
	const std::string propertystring;

	const auto CreatePropertiesString(size_t properties) {
		std::string property_string { "{ " };

		if(properties & N_Square) {
			property_string += "O(n^2) ";
		}

		if(properties & N_LogN) {
			property_string += "O(log(n)) ";
		}

		if(properties & Iterative) {
			property_string += "Iterative ";
		}

		if(properties & Recursive) {
			property_string += "Recursive ";
		}

		if(properties & TailRecursive) {
			property_string += "TailRecursion ";
		}

		if(properties & HeapEnabled) {
			property_string += "HeapEnabled ";
		}

		if(properties & OptimizedCustom) {
			property_string += "OptimizedCustom ";
		}

		if(properties & OptimizeLeft) {
			property_string += "OptimizeLeft ";
		}

		if(properties & Optimized) {
			property_string += "Optimized ";
		}

		if(properties & Randomize) {
			property_string += "Randomize ";
		}

		if(properties & Pointer) {
			property_string += "Pointer ";
		}

		property_string += "}";
		return property_string;
	}

public:
	enum property_type : size_t {
		NONE = 0x0,
		N_Square = 0x1,
		N_LogN = 0x2,
		Iterative = 0x4,
		Recursive = 0x8,
		TailRecursive = 0x10,
		HeapEnabled = 0x20,
		OptimizedCustom = 0x40,
		OptimizeLeft = 0x80,
		Optimized = 0x100,
		Randomize = 0x200,
		Pointer = 0x400,
	};

	template <class... Types>
	TestProperties(Types... args) : properties { (args | ...) }, propertystring { CreatePropertiesString(properties) } { }
	TestProperties(size_t properties) : properties { properties }, propertystring { CreatePropertiesString(properties) } { }
	virtual ~TestProperties() = default;

	const auto &GetProperyString() const { return propertystring; }
	auto GetProperty() const { return properties; }

	auto IsNSquare() const { return (properties & N_Square) != 0; }
	auto IsNLogN() const { return (properties & N_LogN) != 0; }
	auto IsIterative() const { return (properties & Iterative) != 0; }
	auto IsRecursive() const { return (properties & Recursive) != 0; }
	auto IsTailRecursive() const { return (properties & TailRecursive) != 0; }
	auto IsHeapEnabled() const { return (properties & HeapEnabled) != 0; }
	auto IsOptimizedCustom() const { return (properties & OptimizedCustom) != 0; }
	auto IsOptimizedLeft() const { return (properties & OptimizeLeft) != 0; }
	auto IsOptimized() const { return (properties & Optimized) != 0; }
	auto IsRandomize() const { return (properties & Randomize) != 0; }
	auto IsPointer() const { return (properties & Pointer) != 0; }

	template <class... Types>
	auto IsPropertySet(Types... args) {
		auto PropertyToCheck { (args | ...) };
		return PropertyToCheck == properties;
	}

	template <class... Types>
	static constexpr auto GetPropertyString(Types... args) {
		size_t properties { (args | ...) };
		return properties;
	}

	operator size_t() const { return properties; }
};


class TestClassBase : public TestProperties {
protected:
	size_t NumberOfArraySorted  { 0 };
	decltype(std::chrono::high_resolution_clock::now()) begin_time { };
	decltype(std::chrono::high_resolution_clock::now()) end_time { };
	std::chrono::duration<double> elapsed_time { 0 };

	size_t InitialSortedAsc { 0 };
	size_t InitialSortedDesc { 0 };
	size_t SortedAfterExecutionAsc { 0 };
	size_t SortedAfterExecutionDesc { 0 };

	virtual const std::string_view &GetBaseName() const = 0;
	virtual void InitiateSort(size_t ArrayIndex) = 0;
	virtual size_t GettArrayListSize() const = 0;

public:
	using TestProperties::TestProperties;

	void Sort(size_t NumberOfArrayToSort) {
		if (NumberOfArraySorted + NumberOfArrayToSort > GettArrayListSize()) return;
		begin_time = std::chrono::high_resolution_clock::now();

		for (size_t i = 0; i < NumberOfArrayToSort; i++) {
			InitiateSort(NumberOfArraySorted + i);
		}

		end_time = std::chrono::high_resolution_clock::now();

		NumberOfArraySorted += NumberOfArrayToSort;
		elapsed_time += end_time - begin_time;
	}

	template <typename StoreType>
	static auto IsSorted(std::vector<StoreType> &array) {
		auto n = array.size();
		bool ArrayIsSortedAsc = true;
		bool ArrayIsSortedDesc = true;

		for (decltype(array.size()) i = 1; i < n; i++) {
			if (array[i - 1] > array[i]) ArrayIsSortedAsc = false;
			if (array[i - 1] < array[i]) ArrayIsSortedDesc = false;
		}

		return std::make_pair(ArrayIsSortedAsc, ArrayIsSortedDesc);
	}

	virtual void FindSorted() = 0;
	virtual void DisplayResult() const = 0;
	auto getElapsedTime() const {
		return elapsed_time;
	}

	const auto GetName() const {
		return std::string { GetBaseName() } + " " + GetProperyString();
	}

	static void DisplaySorted(std::string pre,  size_t count, size_t Asc, size_t Desc) {
		std::cout << pre << " Sorted: " << count;
		std::cout << "(";
		if (Asc == 0 && Desc == 0) {
			std::cout << "unsorted";
		}
		else if (Asc > 0 && Desc > 0) {
			std::cout << "asc:" << Asc << ",desc:" << Desc;
		}
		else if (Asc > 0) {
			std::cout << "asc";
			if (Asc < count) std::cout << ":" << Asc;
		}
		else if (Desc > 0) {
			std::cout << "desc:" << Desc;
			if (Desc < count) std::cout << ":" << Desc;
		}
		std::cout << ")";
	}
};

typedef void (*SortingFunction)(std::vector<int> &a);

class TestClass : public TestClassBase {
private:
	std::vector<std::vector<int>> &arrays;

protected:
	std::string Name { };
	virtual void SortAlgorithm(std::vector<int> &a) {
		auto sortmaps = GetSortMapping();
		auto sortfunctionitr = sortmaps.find(GetProperty());
		if (sortfunctionitr == std::end(sortmaps)) {
			throw std::invalid_argument("Unsupported sorting alogrithm");
		}
		auto sortfunction = *sortfunctionitr->second;
		sortfunction(a);
	}

	void InitiateSort(size_t ArrayIndex) override {
		SortAlgorithm(arrays[ArrayIndex]);
	}

public:
	TestClass(std::vector<std::vector<int>> &inarrays, size_t properties) : TestClassBase { properties }, arrays { inarrays } {
		for (auto &inarray : inarrays) {
			auto srtpr = IsSorted(inarray);
			if (srtpr.first) InitialSortedAsc++;
			if (srtpr.second) InitialSortedDesc++;
		}
	}

	template <class... Types>
	TestClass(std::vector<std::vector<int>> &inarrays, Types... properties) : TestClassBase { (properties | ...) }, arrays { (inarrays) } {
		for (auto &inarray : inarrays) {
			auto srtpr = IsSorted(inarray);
			if (srtpr.first) InitialSortedAsc++;
			if (srtpr.second) InitialSortedDesc++;
		}
	}

	size_t GettArrayListSize() const override { return arrays.size(); }

private:
	virtual const std::unordered_map<size_t, SortingFunction> &GetSortMapping() const = 0;

public:

	void FindSorted() override {
		SortedAfterExecutionAsc = 0;
		SortedAfterExecutionDesc = 0;
		for (auto &array : arrays) {
			auto srtpr = IsSorted<int>(array);
			if (srtpr.first) SortedAfterExecutionAsc++;
			if (srtpr.second) SortedAfterExecutionDesc++;
		}
	}

	void DisplayResult() const override {
		std::cout << GetName() << ": " << elapsed_time.count() << " s; ";
		DisplaySorted("Initial", arrays.size(), InitialSortedAsc, InitialSortedDesc);
		std::cout << "; ";
		DisplaySorted("Final", arrays.size(), SortedAfterExecutionAsc, SortedAfterExecutionDesc);
		std::cout << std::endl;
	}

	template <typename IntType = int>
	static std::vector<IntType> GenerateRandomArray(size_t size, IntType min_val = 0, IntType max_val = std::numeric_limits<IntType>::max()) {
		std::vector<IntType> ret(size);
		for (size_t i = 0; i < size; i++) {
			IntType rnd = (rand() % (max_val - min_val + 1)) + min_val;
			ret[i] = rnd;
		}
		return ret;
	}

	template <typename IntType = int>
	static std::vector<std::vector<IntType>> GenerateManyArray(size_t count, size_t size, IntType min_val = 0, IntType max_val = std::numeric_limits<IntType>::max()) {
		std::vector<std::vector<IntType>> arrays(count, std::vector<IntType>(size));
		for (size_t i = 0; i < count; ++i) {
			for (size_t j = 0; j < size; j++) {
				IntType rnd = (rand() % (max_val - min_val + 1)) + min_val;
				arrays[i][j] = rnd;
			}
		}
		return arrays;
	}

	template <typename StorageType>
	static void Display(std::vector<StorageType> &a, const char *str, bool bDispSorted) {
		bool bDispColon;
		bool bDispBracket;
		if (str != nullptr && *str != '\0') {
			std::cout << str;
			bDispColon = true;
			bDispBracket = true;
		}

		if (bDispSorted) {
			auto bSorted = TestClass::IsSorted<StorageType>(a);
			bDispColon = true;
			if (bDispBracket) std::cout << " (";
			if (bSorted.first == true && bSorted.second == true) {
				if (a.empty()) std::cout << "Empty";
				else if (a.size() == 1) std::cout << "One element";
				else {
					std::cout << "All equal";
				}
			}
			else if (bSorted.first == false && bSorted.second == false) {
				std::cout << "Unsorted";
			}
			else if (bSorted.first == true) {
				std::cout << "Ascending";
			}
			else if (bSorted.second == true) {
				std::cout << "Descending";
			}

			if (bDispBracket) std::cout << ")";
		}

		if (bDispColon && !a.empty()) {
			std::cout << ": ";
		}

		if (!a.empty()) {
			std::cout << a[0];
			for (size_t i = 1; i < a.size(); i++) {
				std::cout << ", " << a[i];
			}
		}
		
		std::cout << std::endl;
	}
};

// We do not want to use std::less as it has to pass function
// With below class no function has to be passed
template <typename T>
class testless {
public:
	static bool compare(const T& lhs, const T& rhs) { return lhs < rhs; }
};

template <typename T>
class testgreater {
public:
	static bool compare(const T& lhs, const T& rhs) { return lhs > rhs; }
};

void SortAllTest(const int count, const int arraycount, const int arraysize);
