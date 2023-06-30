#pragma once
/*****************************************************************//**
 * \file   ProiorityQueue.h
 * \brief  优先队列
 * \author RayDataWorker001
 * \date   June 2023
 *********************************************************************/
#include <stdlib.h>
#include "Utils.h"

#define PQ_INIT_CAPACITY  10	//优先队列的默认容量

//堆/优先队列结构 - 堆是使用数组实现的二叉树，它的逻辑结构是二叉树，存储结构是数组，所以没有左右孩子
typedef struct{					
	unsigned int capacity;		//容量
	unsigned int size;			//元素个数
	void** elements;			//元素数组
	int (*CompareFunction)(const void*, const void*);	//比较函数的函数指针
}ProirityQueue;

/** 创建优先队列 */
ProirityQueue* pq_create(int (*CompareFunction)(const void*, const void*));

/** 优先队列内部数组扩容 */
void pq_resize(ProirityQueue* proirityQueue);

/** 返回完全二叉树数组中 指定下标所表示的父亲结点的下标 */
int parent(int index);

/** 返回左孩子下标：index * 2 + 1 */
int leftChild(int index);

/** 返回右孩子下标：index * 2 + 2 */
int rightChild(int index);

/** 返回首元素 */
void* pq_top(ProirityQueue * queue);

/** 上浮指定下标的元素 */
void pq_sift_up(ProirityQueue* queue, int index);

/** 下浮指定下标的元素 */
void pq_sift_down(ProirityQueue* queue, int index);

/** 向堆中添加元素 */
void pq_push(ProirityQueue* queue, void* element);

/** 去除并返回堆中的最大元素，保证取出仍维持堆结构特性 */
void* pq_pop(ProirityQueue* queue);

/** 取出堆中最大元素，替换成指定的元素 */
void* pq_replace(ProirityQueue* queue, void* element);

/** 堆化数组 */
void pq_heapify(ProirityQueue* queue);

/** 释放内存 */
void pq_free(ProirityQueue* proirityQueue);

/** 清空数组 */
void pq_clear(ProirityQueue* prorityQueue);

