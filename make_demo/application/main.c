#include <stdio.h>
#include <stdarg.h>
#include "common.h"

void va_test(int count, ...) {
    va_list args;
    va_start(args, count);
	printf("\nva test count = [%d]\nva_param:\n", count);
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        printf("%d ", value);			//deal with code
    }
    printf("\n");
    va_end(args);
}

void testListNode() {
    int nums[] = {2, 3, 5, 6, 7};
    int size = sizeof(nums) / sizeof(int);
    ListNode *head = arrToLinkedList(nums, size);
    printLinkedList(head);
}

void testTreeNode() {
    int nums[] = {1, 2, 3, INT_MAX, 5, 6, INT_MAX};
    int size = sizeof(nums) / sizeof(int);
    TreeNode *root = arrayToTree(nums, size);

    // print tree
    printTree(root);

    // tree to arr
    int *arr = treeToArray(root, &size);
    printArray(arr, size);
}

int main(int argc, char *argv[]) 
{
    printf("==testListNode==\n");
    testListNode();
    printf("==testTreeNode==\n");
    testTreeNode();

    int nums[] = {4, 1, 3, 1, 5, 2};
    insertionSort(nums, 6);
    printf("插入排序完成后 nums = ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    va_test(5, 4, 1, 3, 9, 13);

    return 0;
}


