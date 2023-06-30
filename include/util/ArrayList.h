#pragma once
/**
 * @file array_list.h
 * @brief array_list 类及相关操作
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

#define INIT_CAPACITY 10		//线性表数组的初始容量

typedef struct {
	void** elements;			//元素数组
	int size;					//实际元素个数(元素数组大小)
	int capacity;				//元素数组最大容量
}ArrayList;

/**
 * @brief 创建一个线性表
 *
 * @return array_list* 线性表指针
 */
ArrayList* arraylist_create();

/**
 * @brief 初始化一个线性表
 *
 * @param array_list* 线性表指针
 */
void arraylist_init(ArrayList* arraylist);

/**
 * @brief 获得线性表中相应位置元素的指针（从0开始）
 *
 * @param al 线性表指针
 * @param idx 元素位置
 * @return void* 元素指针
 */
void* arraylist_at(ArrayList* arrayList, int index);

/**
 * @brief 将元素插入线性表末尾
 *
 * @param al 线性表指针
 * @param val 元素指针
 */
void arraylist_push(ArrayList* arrayList, void* value);

/**
 * @brief  释放线性表分配空间
 * @param al 线性表指针
 */
void arraylist_free(ArrayList* arrayList);

/**
 * @brief 自动增长线性表
 *
 * @param al 线性表指针
 */
void arraylist_resize(ArrayList* arrayList);

/**
 * @brief 删除并返回线性表相应位置元素（从0开始）
 *
 * @param al 线性表指针
 * @param idx 相应位置
 * @return void* 元素指针
 */
void* arraylist_pop(ArrayList* arrayList, int index);

/**
 * @brief 将线性表清空
 *
 * @param al 线性表指针
 */
void arraylist_clean(ArrayList* arrayList);