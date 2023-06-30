/**
 * @file AdminBiz.h
 * @brief 管理员相关操作
 *
 */
#pragma once

#include "../include/dao/AdminDAO.h"
#include "../include/util/md5.h"

/** 验证传入的用户名和密码是否匹配 */
int admin_login(char* login_name, char* password);