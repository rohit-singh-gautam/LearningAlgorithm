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

const std::unordered_map<size_t, SortingFunction> BubbleSortTester::sortmaps {
	{ TestProperties::GetPropertyString(N_Square, Iterative), BubbleSortTester::BubbleSortAlgorithm }
};

const std::vector<size_t> BubbleSortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};

const std::unordered_map<size_t, SortingFunction> HeapSortTester::sortmaps {
	{TestProperties::GetPropertyString(N_LogN, Iterative), HeapSortTester::HeapSortAlgorithm}
};

const std::vector<size_t> HeapSortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};

const std::unordered_map<size_t, SortingFunction> InsertionSortTester::sortmaps {
	{TestProperties::GetPropertyString(N_Square, Iterative), InsertionSort},
	{TestProperties::GetPropertyString(N_Square, Iterative, Pointer), InsertionSortPointer},
};

const std::vector<size_t> InsertionSortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};

const std::unordered_map<size_t, SortingFunction> LibrarySortTester::sortmaps {
	{0, LibrarySortTester::LibrarySortAlgorithm},
};

const std::vector<size_t> LibrarySortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};

const std::unordered_map<size_t, SortingFunction> MergeSortTester::sortmaps {
	{TestProperties::GetPropertyString(N_LogN, Recursive), MergeSortTester::MergeSortAlgorithm}
};

const std::vector<size_t> MergeSortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};

const std::unordered_map<size_t, SortingFunction> QuickSortTester::sortmaps {
	{TestProperties::GetPropertyString(N_LogN, Iterative), QuickSortIterative},
	{TestProperties::GetPropertyString(N_LogN, Iterative, OptimizeLeft), QuickSortIterativeLeftOptimized},
	{TestProperties::GetPropertyString(N_LogN, Iterative, Randomize), QuickSortIterativeRand},
	{TestProperties::GetPropertyString(N_LogN, Iterative, Randomize, OptimizeLeft), QuickSortIterativeRandLeftOptimized},
	{TestProperties::GetPropertyString(N_LogN, TailRecursive), QuickSortTailRecursiveHelper},
	{TestProperties::GetPropertyString(N_LogN, TailRecursive, OptimizeLeft), QuickSortTailRecursiveLeftOptimizedHelper},
	{TestProperties::GetPropertyString(N_LogN, Recursive, OptimizeLeft), QuickSortRecursiveHelperLeftOptimized},
	{TestProperties::GetPropertyString(N_LogN, Recursive, Randomize), QuickSortRecursiveHelperRand},
	{TestProperties::GetPropertyString(N_LogN, Recursive, Randomize, OptimizeLeft), QuickSortRecursiveHelperRandLeftOptimized},
	{TestProperties::GetPropertyString(N_LogN, OptimizedCustom, Recursive, OptimizeLeft), CustomQuickSortRecursiveHelper},
	{TestProperties::GetPropertyString(N_LogN, OptimizedCustom, TailRecursive, OptimizeLeft), CustomQuickSortRecursiveTailHelper},
	{TestProperties::GetPropertyString(N_LogN, N_Square, OptimizedCustom, TailRecursive, OptimizeLeft), CustomQuickSortRecursiveTailInsertionHelper},
	{TestProperties::GetPropertyString(N_LogN, N_Square, OptimizedCustom, TailRecursive, OptimizeLeft, HeapEnabled), CustomQuickSortRecursiveTailInsertionHeapHelper}
};

const std::vector<size_t> QuickSortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};

const std::unordered_map<size_t, SortingFunction> SelectionSortTester::sortmaps {
	{TestProperties::GetPropertyString(N_Square, Iterative), SelectionSort}
};

const std::vector<size_t> SelectionSortTester::AllSortProperties { 
	sortmaps | std::views::transform([](const auto &entry) { return entry.first; }) | std::ranges::to<std::vector>()
};
