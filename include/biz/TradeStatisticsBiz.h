/**
 * @file TradeStatisticsBiz.h
 * @brief ������ز���
 *
 */

#pragma once

#include <stdlib.h>

/** ����ͳ����Ϣ */
typedef struct {
	int total_receptions;				//�Ӵ�����
	int total_time;						//�Ӵ��ͻ���ʱ
	double flowing_water;				//����ˮ
	double total_deposits;				//�ܴ����
}TradeStatistics;

/**
 * @brief ��������ͳ�ƶ���
 *
 * @return TradeStatistics ����ͳ��
 */
void ts_create(TradeStatistics* tradeStatistics);

/**
 * @brief չʾ����ͳ��
 *
 * @param ts ����ͳ����ָ��
 */
void ts_show_info(TradeStatistics* ts);

/**
 * @brief ����ʱ���չʾʱ��
 *
 * @param seconds ʱ���
 */
void ts_show_time(int seconds);

