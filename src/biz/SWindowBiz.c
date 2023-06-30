#include "../include/biz/SWindowBiz.h"

ArrayList* create_swindows(int count)
{
	ArrayList* swindow_list = arraylist_create();
	for (int i = 0; i < count; i++) {
		SWindow* swindow = malloc(sizeof(SWindow));
		swindow->customer = NULL;
		swindow->no = i + 1;
		//swindow->kpi = malloc(sizeof(TradeStatistics));
		ts_create(&swindow->kpi);
		arraylist_push(swindow_list, swindow);
	}
	return swindow_list;
}

void swindow_assign_customer(SWindow* swindow, Customer* customer)
{
	cur_call_num[customer->vip_level]++;				//对应vip等级叫号数量+1
	swindow->customer = customer;						//设置当前服务的客户
	strcpy(swindow->customer->begin_time, get_cur_date_str());	//记录开始服务的时间
	//分配窗口
	show_date(out_target, get_cur_date());
	fprintf(out_target, "(ID: %d, 客户名称：%s)分配至窗口 %d \n", customer->id, customer->name, swindow->no);
}

void swindow_show_customers()
{
	for (int i = 0; i < swindow_list->size; i++) {
		SWindow* swindow = arraylist_at(swindow_list, i);
		if (swindow->customer == NULL) {
			printf("窗口 %d 空闲中\n", i + 1);
			continue;
		}
		printf("窗口 %d >> [ID: %d, 客户：%s]可以办理业务\n", 
			i + 1, swindow->customer->id, swindow->customer->name);
	}
}

void swindow_leave_customer(SWindow* swindow, Customer* customer)
{
	swindow->kpi.total_receptions++;			//当前服务窗口的接待总数+1
	strcpy(customer->end_time, get_cur_date_str());//设置结束服务的时间
	//计算当前客户服务总用时
	int time_cost = get_date_diff(customer->end_time, customer->begin_time);
	swindow->kpi.total_time += time_cost;		//累加当前柜台服务总用时

	global_trade_statistics.total_receptions;			//全局接待总数+1
	global_trade_statistics.total_time += time_cost;	//累加全局总服务时间

	// 日志信息
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID: %d 姓名: %s, vip：%d) 离开银行 \n", customer->id, customer->name, customer->vip_level);
	//safe_free(customer);
	safe_free(swindow->customer);
}