#include "../include/biz/CustomerBiz.h"

Customer* customer_sign_in(char* name) {
	Customer* customer = malloc(sizeof(Customer));
	memset(customer, 0, sizeof(Customer));
	query_customer(customer, name);
	if (customer->id == 0) {
		//// δ��ѯ�����½��û�
		strcpy(customer->name, name);
		insert_customer(customer);
		query_customer(customer, customer->name);
		printf("�𾴵�%s�����Զ�Ϊ������ ID������ ID ��Ϊ %d\n", customer->name, customer->id);
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
	cur_noraml_num++;						//�ܽк�+1
	cur_pick_num[customer->vip_level]++;	//��Ӧvip�ȼ����Ŷ�����+1
	//����vip
	customer->pick_number_vip = cur_pick_num[customer->vip_level];
	customer->pick_number_normal = cur_noraml_num;
	show_date(out_target, get_cur_date());	//��־��¼
	fprintf(out_target, "[id: %d, ����: %s, vip: %d]ȡ���ĺ���Ϊ��%d\n", 
		customer->id, customer->name, customer->vip_level, customer->pick_number_normal);
}
