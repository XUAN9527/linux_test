import threading
import time
import numpy as np
import sys
import os
sys.path.append(os.path.expanduser('~/linux/demos/py_demo/chapter_sorting'))
import insertion_sort
import quick_sort

nums1 = []
nums2 = []

times1 = 0
times2 = 0

mutex = threading.Lock()

def sort_with_inserting(*args, **kwargs):
	global nums1, times1
	while True:
		with mutex:
			times1 += 1
			if times1 > 10:
				break
			print(f"args = [{0}], [{1}]" .format(args[0], args[1]))
			print("key=[breo], value=[%d]; key=[edison], value=[%s]" % (kwargs['breo'], kwargs['edison']))
			print("sort_with_inserting : times1 = [{0}]" .format(times1))
			nums1 = np.random.randint(0, 1000, size=10)
			print(f"生成随机数组 nums1 = {nums1}")
			insertion_sort.insertion_sort(nums1)
			print("插入排序完成 nums1 =", nums1, "\n")
		time.sleep(2)
def sort_with_quick():
	global nums2, times2
	while True:
		with mutex:
			times2 += 1
			if times2 > 10:
				break
			print("sort_with_quick : times2 = [%d]" %(times2))
			nums2 = np.random.randint(0, 1000, size=10)
			print("生成随机数组 nums2 = ", nums2)
			quick_sort.QuickSort().quick_sort(nums2, 0, len(nums2) - 1)
			print("快速排序完成 nums2 =", nums2, "\n")
		time.sleep(2)

if __name__ == "__main__":

	kv_arg = {'breo': 27 ,'edison': 'true'}
	arg1 = 55
	arg2 = 100

	thread1 = threading.Thread(target=sort_with_inserting, name="sort_with_inserting", args=(arg1, arg2), kwargs=kv_arg)
	thread2 = threading.Thread(target=sort_with_quick, name="sort_with_quick")

	thread1.start()
	print("thread1 is started!")

	thread2.start()
	print("thread2 is started!")

    # 等待两个线程都完成
	thread1.join()
	print("thread1 is joined!")

	thread2.join()
	print("thread2 is joined!")
	

