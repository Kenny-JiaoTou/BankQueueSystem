#include "../include/biz/TradeStatisticsBiz.h"

void ts_create(TradeStatistics* tradeStatistics)
{
	if (tradeStatistics == NULL) {
		tradeStatistics = malloc(sizeof(TradeStatistics));
	}
	memset(tradeStatistics, 0, sizeof(TradeStatistics));
}

void ts_show_time(int seconds)
{
	int all_hours = seconds / 3600;
	int all_minutes = (seconds % 3600) / 60;
	int all_seconds = seconds % 60;
	printf("%d 小时 %d 分钟 %d 秒\n", all_hours, all_minutes, all_seconds);
}

void ts_show_info(TradeStatistics* ts)
{
	printf("招待客户总数：%d\n", ts->total_receptions);
	printf("总流水：%.2lf\n", ts->flowing_water);
	printf("总存款量：%.2lf\n", ts->total_deposits);
	printf("逗留总时间：");
	ts_show_time(ts->total_time);
	printf("逗留平均时间：");
	if (ts->total_receptions != 0)
		ts_show_time(ts->total_time / ts->total_receptions);
	else
		ts_show_time(0);
}


