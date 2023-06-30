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
	cur_call_num[customer->vip_level]++;				//��Ӧvip�ȼ��к�����+1
	swindow->customer = customer;						//���õ�ǰ����Ŀͻ�
	strcpy(swindow->customer->begin_time, get_cur_date_str());	//��¼��ʼ�����ʱ��
	//���䴰��
	show_date(out_target, get_cur_date());
	fprintf(out_target, "(ID: %d, �ͻ����ƣ�%s)���������� %d \n", customer->id, customer->name, swindow->no);
}

void swindow_show_customers()
{
	for (int i = 0; i < swindow_list->size; i++) {
		SWindow* swindow = arraylist_at(swindow_list, i);
		if (swindow->customer == NULL) {
			printf("���� %d ������\n", i + 1);
			continue;
		}
		printf("���� %d >> [ID: %d, �ͻ���%s]���԰���ҵ��\n", 
			i + 1, swindow->customer->id, swindow->customer->name);
	}
}

void swindow_leave_customer(SWindow* swindow, Customer* customer)
{
	swindow->kpi.total_receptions++;			//��ǰ���񴰿ڵĽӴ�����+1
	strcpy(customer->end_time, get_cur_date_str());//���ý��������ʱ��
	//���㵱ǰ�ͻ���������ʱ
	int time_cost = get_date_diff(customer->end_time, customer->begin_time);
	swindow->kpi.total_time += time_cost;		//�ۼӵ�ǰ��̨��������ʱ

	global_trade_statistics.total_receptions;			//ȫ�ֽӴ�����+1
	global_trade_statistics.total_time += time_cost;	//�ۼ�ȫ���ܷ���ʱ��

	// ��־��Ϣ
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID: %d ����: %s, vip��%d) �뿪���� \n", customer->id, customer->name, customer->vip_level);
	//safe_free(customer);
	safe_free(swindow->customer);
}