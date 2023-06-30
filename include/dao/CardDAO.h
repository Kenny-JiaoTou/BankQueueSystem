/**
 * @file CardDAO.h
 * @brief ���п����ݷ��ʲ���
 *
 */
#pragma once

#include "../include/util/Common.h"

typedef struct {
	int card_id;			///< ����
	int user_id;			///< �û�id
	double balance;			///< ���
}Card;


/** �����û�id���ض�Ӧ�Ŀ���Ϣ */
void query_cards(ArrayList* card_list, int user_id);

/** ���벢���ؿ��ţ�����ʧ�ܷ���-1 */
int insert_card(Card* card);

/**
 * @brief �������µĿ���Ϣ
 *
 * @param card_id ��
 */
void query_card_latest(Card* card);

/**
 * @brief ���ݿ��Ų�ѯ��Ƭ��Ϣ
 *
 * @param card_id ��
 */
void query_card_by_id(Card* card, int card_id);

/**
 * @brief ���¿�Ƭ��Ϣ
 *
 * @param card ��
 */
int update_card(Card* card);
