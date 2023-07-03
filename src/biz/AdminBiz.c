#include "../include/biz/AdminBiz.h"

int admin_login(char* login_name, char* password) {
	Admin admin;
	query_admin(&admin, login_name);		//根据登录名查询对应的管理员信息
	if (admin.id < 0) {
		return 0;		//查无此人
	}
	//比较密码
	char* md5_password = GetMD5(password);	//将传入的密码进行md5加密
	//比较 加密后的传入密码 和 数据库中取出的密码
	if (strcmp(md5_password, admin.password) == 0) {
		return 1;
	}
	safe_free(md5_password);
	return 0;			//密码错误
}