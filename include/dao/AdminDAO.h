/**
 * @file AdminDAO.h
 * @brief 管理员数据访问操作
 *
 */
#pragma once

#include "../include/util/Common.h"
#include "../include/util/md5.h"

typedef struct {
	int id;
	char login_name[50];
	char password[200];
	char login_time[20];
}Admin;

int insert_admin(Admin* admin);

void query_admin(Admin* admin, char* login_name);