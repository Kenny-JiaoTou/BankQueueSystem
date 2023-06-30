/**
 * @file Date.h
 * 参考文档：https://www.runoob.com/cprogramming/c-standard-library-time-h.html
 * @brief 日期结构及相关操作
 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TM_YEAR_BASE 1900
 /*
  * We do not implement alternate representations. However, we always
  * check whether a given modifier is allowed for a certain conversion.
  */
#define ALT_E     0x01
#define ALT_O     0x02
#define LEGAL_ALT(x)    { if (alt_format & ~(x)) return (0); }

typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}Date;

/**
 * @brief 获取当前时间
 *
 * @return date 日期类
 */
Date get_cur_date();

char* get_cur_date_str();

/**
 * @brief 在文件 f 中显示日期 d
 *
 * @param f 输出文件
 * @param d 输出日期
 */
void show_date(FILE* file, Date date);

/**
 * @brief 将字符串格式的时间转换为整数类型<br/>
 * 时间格式："%Y-%m-%d %H:%M:%S
 */
time_t str_to_time(char* str_time);

/**
 * @brief 返回两个字符串时间之差 <br/>
 * 时间格式："%Y-%m-%d %H:%M:%S
 */
long get_date_diff(char* str_time1, char* str_time2);



/************************************************************************/
/* Windows平台无strptime函数，所以，想要使用strptime函数，需要如下的代码                                                                     */
/************************************************************************/

static  int conv_num(const char**, int*, int, int);

static const char* day[7] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
  "Friday", "Saturday"
};
static const char* abday[7] = {
  "Sun","Mon","Tue","Wed","Thu","Fri","Sat"
};
static const char* mon[12] = {
  "January", "February", "March", "April", "May", "June", "July",
  "August", "September", "October", "November", "December"
};
static const char* abmon[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char* am_pm[2] = {
  "AM", "PM"
};

char* strptime(const char* buf, const char* fmt, struct tm* tm);

