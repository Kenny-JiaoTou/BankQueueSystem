#include "../include/util/Common.h"

int mysql_error_no = 0;                         ///< mysql�����
MYSQL mysql;                                    ///< mysql���Ӷ���
MYSQL* mysql_connection = NULL;                 ///< mysql����ָ��
MYSQL_STMT* stmt = NULL;                        ///< mysqlԤ�������

const char* db_host = "localhost";				///< mysql host ��ַ
const char* db_username = "root";				///< mysql �û���
const char* db_password = "Aa123456";			///< mysql ����
const char* db_schema = "BankQueueSystem";  	///< mysql ���ݿ�����
int db_port = 3306;					            ///< mysql ���ݿ�˿ں�
const char* db_query_charset = "GBK";

// ----  ȫ�ֲ���  ---------
FILE* out_target = NULL;                        ///< ��ǰϵͳ��־д���ȫ��Ŀ�����
ArrayList* swindow_list = NULL;                 ///< ȫ�����з��񴰿��б�
ProirityQueue* waiting_queue = NULL;            ///< ȫ�ֵȴ��ͻ�����
TradeStatistics global_trade_statistics;        ///< ȫ�ֽ���ͳ����Ϣ����
int cur_noraml_num = 0;						    ///< �ܽк�
int cur_pick_num[VIP_LEVEL + 1] = { 0 };		///< ��ǰȡ�ź���
int cur_call_num[VIP_LEVEL + 1] = { 0 };		///< ��ǰ�кź���

int initial_mysql()
{
	mysql_connection = mysql_init(&mysql);
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL��ʼ��ʧ��: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    //printf("MySQL��ʼ���ɹ�..............\n");
    mysql_connection = mysql_real_connect(&mysql, db_host, db_username, db_password, db_schema, db_port, NULL, 0);
    //�������ݿ�
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL����ʧ��: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    //printf("MySQL�������ݿ�ɹ�..............\n");

    mysql_error_no = mysql_set_character_set(&mysql, db_query_charset);
    if (mysql_error_no != 0) {
        printf("����Ĭ���ַ���ʧ�ܣ�%s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    //printf("����Ĭ���ַ����ɹ�..............\n");
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
		fprintf(out_target, "%s\tmysql_stmt_prepare()->Ԥ����������ʧ�ܣ�������Ϣ��%s\n", get_cur_date_str(), mysql_error(mysql_connection));
	}
    //int param_count = mysql_stmt_param_count(stmt);
	//�󶨲���
	if (mysql_stmt_bind_param(stmt, mysql_bind)) {
		fprintf(out_target, "%s\tmysql_stmt_bind_param() failed, ������Ϣ��%s\n", get_cur_date_str(), mysql_stmt_error(stmt));
	}
	if (mysql_stmt_execute(stmt)) {
		fprintf(stdout, "%s\tmysql_stmt_execute(), 1 failed, ������Ϣ: %s\n", get_cur_date_str(), mysql_stmt_error(stmt));
		exit(0);
	}
    int affected_rows = mysql_stmt_affected_rows(stmt);
    return affected_rows;
}

MYSQL_RES* execute_query(char* sql)
{
    if (mysql_query(mysql_connection, sql)) {
        fprintf(out_target, "%s\tSQL���ִ�д���%s", get_cur_date_str(), mysql_error(mysql_connection));
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