/**
 * @file SWindowBiz.h
 * @brief ���񴰿�/��̨�༰��ز���
 *
 */

#pragma once


#include "CustomerBiz.h"
#include "TradeStatisticsBiz.h"

/** ���񴰿ڽṹ */
typedef struct {
	int no;					///< ���ں�
	TradeStatistics kpi;	///< ��̨kpiͳ����Ϣ
	Customer* customer;		///< ��ǰ���ڷ���Ŀͻ�
}SWindow;

/**
 * @brief ����һ�� ArrayList* ���͵ķ��񴰿��б�
 *
 * @param count ��������
 * @return ArrayList* ���񴰿ڵ����Ա�
 */
ArrayList* create_swindows(int count);

/**
 * @brief ���ͻ����䵽���񴰿�
 *
 * @param swindow ���񴰿�ָ��
 * @param customer �ͻ�ָ��
 */
void swindow_assign_customer(SWindow* swindow, Customer* customer);

/**
 * @brief չʾ���й�̨��ǰ����ҵ����Ա��Ϣ
 *
 */
void swindow_show_customers();

/**
 * @brief �ͻ��뿪���񴰿ڣ���������
 *
 * @param swindow ����ָ��
 * @param customer �ͻ�ָ��
 */
void swindow_leave_customer(SWindow* swindow, Customer* customer);