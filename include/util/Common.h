/*****************************************************************//**
 * \file   Common.h
 * \brief  ͨ�ó���������
 * 
 * \author RayDataWorker001
 * \date   June 2023
 *********************************************************************/
#pragma once

#pragma comment(lib, "libmysql.lib")
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "../include/util/Date.h"
#include "../include/util/ArrayList.h"
#include "../include/util/ProiorityQueue.h"
#include "../include/biz/TradeStatisticsBiz.h"

#define VIP_LEVEL 10							///< vip�ȼ�
#define	COUNT_WINDOWS 3							///< ���񴰿�/��̨����

extern FILE* out_target;						///< ���Ŀ�꣬��������־�ļ���Ҳ�����ǿ���̨

extern ArrayList* swindow_list;					///< ��ǰ����ӵ�еĴ��ڼ���
extern ProirityQueue* waiting_queue;			///< ��ǰ�ȴ����û�����
extern TradeStatistics global_trade_statistics;	///< ȫ�ֽ���ͳ����Ϣ
extern int cur_noraml_num;						///< �ܽк�
extern int cur_pick_num[VIP_LEVEL + 1];			///< ��ǰ��VIP�����ȡ�ź���
extern int cur_call_num[VIP_LEVEL + 1];			///< ��ǰ��VIP����Ľкź���



/** ��ʼ��MySQL */
int initial_mysql();

/**
 * ִ��Ԥ����
 * @param sql_len strlen(sql)
 * @param mysql_bind �󶨲���Ĳ���
 * @return Ӱ�������
 */
int execute_update_stmt(char* sql, int sql_len, MYSQL_BIND* mysql_bind);

MYSQL_RES* execute_query(char* sql);

void transaction_start();

void transaction_commit();

void transaction_rollback();

/** �ͷ�MySQL��Դ */
void release_mysql();
