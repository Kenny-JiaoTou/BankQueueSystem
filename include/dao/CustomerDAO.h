/**
 * @file CustomerDAO.h
 * @brief 客户数据访问操作
 *
 */
#pragma once

#include <string.h>
#include "../include/util/Date.h"
#include "../include/util/Utils.h"
#include "../include/util/Common.h"

#define NAME_SIZE 20			///< 客户姓名长度
#define TIME_SIZE 20			///< 时间字符串长度

/** 客户结构 */
typedef struct {
	int id;						///< 客户id
	int pick_number_normal;		///< 普通号码
	int pick_number_vip;		///< vip号码
	int vip_level;				///< vip等级
	char name[NAME_SIZE];		///< 顾客姓名
	char begin_time[TIME_SIZE];	///< 起始时间
	char end_time[TIME_SIZE];	///< 结束时间
}Customer;

/** 将指定客户信息写入到数据库 */
int insert_customer(Customer* customer);

/** 更新指定的(以客户id为主键)客户信息 */
int update_customer(Customer* customer);

/** 返回指定登录名的客户信息 */
void query_customer(Customer* customer, char* login_name);
