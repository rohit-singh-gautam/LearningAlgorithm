cmake_minimum_required(VERSION 3.16)

project(SortingAlgorithm)

add_executable(SortingAlgorithm 
    BubbleSort.cpp
    CustomQuickSort.cpp
    DisplayHelper.cpp
    HeapSort.cpp
    InsertionSort.cpp
    LibrarySort.cpp
    MergeSort.cpp
    QuickSort.cpp
    SelectionSort.cpp
    SortingAlgorithm.cpp
    TestHelper.cpp
)

set_property(TARGET SortingAlgorithm PROPERTY CXX_STANDARD 20)
