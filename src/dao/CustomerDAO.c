#include "../include/dao/CustomerDAO.h"

int insert_customer(Customer* customer)
{
	initial_mysql();
	char* sql = "insert into customer values (default, ?, ?, now(), null);";
	int customer_name_length = strlen(customer->name);
	MYSQL_BIND mysql_bind[2];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	mysql_bind[0].buffer_type = MYSQL_TYPE_STRING;
	mysql_bind[0].buffer = customer->name;
	mysql_bind[0].buffer_length = NAME_SIZE;
	mysql_bind[0].length = &customer_name_length;
	mysql_bind[0].is_null = 0;

	mysql_bind[1].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[1].buffer = (char*)&customer->vip_level;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].length = 0;
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	release_mysql();
	return effected;
}

int update_customer(Customer* customer)
{
	initial_mysql();
	char* sql = "update customer set name=?, vip_level=?, end_time=? where id=?;";
	int customer_name_length = strlen(customer->name);
	MYSQL_BIND mysql_bind[4];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	mysql_bind[0].buffer_type = MYSQL_TYPE_STRING;
	//mysql_bind[0].buffer = customer_name;
	mysql_bind[0].buffer = (char*)customer->name;
	mysql_bind[0].buffer_length = NAME_SIZE;
	mysql_bind[0].length = &customer_name_length;
	mysql_bind[0].is_null = 0;

	mysql_bind[1].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[1].buffer = (char*)&customer->vip_level;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].length = 0;

	if (customer->end_time == NULL || strcmp(customer->end_time, "NULL") == 0) {
		mysql_bind[2].buffer_type = MYSQL_TYPE_NULL;
		mysql_bind[2].buffer = NULL;
		mysql_bind[2].is_null = 0;
		mysql_bind[2].length = 0;
	}
	else {
		int customer_endtime_length = strlen(customer->end_time);
		mysql_bind[2].buffer_type = MYSQL_TYPE_STRING;
		mysql_bind[2].buffer = (char*)customer->end_time;
		mysql_bind[2].is_null = 0;
		mysql_bind[2].length = &customer_endtime_length;
	}
	

	mysql_bind[3].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[3].buffer = (char*)&customer->id;
	mysql_bind[3].is_null = 0;
	mysql_bind[3].length = 0;
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	release_mysql();
	return effected;
}

void query_customer(Customer* customer, char* name)
{
	char sql[150];
	sprintf(sql, "select * from customer where name =\'%s\';", name);
	int sql_length = strlen(sql);
	initial_mysql();

	MYSQL_RES* result = execute_query(sql);
	if (!result) {
		customer = NULL;
		return;
	}
	MYSQL_FIELD* mysql_fields = mysql_fetch_fields(result);
	MYSQL_ROW row;
	if (row = mysql_fetch_row(result))
	{
		customer->id = atoi(row[0]);
		strcpy(customer->name, row[1]);
		customer->vip_level = atoi(row[2]);
		strcpy(customer->begin_time, row[3]);
		if (row[4] != NULL) {
			strcpy(customer->end_time, row[4]);
		}
		else {
			strcpy(customer->end_time, "NULL");
		}
	}
	mysql_free_result(result);
	release_mysql();
}
