/**
 * @file TradeDAO.h
 * @brief 交易信息数据访问操作
 *
 */
#pragma once
#include "../include/util/Common.h"

/** 交易信息结构 */
typedef struct {
	int id;
	int card_id;
	int to_card_id;
	int trade_type;
	char trade_time[20];
	double pre_money;
	double curr_money;
}Trade;

/**
 * @brief 插入指定的交易信息到数据库
 *
 * @param trade 交易信息
 */
int insert_trade(Trade* trade);

/**
 * @brief 返回指定银行卡的交易记录
 *
 * @param card_id 卡id
 */
void query_trade_by_card(ArrayList * trade_list, int card_id);