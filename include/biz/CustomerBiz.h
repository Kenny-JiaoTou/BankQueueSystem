/**
 * @file CustomerBiz.h
 * @brief �ͻ���ز���
 *
 */
#pragma once

#include "../include/dao/CustomerDAO.h"


/** �˿�ǩ�� */
Customer* customer_sign_in(char* name);

/** �ͻ��ȽϺ��� */
int customer_compare(const void* lptr, const void* rptr);

/** ����ȡ�ź��� */
void update_pick(Customer* customer);
