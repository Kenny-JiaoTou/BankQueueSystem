#include "../include/biz/CustomerBiz.h"

Customer* customer_sign_in(char* name) {
	Customer* customer = malloc(sizeof(Customer));
	memset(customer, 0, sizeof(Customer));
	query_customer(customer, name);
	if (customer->id == 0) {
		//// 未查询到，新建用户
		strcpy(customer->name, name);
		insert_customer(customer);
		query_customer(customer, customer->name);
		printf("尊敬的%s，已自动为您生成 ID，您的 ID 号为 %d\n", customer->name, customer->id);
		system("pause");
	}
	return customer;
}

int customer_compare(const void* lptr, const void* rptr)
{
	Customer* cust1 = (Customer*)lptr;
	Customer* cust2 = (Customer*)rptr;
	return (cust1->pick_number_normal - cust1->pick_number_vip * 3) - (cust2->pick_number_normal - cust2->vip_level * 3);
}

void update_pick(Customer* customer)
{
	cur_noraml_num++;						//总叫号+1
	cur_pick_num[customer->vip_level]++;	//相应vip等级的排队人数+1
	//设置vip
	customer->pick_number_vip = cur_pick_num[customer->vip_level];
	customer->pick_number_normal = cur_noraml_num;
	show_date(out_target, get_cur_date());	//日志记录
	fprintf(out_target, "[id: %d, 姓名: %s, vip: %d]取到的号码为：%d\n", 
		customer->id, customer->name, customer->vip_level, customer->pick_number_normal);
}
