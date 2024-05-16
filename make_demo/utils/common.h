/**
 * File: common.h
 * Created Time: 2022-12-20
 * Author: MolDuM (moldum@163.com)、Reanon (793584285@qq.com)
 */

#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "list_node.h"
#include "print_util.h"
#include "tree_node.h"
#include "vertex.h"

// hash table lib
#include "uthash.h"
#include "vector.h"

void bubbleSort(int nums[], int size);
void bubbleSortWithFlag(int nums[], int size);

void bucketSort(float nums[], int n);

void countingSortNaive(int nums[], int size);
void countingSort(int nums[], int size);

void heapSort(int nums[], int n);

void insertionSort(int nums[], int size);

void mergeSort(int *nums, int left, int right);

void quickSort(int nums[], int left, int right);
void quickSortMedian(int nums[], int left, int right);
void quickSortTailCall(int nums[], int left, int right);

void radixSort(int nums[], int size);

void selectionSort(int nums[], int n);


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif // COMMON_H
