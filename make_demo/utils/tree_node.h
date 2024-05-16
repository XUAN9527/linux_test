/**
 * File: tree_node.h
 * Created Time: 2023-01-09
 * Author: Reanon (793584285@qq.com)
 */

#ifndef TREE_NODE_H
#define TREE_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

#define MAX_NODE_SIZE 5000

/* 二叉树节点结构体 */
typedef struct TreeNode {
    int val;                // 节点值
    int height;             // 节点高度
    struct TreeNode *left;  // 左子节点指针
    struct TreeNode *right; // 右子节点指针
} TreeNode;

/* 构造函数 */
TreeNode *newTreeNode(int val);

// 序列化编码规则请参考：
// https://www.hello-algo.com/chapter_tree/array_representation_of_tree/
// 二叉树的数组表示：
// [1, 2, 3, 4, None, 6, 7, 8, 9, None, None, 12, None, None, 15]
// 二叉树的链表表示：
//             /——— 15
//         /——— 7
//     /——— 3
//    |    \——— 6
//    |        \——— 12
// ——— 1
//     \——— 2
//        |    /——— 9
//         \——— 4
//             \——— 8

/* 将列表反序列化为二叉树：递归 */
TreeNode *arrayToTreeDFS(int *arr, int size, int i);

/* 将列表反序列化为二叉树 */
TreeNode *arrayToTree(int *arr, int size);

/* 将二叉树序列化为列表：递归 */
void treeToArrayDFS(TreeNode *root, int i, int *res, int *size);

/* 将二叉树序列化为列表 */
int *treeToArray(TreeNode *root, int *size);

/* 释放二叉树内存 */
void freeMemoryTree(TreeNode *root);

#ifdef __cplusplus
}
#endif

#endif // TREE_NODE_H
