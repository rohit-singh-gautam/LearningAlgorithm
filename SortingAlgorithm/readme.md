# Sorting Analysis Applicaiton

This application evaluates various sorting algorithms across multiple datasets. Accurate analysis requires compilation in release mode. Measures are taken to ensure exclusive thread access. Additionally, execution randomization prevents one sorting algorithm from affecting another. Moreover, identical data copies are supplied to all algorithms to prevent caching from previous sorting operations.

Array that is algorithm tested with:
1. Random array
1. Sorted array
1. Reverse sorted array.


Below algoritm are tested:
1. Quick + Insertion Sort
1. Quick sort multiple variations
1. Heap Sort
1. Insertion Sort
1. MergeSort
1. BubbleSort
1. std::sort

Attempt is made to optimize these algorithms as much as possible.

## Library sort algoritms
Library sorting algoritm implements combination of three sorting algorithms:
1. Insertion sort
1. Quick sort
3. Merge sort

Insertion sort is used if array to be sorted is less than 16 and in some case 32. Even if during intermediate steps data is smaller it will use insertion sort.

Quick sort in combination of Insertion sort is used where stability is not required. Stable sort is one where original order is maintained when its sorting key is equal. For primitives Quick sort is used.

Merge sort in combination of Insertion sort is used where stability is important. All structures and classes are sorted by default using merge sort.

Quick sort performas badly in case of sorted array. To address this median of first, last and middle is used as pivot for partitioning in Quick sort. Similar behavbiour is in Visual Studio and Glibc, variation is in how two poiter is used. Visual Studio use two pointer both start from begining and Glibc use one start from begining and other from end. Start both pointer from begining gives substantial benefits in older processor on Intel Ultra Core 9 much difference was not observed though start both pointer from begining has some benefits.

## My Quick sort
My best sorting algoritm is similar to library sort that has combination of insertion and quick sort. Only difference lies in partitioning algorithms. It attempts to detect sorted part of array and partition accordingly. Also, it attempt to swap if start element is greater than last element (in case of ascending sorting). This optimizaiton is marked as OptimizedCustom.

There are multiple different sorting algorithms implemented one where two pointer start from left marked as OptimizeLeft. 

## Result
```
All Test started
Testing sort with ascending array...
Sorting .................................................................................................
Quick Sort { O(log(n)) Recursive OptimizedCustom OptimizeLeft }: 0.0291882 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion OptimizedCustom OptimizeLeft }: 0.0296493 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(n^2) O(log(n)) TailRecursion OptimizedCustom OptimizeLeft }: 0.0313476 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Insertion Sort { O(n^2) Iterative Pointer }: 0.0375091 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Insertion Sort { O(n^2) Iterative }: 0.0375552 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(n^2) O(log(n)) TailRecursion HeapEnabled OptimizedCustom OptimizeLeft }: 0.0467488 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Merge Sort { O(log(n)) Recursive }: 0.165965 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Library Sort { }: 0.177654 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative Randomize }: 0.907042 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive Randomize }: 0.94009 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative OptimizeLeft Randomize }: 2.35346 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizeLeft Randomize }: 2.36105 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative }: 18.0976 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion }: 18.1738 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion OptimizeLeft }: 18.2885 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizeLeft }: 18.3162 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative OptimizeLeft }: 18.4506 s; Initial Sorted: 10000(asc); Final Sorted: 10000(asc)
Testing Completed: 
Testing sort with descending array...
Sorting ......................................................................................................................
Quick Sort { O(n^2) O(log(n)) TailRecursion OptimizedCustom OptimizeLeft }: 0.0367453 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion OptimizedCustom OptimizeLeft }: 0.0444333 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizedCustom OptimizeLeft }: 0.0444461 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Merge Sort { O(log(n)) Recursive }: 0.229873 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Library Sort { }: 0.236356 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(n^2) O(log(n)) TailRecursion HeapEnabled OptimizedCustom OptimizeLeft }: 0.872049 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive Randomize }: 0.987078 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative Randomize }: 1.04091 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizeLeft Randomize }: 1.22651 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative OptimizeLeft Randomize }: 1.27755 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Insertion Sort { O(n^2) Iterative Pointer }: 1.96827 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(unsorted)
Insertion Sort { O(n^2) Iterative }: 2.00572 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative }: 18.7477 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion }: 18.8932 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizeLeft }: 23.6323 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion OptimizeLeft }: 23.6964 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative OptimizeLeft }: 23.8996 s; Initial Sorted: 10000(desc:10000); Final Sorted: 10000(asc)
Testing Completed: 
Testing sort with randomized array...
Sorting ........................................
Quick Sort { O(n^2) O(log(n)) TailRecursion OptimizedCustom OptimizeLeft }: 1.26337 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Library Sort { }: 1.2662 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Merge Sort { O(log(n)) Recursive }: 1.27197 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizeLeft }: 1.41527 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(n^2) O(log(n)) TailRecursion HeapEnabled OptimizedCustom OptimizeLeft }: 1.42431 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion OptimizeLeft }: 1.4505 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative OptimizeLeft }: 1.49339 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizedCustom OptimizeLeft }: 1.63622 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion OptimizedCustom OptimizeLeft }: 1.65419 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) TailRecursion }: 1.72091 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative }: 1.79051 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative OptimizeLeft Randomize }: 1.84096 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive OptimizeLeft Randomize }: 1.87994 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Iterative Randomize }: 2.12277 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Quick Sort { O(log(n)) Recursive Randomize }: 2.16628 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Insertion Sort { O(n^2) Iterative }: 8.07644 s; Initial Sorted: 10000(unsorted); Final Sorted: 10000(asc)
Testing Completed: 
------------------------------------------------------------------------------------------------
The End
```