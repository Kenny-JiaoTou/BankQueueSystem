/**
 * @file AdminBiz.h
 * @brief ����Ա��ز���
 *
 */
#pragma once

#include "../include/dao/AdminDAO.h"
#include "../include/util/md5.h"

/** ��֤������û����������Ƿ�ƥ�� */
int admin_login(char* login_name, char* password);