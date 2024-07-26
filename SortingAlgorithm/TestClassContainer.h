#pragma once

#include "TestClass.h"
#include "BubbleSort.h"
#include "CustomQuickSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "LibrarySort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include <random>
#include <unordered_set>

template<>
struct std::hash<std::pair<std::string_view, size_t>> {
    constexpr size_t operator()(const std::pair<std::string_view, size_t> &pr) const noexcept {
        const auto &[name, property] = pr;
        const size_t h1 = std::hash<std::string_view>{}(name);
        const size_t h2 = std::hash<size_t>{}(property);
        return h1 ^ (h2 << 1);
    }
};

class TestClassContainer {
    static constexpr const std::string_view SortAlgorithmList[] {
        QuickSortTester::name,
        LibrarySortTester::name,
        MergeSortTester::name,
        SelectionSortTester::name,
        BubbleSortTester::name,
        InsertionSortTester::name
    };

    template <bool clone_arrays>
    static TestClassBase *CreateSortAlgorithm(const std::string_view &name, size_t properties, std::vector<std::vector<int>> &arrays) {
        vector<vector<int>> *arraysptr { nullptr };
        if constexpr(clone_arrays)
            arraysptr = new vector<vector<int>>(arrays);
        else arraysptr = &arrays;

        if (name == QuickSortTester::name) {
            return new QuickSortTester(*arraysptr, properties);
        } else if (name == LibrarySortTester::name) {
            return new LibrarySortTester(*arraysptr, properties);
        } else if (name == MergeSortTester::name) {
            return new MergeSortTester(*arraysptr, properties);
        } else if (name == SelectionSortTester::name) {
            return new SelectionSortTester(*arraysptr, properties);
        } else if (name == BubbleSortTester::name) {
            return new BubbleSortTester(*arraysptr, properties);
        } else if (name == InsertionSortTester::name) {
            return new InsertionSortTester(*arraysptr, properties);
        } else throw std::invalid_argument("Unsupported Sorting Algorithm");
    }

    static const std::vector<size_t> &GetAllSortAlgorithmProperty(const std::string_view &name) {
        if (name == QuickSortTester::name) {
            return QuickSortTester::GetAllSortProperties();
        } else if (name == LibrarySortTester::name) {
            return LibrarySortTester::GetAllSortProperties();
        } else if (name == MergeSortTester::name) {
            return MergeSortTester::GetAllSortProperties();
        } else if (name == SelectionSortTester::name) {
            return SelectionSortTester::GetAllSortProperties();
        } else if (name == BubbleSortTester::name) {
            return BubbleSortTester::GetAllSortProperties();
        } else if (name == InsertionSortTester::name) {
            return InsertionSortTester::GetAllSortProperties();
        } else throw std::invalid_argument("Unsupported Sorting Algorithm");
    }

    template <typename IntType = int>
    static void SortAscending(std::vector<std::vector<IntType>> &arrays) {
        for(auto &array: arrays) {
            std::ranges::sort(array);
        }
    }

    template <typename IntType = int>
    static void SortDescending(std::vector<std::vector<IntType>> &arrays) {
        for(auto &array: arrays) {
            std::ranges::sort(array, std::greater<IntType> { });
        }
    }

public:

    template <typename IntType = int>
    static void TestAllSortingAlgorigthm(const SortOrder order, size_t NumberOfArray, size_t ArraySize, size_t NumberOfArrayToSortAtOnce, const std::unordered_set<std::pair<std::string_view, size_t>> &skiptestlist) {
        std::vector<TestClassBase *> SortTestList { };
        auto arrays = TestClass::GenerateManyArray<IntType>(NumberOfArray, ArraySize);
        if (order == SortOrder::Ascending) {
            std::cout << "Testing sort with ascending array...\n";
            SortAscending<IntType>(arrays);
        } else if (order == SortOrder::Descending) {
            SortDescending<IntType>(arrays);
            std::cout << "Testing sort with descending array...\n";
        } else {
            std::cout << "Testing sort with randomized array...\n";
        }
        
        for(auto &algoname: SortAlgorithmList) {
            auto allproperties = GetAllSortAlgorithmProperty(algoname);

            for(auto property: allproperties) {
                std::pair<std::string_view, size_t> algoprop { algoname, property };

                if (skiptestlist.find(algoprop) == std::end(skiptestlist)) {
                    auto testobject = CreateSortAlgorithm<true>(algoname, property, arrays);
                    SortTestList.push_back(testobject);
                }
            }
        }

        const auto DisplayPeriod = std::chrono::milliseconds(1000);
        std::cout << "Sorting ";
        int current = 0;
        auto begin_time = std::chrono::high_resolution_clock::now();
        auto prev_time = begin_time;
        while (current + NumberOfArrayToSortAtOnce <= arrays.size()) {
            auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(std::begin(SortTestList), std::end(SortTestList), std::default_random_engine(seed));
            
            for (auto &test : SortTestList) {
                test->Sort(NumberOfArrayToSortAtOnce);
            }
            current += NumberOfArrayToSortAtOnce;
            auto current_time = std::chrono::high_resolution_clock::now();
            if (current_time - prev_time > DisplayPeriod) {
                cout << '.' << std::flush;
                prev_time = current_time;
            }
        }

        std::cout << std::endl;

        std::sort(std::begin(SortTestList), std::end(SortTestList),
                    [](const auto lhs, const auto rhs) 
                        { return lhs->getElapsedTime() < rhs->getElapsedTime(); } );

        for (auto &test : SortTestList) {
            test->FindSorted();
            test->DisplayResult();
        }
        std::cout << "Testing Completed: " << std::endl;
    }

    template <typename IntType = int>
    static void TestAllSortingAlgorigthmAllOrders(size_t NumberOfArray, size_t ArraySize, size_t NumberOfArrayToSortAtOnce, const std::unordered_set<std::pair<std::string_view, size_t>> &skiptestlist) {
        std::cout << "------------------------------------------------------------------------------------------------\nAll Test started\n";
        TestAllSortingAlgorigthm<IntType>(SortOrder::Ascending, NumberOfArray, ArraySize, NumberOfArrayToSortAtOnce, skiptestlist);
        TestAllSortingAlgorigthm<IntType>(SortOrder::Descending, NumberOfArray, ArraySize, NumberOfArrayToSortAtOnce, skiptestlist);
        TestAllSortingAlgorigthm<IntType>(SortOrder::Random, NumberOfArray, ArraySize, NumberOfArrayToSortAtOnce, skiptestlist);
        std::cout << "------------------------------------------------------------------------------------------------\nThe End\n";
    }

};