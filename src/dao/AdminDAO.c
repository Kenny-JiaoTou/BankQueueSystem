#include "../include/dao/AdminDAO.h"

int insert_admin(Admin* admin) {
	initial_mysql();
	char* sql = "insert into `admin` values (default, ?, ?, null);";
	MYSQL_BIND mysql_bind[2];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	int name_length = strlen(admin->login_name);
	mysql_bind[0].buffer_type = MYSQL_TYPE_STRING;
	mysql_bind[0].buffer = (char*)admin->login_name;
	mysql_bind[0].is_null = 0;
	mysql_bind[0].buffer_length = 50;
	mysql_bind[0].length = &name_length;

	//密码需要转换成md5写入数据库
	char* md5_password = GetMD5(admin->password);
	int password_length = strlen(md5_password);
	mysql_bind[1].buffer_type = MYSQL_TYPE_STRING;
	mysql_bind[1].buffer = (char*)md5_password;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].buffer_length = 200;
	mysql_bind[1].length = &password_length;
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	release_mysql();
	safe_free(md5_password);
	return effected;
}

void query_admin(Admin* admin, char* login_name) {
	char sql[50];
	sprintf(sql, "select * from admin where login_name='%s';", login_name);
	initial_mysql();
	MYSQL_RES* result = execute_query(sql);
	if (!result) {
		admin->id = -1;
		return;
	}
	MYSQL_ROW row;
	if (row = mysql_fetch_row(result)) {
		admin->id = atoi(row[0]);
		strcpy(admin->login_name, row[1]);
		strcpy(admin->password, row[2]);
		if (row[3] != NULL) {
			strcpy(admin->login_time, row[3]);
		}
	}
	mysql_free_result(result);
	release_mysql();
}