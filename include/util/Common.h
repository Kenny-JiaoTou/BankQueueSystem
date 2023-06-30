/*****************************************************************//**
 * \file   Common.h
 * \brief  通用常量及方法
 * 
 * \author RayDataWorker001
 * \date   June 2023
 *********************************************************************/
#pragma once

#pragma comment(lib, "libmysql.lib")
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "../include/util/Date.h"
#include "../include/util/ArrayList.h"
#include "../include/util/ProiorityQueue.h"
#include "../include/biz/TradeStatisticsBiz.h"

#define VIP_LEVEL 10							///< vip等级
#define	COUNT_WINDOWS 3							///< 服务窗口/柜台数量

extern FILE* out_target;						///< 输出目标，可以是日志文件，也可以是控制台

extern ArrayList* swindow_list;					///< 当前银行拥有的窗口集合
extern ProirityQueue* waiting_queue;			///< 当前等待的用户队列
extern TradeStatistics global_trade_statistics;	///< 全局交易统计信息
extern int cur_noraml_num;						///< 总叫号
extern int cur_pick_num[VIP_LEVEL + 1];			///< 当前各VIP级别的取号号码
extern int cur_call_num[VIP_LEVEL + 1];			///< 当前各VIP级别的叫号号码



/** 初始化MySQL */
int initial_mysql();

/**
 * 执行预处理
 * @param sql_len strlen(sql)
 * @param mysql_bind 绑定插入的参数
 * @return 影响的行数
 */
int execute_update_stmt(char* sql, int sql_len, MYSQL_BIND* mysql_bind);

MYSQL_RES* execute_query(char* sql);

void transaction_start();

void transaction_commit();

void transaction_rollback();

/** 释放MySQL资源 */
void release_mysql();
