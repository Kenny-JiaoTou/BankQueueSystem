/**
 * @file CustomerDAO.h
 * @brief �ͻ����ݷ��ʲ���
 *
 */
#pragma once

#include <string.h>
#include "../include/util/Date.h"
#include "../include/util/Utils.h"
#include "../include/util/Common.h"

#define NAME_SIZE 20			///< �ͻ���������
#define TIME_SIZE 20			///< ʱ���ַ�������

/** �ͻ��ṹ */
typedef struct {
	int id;						///< �ͻ�id
	int pick_number_normal;		///< ��ͨ����
	int pick_number_vip;		///< vip����
	int vip_level;				///< vip�ȼ�
	char name[NAME_SIZE];		///< �˿�����
	char begin_time[TIME_SIZE];	///< ��ʼʱ��
	char end_time[TIME_SIZE];	///< ����ʱ��
}Customer;

/** ��ָ���ͻ���Ϣд�뵽���ݿ� */
int insert_customer(Customer* customer);

/** ����ָ����(�Կͻ�idΪ����)�ͻ���Ϣ */
int update_customer(Customer* customer);

/** ����ָ����¼���Ŀͻ���Ϣ */
void query_customer(Customer* customer, char* login_name);
