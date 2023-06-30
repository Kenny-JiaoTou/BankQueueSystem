/**
 * @file CustomerBiz.h
 * @brief 客户相关操作
 *
 */
#pragma once

#include "../include/dao/CustomerDAO.h"


/** 顾客签到 */
Customer* customer_sign_in(char* name);

/** 客户比较函数 */
int customer_compare(const void* lptr, const void* rptr);

/** 更新取号号码 */
void update_pick(Customer* customer);
