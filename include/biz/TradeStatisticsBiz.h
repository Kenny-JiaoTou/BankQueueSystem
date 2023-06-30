/**
 * @file TradeStatisticsBiz.h
 * @brief 交易相关操作
 *
 */

#pragma once

#include <stdlib.h>

/** 交易统计信息 */
typedef struct {
	int total_receptions;				//接待总数
	int total_time;						//接待客户耗时
	double flowing_water;				//总流水
	double total_deposits;				//总存款量
}TradeStatistics;

/**
 * @brief 创建交易统计对象
 *
 * @return TradeStatistics 交易统计
 */
void ts_create(TradeStatistics* tradeStatistics);

/**
 * @brief 展示交易统计
 *
 * @param ts 交易统计类指针
 */
void ts_show_info(TradeStatistics* ts);

/**
 * @brief 根据时间戳展示时间
 *
 * @param seconds 时间戳
 */
void ts_show_time(int seconds);

