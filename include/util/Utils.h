/**
 * @file Utils.h
 * @brief 存储一些实用函数
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
 //C4996    ‘localtime‘: This function or variable may be unsafe. Consider using localtime_s instead. 
//1. 在项目设置的C / C++选项中，把检查64位移植性去掉。
//2. 方案a：使用_localtime_s, _localtime32_s, _localtime64_s这3个函数代替localtime
//	 方案b：去掉C4996警告，比如按照提示所说	#define _CRT_SECURE_NO_WARNINGS 1 或者直接 #pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * @brief 释放指针P并将p设为NULL
  *
  * @param p 需要释放的指针
  */
void safe_free(void* p);

/**
 * @brief 交换函数
 *
 * @param ptr1 变量指针 1
 * @param ptr2 变量指针 2
 * @param size 交换变量大小
 */
void swap(void* ptr1, void* ptr2, int size);
