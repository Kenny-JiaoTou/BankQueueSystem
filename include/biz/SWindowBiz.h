/**
 * @file SWindowBiz.h
 * @brief 服务窗口/柜台类及相关操作
 *
 */

#pragma once


#include "CustomerBiz.h"
#include "TradeStatisticsBiz.h"

/** 服务窗口结构 */
typedef struct {
	int no;					///< 窗口号
	TradeStatistics kpi;	///< 柜台kpi统计信息
	Customer* customer;		///< 当前正在服务的客户
}SWindow;

/**
 * @brief 创建一个 ArrayList* 类型的服务窗口列表
 *
 * @param count 窗口总数
 * @return ArrayList* 服务窗口的线性表
 */
ArrayList* create_swindows(int count);

/**
 * @brief 将客户分配到服务窗口
 *
 * @param swindow 服务窗口指针
 * @param customer 客户指针
 */
void swindow_assign_customer(SWindow* swindow, Customer* customer);

/**
 * @brief 展示所有柜台当前办理业务人员信息
 *
 */
void swindow_show_customers();

/**
 * @brief 客户离开服务窗口（结束服务）
 *
 * @param swindow 窗口指针
 * @param customer 客户指针
 */
void swindow_leave_customer(SWindow* swindow, Customer* customer);