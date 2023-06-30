/**
 * @file TradeDAO.h
 * @brief ������Ϣ���ݷ��ʲ���
 *
 */
#pragma once
#include "../include/util/Common.h"

/** ������Ϣ�ṹ */
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
 * @brief ����ָ���Ľ�����Ϣ�����ݿ�
 *
 * @param trade ������Ϣ
 */
int insert_trade(Trade* trade);

/**
 * @brief ����ָ�����п��Ľ��׼�¼
 *
 * @param card_id ��id
 */
void query_trade_by_card(ArrayList * trade_list, int card_id);