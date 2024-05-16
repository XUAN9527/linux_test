/**
 * File: print_util.h
 * Created Time: 2022-12-21
 * Author: MolDum (moldum@163.com), Reanon (793584285@qq.com)
 */

#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_node.h"
#include "tree_node.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 打印数组 */
void printArray(int arr[], int size);

/* 打印数组 */
void printArrayFloat(float arr[], int size);

/* 打印链表 */
void printLinkedList(ListNode *node);

typedef struct Trunk {
    struct Trunk *prev;
    char *str;
} Trunk;

Trunk *newTrunk(Trunk *prev, char *str);

void showTrunks(Trunk *trunk);

/**
 * 打印二叉树
 * This tree printer is borrowed from TECHIE DELIGHT
 * https://www.techiedelight.com/c-program-print-binary-tree/
 */
void printTreeHelper(TreeNode *node, Trunk *prev, bool isRight);

/* 打印二叉树 */
void printTree(TreeNode *root);

/* 打印堆 */
void printHeap(int arr[], int size);

#ifdef __cplusplus
}
#endif

#endif // PRINT_UTIL_H
