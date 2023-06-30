/**
 * @file TradeBiz.h
 * @brief 实现交易业务
 * @date 2021-07-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "../include/view/MenuView.h"
#include "SWindowBiz.h"
#include "../include/dao/CardDAO.h"
#include "../include/dao/TradeDAO.h"

 /** 交易类型枚举 */
enum TradeType {
	DEPOSIT,			///< 存款
	WITHDRAW,			///< 取款
	TRANSFER,			///< 转账（转出）
	BETRANSFERRED		///< 转账（转入）
};

/**
 * @brief 交易主函数入口
 *
 */
void start_trade();

/**
 * @brief 展示客户卡的信息
 *
 * @param customer 客户指针
 * @return int 卡的数量
 */
int show_cards(Customer* customer);

/**
 * @brief 为指定的客户开卡
 *
 * @param cust_id 客户id
 */
void create_card(int cust_id);

/**
 * @brief 结束当前客户的服务
 *
 * @param swindow 窗口指针
 */
void end_trade(SWindow* swindow);

/**
 * @brief 呼叫下位客户
 *
 * @param swindow 窗口指针
 */
void call_next(SWindow* swindow);

/**
 * @brief 检查指定卡片的余额
 *
 * @param swindow 窗口指针
 */
void check_balance(int card_id);

/**
 * @brief 在指定的窗口向指定的卡片进行存款操作
 *
 * @param swindow 窗口指针
 * @param card_id 卡id
 */
void deposit_money(SWindow* swindow, int card_id);

/**
 * @brief 在指定的窗口向指定的卡片进行取款操作
 *
 * @param swindow 窗口指针
 * @param card_id 卡id
 */
void withdraw_money(SWindow* swindow, int card_id);

/**
 * @brief 在指定的窗口向指定的卡片进行转账操作
 *
 * @param swindow 窗口指针
 * @param card_id 卡id
 */
void transfer_money(SWindow* swindow, int card_id);

/**
 * @brief 查看指定卡的交易记录
 *
 * @param card_id 卡id
 */
void view_transactions(int card_id);