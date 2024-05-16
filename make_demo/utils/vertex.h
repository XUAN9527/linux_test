/**
 * File: vertex.h
 * Created Time: 2023-10-28
 * Author: krahets (krahets@163.com)
 */

#ifndef VERTEX_H
#define VERTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* 顶点结构体 */
typedef struct {
    int val;
} Vertex;

/* 构造函数，初始化一个新节点 */
Vertex *newVertex(int val);

/* 将值数组转换为顶点数组 */
Vertex **valsToVets(int *vals, int size);

/* 将顶点数组转换为值数组 */
int *vetsToVals(Vertex **vertices, int size);

#ifdef __cplusplus
}
#endif

#endif // VERTEX_H
