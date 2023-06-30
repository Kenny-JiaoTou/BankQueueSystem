#include "../include/util/Common.h"

int mysql_error_no = 0;                         ///< mysql错误号
MYSQL mysql;                                    ///< mysql连接对象
MYSQL* mysql_connection = NULL;                 ///< mysql连接指针
MYSQL_STMT* stmt = NULL;                        ///< mysql预处理对象

const char* db_host = "localhost";				///< mysql host 地址
const char* db_username = "root";				///< mysql 用户名
const char* db_password = "Aa123456";			///< mysql 密码
const char* db_schema = "BankQueueSystem";  	///< mysql 数据库名称
int db_port = 3306;					            ///< mysql 数据库端口号
const char* db_query_charset = "GBK";

// ----  全局参数  ---------
FILE* out_target = NULL;                        ///< 当前系统日志写入的全局目标对象
ArrayList* swindow_list = NULL;                 ///< 全局银行服务窗口列表
ProirityQueue* waiting_queue = NULL;            ///< 全局等待客户队列
TradeStatistics global_trade_statistics;        ///< 全局交易统计信息对象
int cur_noraml_num = 0;						    ///< 总叫号
int cur_pick_num[VIP_LEVEL + 1] = { 0 };		///< 当前取号号码
int cur_call_num[VIP_LEVEL + 1] = { 0 };		///< 当前叫号号码

int initial_mysql()
{
	mysql_connection = mysql_init(&mysql);
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL初始化失败: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    //printf("MySQL初始化成功..............\n");
    mysql_connection = mysql_real_connect(&mysql, db_host, db_username, db_password, db_schema, db_port, NULL, 0);
    //连接数据库
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL连接失败: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    //printf("MySQL连接数据库成功..............\n");

    mysql_error_no = mysql_set_character_set(&mysql, db_query_charset);
    if (mysql_error_no != 0) {
        printf("设置默认字符集失败：%s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    //printf("设置默认字符集成功..............\n");
    //system("pause");
    //system("cls");
    return 1;
}

int execute_update_stmt(char* sql, int sql_len, MYSQL_BIND* mysql_bind) {
    Date date = get_cur_date();
	stmt = mysql_stmt_init(mysql_connection);
	if (!stmt) {
		fprintf(out_target, "%s\tmysql_stmt_init(), out of memory\n", get_cur_date_str());
	}
	if (mysql_stmt_prepare(stmt, sql, sql_len)) {
		fprintf(out_target, "%s\tmysql_stmt_prepare()->预编译插入操作失败，错误信息：%s\n", get_cur_date_str(), mysql_error(mysql_connection));
	}
    //int param_count = mysql_stmt_param_count(stmt);
	//绑定参数
	if (mysql_stmt_bind_param(stmt, mysql_bind)) {
		fprintf(out_target, "%s\tmysql_stmt_bind_param() failed, 错误信息：%s\n", get_cur_date_str(), mysql_stmt_error(stmt));
	}
	if (mysql_stmt_execute(stmt)) {
		fprintf(stdout, "%s\tmysql_stmt_execute(), 1 failed, 错误信息: %s\n", get_cur_date_str(), mysql_stmt_error(stmt));
		exit(0);
	}
    int affected_rows = mysql_stmt_affected_rows(stmt);
    return affected_rows;
}

MYSQL_RES* execute_query(char* sql)
{
    if (mysql_query(mysql_connection, sql)) {
        fprintf(out_target, "%s\tSQL语句执行错误：%s", get_cur_date_str(), mysql_error(mysql_connection));
    }
    return mysql_store_result(mysql_connection);
}

void transaction_start()
{
    mysql_autocommit(mysql_connection, 0);
}

void transaction_commit()
{
    mysql_commit(mysql_connection);
}

void transaction_rollback()
{
    mysql_rollback(mysql_connection);
}

void release_mysql() {
	if (stmt && mysql_stmt_close(stmt))
	{
		fprintf(out_target, " failed while closing the statement\n");
		fprintf(out_target, " %s\n", mysql_error(mysql_connection));
		exit(0);
	}
    mysql_close(mysql_connection);
    stmt = NULL;
    mysql_connection = NULL;
}