#include <stdio.h>
#include "../include/sort.h"

/* Driver Code */
int main() {
    int nums1[] = {4, 1, 3, 1, 5, 2};
    insertionSort(nums1, 6);
    printf("插入排序完成后 nums1 = ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");

	int nums2[] = {4, 1, 3, 1, 5, 2};
    int n = sizeof(nums2) / sizeof(nums2[0]);

    selectionSort(nums2, n);

    printf("选择排序完成后 nums2 = ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums2[i]);
    }
    printf("\n");

    return 0;
}
