import threading
import time
import numpy as np
from chapter_sorting.insertion_sort import insertion_sort
from chapter_sorting.quick_sort import QuickSort

nums1 = []
nums2 = []

times1 = 0
times2 = 0

def sort_with_inserting():
	global nums1, times1, times2
	while True:
		times1 += 1
		print(f"sort_with_inserting : times1 = {0}, times2 = {1}" .format(times1, times2))
		nums1 = np.random.randint(0, 1000, size=10)
		print(f"生成随机数组 nums1 = {nums1}")
		insertion_sort(nums1)
		print("插入排序完成 nums1 =", nums1, "\n")
		time.sleep(2)
def sort_with_quick():
	global nums2, times1, times2
	while True:
		times2 += 1
		print("sort_with_quick : times1 = [%d], times2 = [%d]" %(times1, times2))
		nums2 = np.random.randint(0, 1000, size=10)
		print("生成随机数组 nums2 = ", nums2)
		QuickSort().quick_sort(nums2, 0, len(nums2) - 1)
		print("快速排序完成 nums2 =", nums2, "\n")
		time.sleep(2)

if __name__ == "__main__":

	thread1 = threading.Thread(target=sort_with_inserting)
	thread2 = threading.Thread(target=sort_with_quick)

	thread1.start()
	print("thread1 is started!")

	thread2.start()
	print("thread2 is started!")

    # 等待两个线程都完成
	thread1.join()
	print("thread1 is joined!")

	thread2.join()
	print("thread2 is joined!")
	

