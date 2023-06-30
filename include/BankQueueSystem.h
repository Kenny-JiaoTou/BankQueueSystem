/**
 * @file BankQueueSystem.h
 * @brief 系统功能
 *
 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include "../include/view/MenuView.h"
#include "../include/biz/SWindowBiz.h"
#include "../include/biz/TradeBiz.h"
#include "../include/biz/TradeStatisticsBiz.h"
#include "../include/biz/CustomerBiz.h"
#include "../include/biz/AdminBiz.h"

/**
 * @brief 用来初始化系统数据
 *
 */
void init_system();

/**
 * @brief 启动银行排队系统
 *
 */
void start_system();

/**
 * @brief 进行取号
 *
 */
void pick_number();

/**
 * @brief 登录管理员账号
 *
 * @return int 0 登录失败
 *             1 登录成功
 */
int login_admin();

/**
 * @brief 查看所有交易记录
 *
 */
void check_all_trade();

/**
 * @brief 升级VIP
 *
 */
void update_VIP();

