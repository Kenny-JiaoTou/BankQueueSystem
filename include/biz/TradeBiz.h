/**
 * @file TradeBiz.h
 * @brief ʵ�ֽ���ҵ��
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

 /** ��������ö�� */
enum TradeType {
	DEPOSIT,			///< ���
	WITHDRAW,			///< ȡ��
	TRANSFER,			///< ת�ˣ�ת����
	BETRANSFERRED		///< ת�ˣ�ת�룩
};

/**
 * @brief �������������
 *
 */
void start_trade();

/**
 * @brief չʾ�ͻ�������Ϣ
 *
 * @param customer �ͻ�ָ��
 * @return int ��������
 */
int show_cards(Customer* customer);

/**
 * @brief Ϊָ���Ŀͻ�����
 *
 * @param cust_id �ͻ�id
 */
void create_card(int cust_id);

/**
 * @brief ������ǰ�ͻ��ķ���
 *
 * @param swindow ����ָ��
 */
void end_trade(SWindow* swindow);

/**
 * @brief ������λ�ͻ�
 *
 * @param swindow ����ָ��
 */
void call_next(SWindow* swindow);

/**
 * @brief ���ָ����Ƭ�����
 *
 * @param swindow ����ָ��
 */
void check_balance(int card_id);

/**
 * @brief ��ָ���Ĵ�����ָ���Ŀ�Ƭ���д�����
 *
 * @param swindow ����ָ��
 * @param card_id ��id
 */
void deposit_money(SWindow* swindow, int card_id);

/**
 * @brief ��ָ���Ĵ�����ָ���Ŀ�Ƭ����ȡ�����
 *
 * @param swindow ����ָ��
 * @param card_id ��id
 */
void withdraw_money(SWindow* swindow, int card_id);

/**
 * @brief ��ָ���Ĵ�����ָ���Ŀ�Ƭ����ת�˲���
 *
 * @param swindow ����ָ��
 * @param card_id ��id
 */
void transfer_money(SWindow* swindow, int card_id);

/**
 * @brief �鿴ָ�����Ľ��׼�¼
 *
 * @param card_id ��id
 */
void view_transactions(int card_id);