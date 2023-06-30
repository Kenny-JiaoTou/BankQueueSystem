#include "../../include/dao/CardDAO.h"

void query_cards(ArrayList* card_list, int user_id)
{
	initial_mysql();
	if (card_list == NULL) {
		return;
	}
	char sql[50];
	sprintf(sql, "select * from card where user_id=%d", user_id);
	initial_mysql();
	MYSQL_RES* result = execute_query(sql);
	if (!result) {
		card_list = NULL;
		return;
	}
	MYSQL_FIELD* mysql_fields = mysql_fetch_fields(result);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result)) {
		Card* card = malloc(sizeof(Card));
		card->card_id = atoi(row[0]);
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
		arraylist_push(card_list, card);
	}
	mysql_free_result(result);
	release_mysql();
}

int insert_card(Card* card)
{
	initial_mysql();
	char* sql = "insert into card values(default, ?, ?);";
	MYSQL_BIND mysql_bind[2];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[0].buffer = (char*)&card->user_id;
	mysql_bind[0].is_null = 0;
	mysql_bind[0].length = 0;

	mysql_bind[1].buffer_type =	MYSQL_TYPE_DOUBLE;
	mysql_bind[1].buffer = (char*)&card->balance;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].length = 0;
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	release_mysql();
	return effected;
}

void query_card_latest(Card* card) {
	initial_mysql();
	//获取最新插入的自动标识列
	char * sql = "select * from card order by card_id desc limit 1; ";
	MYSQL_RES* result = execute_query(sql);
	MYSQL_ROW row;
	int card_id = -1;
	if (row = mysql_fetch_row(result)) {
		card->card_id = atoi(row[0]);
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
	}
	mysql_free_result(result);
	release_mysql();
}

void query_card_by_id(Card* card, int card_id)
{
	initial_mysql();
	char sql[50];
	sprintf(sql, "select * from card where card_id=%d", card_id);
	initial_mysql();
	MYSQL_RES* result = execute_query(sql);
	if (!result) {
		card->card_id = -1;
		return;
	}
	//MYSQL_FIELD* mysql_fields = mysql_fetch_fields(result);
	MYSQL_ROW row;
	if (row = mysql_fetch_row(result)) {
		card->card_id = atoi(row[0]);
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
	}
	mysql_free_result(result);
	release_mysql();
}

int update_card(Card* card)	//需要外部进行mysql的初始化和释放
{
	char* sql = "update card set user_id=?, balance=? where card_id=?;";
	MYSQL_BIND mysql_bind[3];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[0].buffer = (char*)&card->user_id;
	mysql_bind[0].is_null = 0;
	mysql_bind[0].length = 0;

	mysql_bind[1].buffer_type = MYSQL_TYPE_DOUBLE;
	mysql_bind[1].buffer = (char*)&card->balance;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].length = 0;

	mysql_bind[2].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[2].buffer = (char*)&card->card_id;
	mysql_bind[2].is_null = 0;
	mysql_bind[2].length = 0;
	return execute_update_stmt(sql, strlen(sql), mysql_bind);
}