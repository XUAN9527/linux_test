/**
 * File: vector.h
 * Created Time: 2023-07-13
 * Author: Zuoxun (845242523@qq.com)、Gonglja (glj0@outlook.com)
 */

#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* 定义向量类型 */
typedef struct vector {
    int size;     // 当前向量的大小
    int capacity; // 当前向量的容量
    int depth;    // 当前向量的深度
    void **data;  // 指向数据的指针数组
} vector;

/* 构造向量 */
vector *newVector(void);

/* 构造向量，指定大小、元素默认值 */
vector *_newVector(int size, void *elem, int elemSize);

/* 析构向量 */
void delVector(vector *v);

/*  添加元素（拷贝方式）到向量尾部 */
void vectorPushback(vector *v, void *elem, int elemSize);

/* 从向量尾部弹出元素 */
void vectorPopback(vector *v);

/* 清空向量 */
void vectorClear(vector *v);

/* 获取向量的大小 */
int vectorSize(vector *v);

/* 获取向量的尾元素 */
void *vectorBack(vector *v);

/* 获取向量的头元素 */
void *vectorFront(vector *v);

/* 获取向量下标 pos 的元素 */
void *vectorAt(vector *v, int pos);

/* 设置向量下标 pos 的元素 */
void vectorSet(vector *v, int pos, void *elem, int elemSize);

/* 向量扩容 */
void vectorExpand(vector *v);

/* 向量缩容 */
void vectorShrink(vector *v);

/* 在向量下标 pos 处插入元素 */
void vectorInsert(vector *v, int pos, void *elem, int elemSize);

/* 删除向量下标 pos 处的元素 */
void vectorErase(vector *v, int pos);

/* 向量交换元素 */
void vectorSwap(vector *v, int i, int j);

/* 向量是否为空 */
bool vectorEmpty(vector *v);

/* 向量是否已满 */
bool vectorFull(vector *v);

/* 向量是否相等 */
bool vectorEqual(vector *v1, vector *v2);

/* 对向量内部进行排序 */
void vectorSort(vector *v, int (*cmp)(const void *, const void *));

/* 打印函数， 需传递一个打印变量的函数进来 */
/* 当前仅支持打印深度为 1 的 vector */
void printVector(vector *v, void (*printFunc)(vector *v, void *p));

/* 当前仅支持打印深度为 2 的 vector */
void printVectorMatrix(vector *vv, void (*printFunc)(vector *v, void *p));

#ifdef __cplusplus
}
#endif

#endif // VECTOR_H
