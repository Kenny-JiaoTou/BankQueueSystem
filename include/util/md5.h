/**
 * @file md5.h
 * @brief md5加密工具类
 *
 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/** 结构定义 */
typedef struct
{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
{ \
    a += F(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define GG(a,b,c,d,x,s,ac) \
{ \
    a += G(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define HH(a,b,c,d,x,s,ac) \
{ \
    a += H(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define II(a,b,c,d,x,s,ac) \
{ \
    a += I(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
/** 初始化MD5结构体, context-> 要初始化的md5结构体 */
void MD5Init(MD5_CTX* context);

/** 将要加密的信息传递给初始化过的md5结构体 input:需要加密的信息; inputLen指定长度 */
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);

/** 存储加密结果 digets:加密结果 */
void MD5Final(MD5_CTX* context, unsigned char digest[16]);

void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len);

/**
 * @brief 计算指定文件的md5
 *
 * @param f     文件名/文件路径
 * @param dest  计算出的md5字符串
 * @return 文件长度(字节)
 */
int CalcMD5(char* fileName, char* dest);

/** 获取指定字符串的MD5 */
char* GetMD5(char* str);
