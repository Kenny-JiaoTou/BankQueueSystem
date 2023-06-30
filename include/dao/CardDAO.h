/**
 * @file CardDAO.h
 * @brief 银行卡数据访问操作
 *
 */
#pragma once

#include "../include/util/Common.h"

typedef struct {
	int card_id;			///< 卡号
	int user_id;			///< 用户id
	double balance;			///< 余额
}Card;


/** 根据用户id返回对应的卡信息 */
void query_cards(ArrayList* card_list, int user_id);

/** 插入并返回卡号，插入失败返回-1 */
int insert_card(Card* card);

/**
 * @brief 返回最新的卡信息
 *
 * @param card_id 卡
 */
void query_card_latest(Card* card);

/**
 * @brief 根据卡号查询卡片信息
 *
 * @param card_id 卡
 */
void query_card_by_id(Card* card, int card_id);

/**
 * @brief 更新卡片信息
 *
 * @param card 卡
 */
int update_card(Card* card);
