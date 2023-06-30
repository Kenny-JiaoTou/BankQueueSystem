#pragma once

#include "../include/dao/TradeDAO.h"

int insert_trade(Trade* trade) {
	//initial_mysql();
	char* sql = "insert into trade values(default, ?, ?, ?, now(), ?, ?);";
	MYSQL_BIND mysql_bind[5];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[0].buffer = (char*)&trade->card_id;
	mysql_bind[0].is_null = 0;
	mysql_bind[0].length = 0;

	if (trade->to_card_id < 0) {
		trade->to_card_id = 0;
	}
	mysql_bind[1].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[1].buffer = (char*)&trade->to_card_id;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].length = 0;

	mysql_bind[2].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[2].buffer = (char*)&trade->trade_type;
	mysql_bind[2].is_null = 0;
	mysql_bind[2].length = 0;

	mysql_bind[3].buffer_type = MYSQL_TYPE_DOUBLE;
	mysql_bind[3].buffer = (char*)&trade->pre_money;
	mysql_bind[3].is_null = 0;
	mysql_bind[3].length = 0;

	mysql_bind[4].buffer_type = MYSQL_TYPE_DOUBLE;
	mysql_bind[4].buffer = (char*)&trade->curr_money;
	mysql_bind[4].is_null = 0;
	mysql_bind[4].length = 0;
	//release_mysql();
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	return effected;
}

void query_trade_by_card(ArrayList* trade_list, int card_id) {
	
	if (trade_list == NULL) return;
	char sql[50];
	sprintf(sql, "select * from trade where card_id=%d", card_id);
	initial_mysql();
	MYSQL_RES* result = execute_query(sql);
	if (!result) {
		trade_list = NULL;
		return;
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result)) {
		Trade* trade = malloc(sizeof(Trade));
		trade->id = atoi(row[0]);
		trade->card_id = atoi(row[1]);
		trade->to_card_id = atoi(row[2]);
		trade->trade_type = atoi(row[3]);
		strcpy(trade->trade_time, row[4]);
		trade->pre_money = atof(row[5]);
		trade->curr_money = atof(row[6]);
		arraylist_push(trade_list, trade);
	}
	release_mysql();
}