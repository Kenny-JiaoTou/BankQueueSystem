#include "../include/biz/AdminBiz.h"

int admin_login(char* login_name, char* password) {
	Admin admin;
	query_admin(&admin, login_name);
	if (admin.id == -1) {
		return 0;		//查无此人
	}
	//比较密码
	char* md5_password = GetMD5(password);
	if (strcmp(md5_password, admin.password)) {
		return 1;
	}
	safe_free(md5_password);
	return -1;			//密码错误
}