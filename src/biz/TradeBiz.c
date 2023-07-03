#include "../include/biz/TradeBiz.h"

void start_trade()
{
	
	while (1) {
		//ѡ�񴰿�
		printf("\n");
		swindow_show_customers();
		printf("\n���������ҵ��ķ��񴰿ںţ�");
		int swindow_no;
		scanf("%d", &swindow_no);
		fflush(stdin);
		if (swindow_no > COUNT_WINDOWS || swindow_no <= 0) {
			printf("��Ч���ںţ�\n");
			return;
		}
		SWindow* curr_window = arraylist_at(swindow_list, swindow_no - 1);
		if (!curr_window->customer) {
			printf("\n����%d��ǰû�пͻ���\n", swindow_no);
			return;
		}
		int choose_card = -1;
#ifdef DEBUG
		system("cls");
#endif // DEBUG
		int card_count = show_cards(curr_window->customer);
		if (card_count == 0) {	//���û�����п���ѡ���½������������ҵ��
			printf("��û�п������� 0 ���а쿨��������������ҵ�����");
			scanf("%d", &choose_card);
			if (choose_card != 0)
			{
				end_trade(curr_window);
				return;
			}
			create_card(curr_window->customer->id);
		}
		else { //����������п�������Ҫ����Ŀ��ſ�ʼ����ҵ��
			printf("���������ҵ��Ŀ��ţ����� 0 ���а쿨�������������ֽ���ҵ�������");
			scanf("%d", &choose_card);
			if (choose_card != 0)
			{
				// ��鿨���Ƿ����
				ArrayList cardList;
				arraylist_init(&cardList);
				query_cards(&cardList, curr_window->customer->id);
				int flag = 0;
				for (int i = 0; i < cardList.size; i++) {
					Card* card = arraylist_at(&cardList, i);
					if (choose_card == card->card_id) {
						flag = 1; break;
					}
				}
				if (!flag) {
					end_trade(curr_window);
					return;
				}
			}
			else {
				create_card(curr_window->customer->id);
				Card newCard;			//�½��Ŀ�
				query_card_latest(&newCard);
				//����id
				choose_card = newCard.card_id;
			}
		}
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID��%d, name: %s ���ţ�%d) �ڹ�̨ %d ��ʼҵ�����\n",
			curr_window->customer->id, curr_window->customer->name,
			choose_card, curr_window->no);
#ifndef DEBUG
		system("cls");
#endif
		//���ײ˵�ѡ��
		int exit_flag = 0; // �˳���־
		while (!exit_flag)
		{
			show_basicbusiness_menu();
			fflush(stdin);
			char choice = getch();
			fflush(stdin);

#ifndef DEBUG
			system("cls");
#endif
			switch (choice)
			{
			case '1':	//�������
				check_balance(choose_card);
				break;
			case '2':	//���
				deposit_money(curr_window, choose_card);
				break;
			case '3':	//ȡ��
				withdraw_money(curr_window, choose_card);
				break;
			case '4':	//ת��
				transfer_money(curr_window, choose_card);
				break;
			case '5':	//�鿴���׼�¼
				view_transactions(choose_card);
				break;
			case '0':	//����ҵ�����
				end_trade(curr_window);
				exit_flag = 1;
				break;
			default:
				printf("�Ƿ��ַ������������룡����\n");
				break;
			}
			if (!exit_flag)
			{
				system("pause");
				system("cls");
			}
		}
	}
}

int show_cards(Customer* customer)
{
	if (customer == NULL) {
		printf("ȱ�ٹ˿���Ϣ��������ȡ�Ű���ҵ��\n");
		return;
	}
	ArrayList* card_list = arraylist_create();
	query_cards(card_list, customer->id);
	printf("\n�𾴵�<%s>��",customer->name);
	int card_count = card_list->size;
	printf("���ڱ���ӵ�� %d �ſ�Ƭ��\n", card_count);
	if (card_count != 0) {	//����������п�������Ҫ����Ŀ��ſ�ʼ����ҵ��		
		for (int i = 0; i < card_count; i++) {
			Card* card = arraylist_at(card_list, i);
			printf("\t���ţ�%d����%.2lf\n", card->card_id, card->balance);
		}
	}
	arraylist_free(card_list);
	return card_count;
}

void create_card(int cust_id)
{
	Card card;
	card.user_id = cust_id;
	card.balance = 0;
	insert_card(&card);
	query_card_latest(&card);
	int card_id = card.card_id;
#ifndef DEBUG
	system("cls");
#endif
	if (card_id != -1) {
		printf("\n���Ŀ������� %d������ɹ�������\n\n", card_id);
	}
	else {
		printf("�������п�����ʧ�ܣ���������ԣ�\n");
	}
	system("pause");
}

void end_trade(SWindow* swindow)
{
	printf("\n��ӭ�´ι��٣���\n");
	swindow_leave_customer(swindow, swindow->customer);
	swindow->customer = NULL;
	call_next(swindow);
}

void call_next(SWindow* swindow) {
	if (waiting_queue->size > 0) {
		Customer* customer = pq_pop(waiting_queue);	//ȥ�������ض���Ԫ��
		swindow_assign_customer(swindow, customer);	//������񴰿�
		printf("�� Vip%d-%d ����̨ %d ����ҵ��\n", 
			swindow->customer->vip_level, swindow->customer->pick_number_vip, swindow->no);
	}
	else {
		printf("��ǰ�ŶӵĿͻ�Ϊ0\n");
	}
}

void check_balance(int card_id) {
	Card card;
	query_card_by_id(&card, card_id);
	if (card.card_id == -1) {
		printf("û���ҵ���Ӧ�Ŀ�Ƭ��Ϣ�����鿨�ţ�%d�Ƿ���ȷ\n", card_id);
		return;
	}
	printf("\n���ţ�%d����%.2lf\n\n", card.card_id, card.balance);
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (���ţ�%d)  ��ѯ�����Ϊ %.2lf\n", card.card_id, card.balance);
}

void deposit_money(SWindow* swindow, int card_id) {
	Card card;
	Trade trade;
	query_card_by_id(&card, card_id);
	double card_deposit = -1;
	while (card_deposit < 0)
	{
		printf("\n��������Ҫ����Ǯ����");
		scanf("%lf", &card_deposit);
		if (card_deposit < 0) {
			printf("\n������Ϣ�������������룡\n");
		}
	}
	trade.card_id = card.card_id;
	trade.pre_money = card.balance;
	card.balance += card_deposit;
	trade.curr_money = card.balance;
	trade.trade_type = DEPOSIT;
	//���¿��������뽻�׼�¼ -> һ�����������
	initial_mysql();
	transaction_start();
	int effected = update_card(&card);
	effected += insert_trade(&trade);
	if (effected != 2) {
		transaction_rollback();
		printf("�������ݲ���ȷ����������ѻع�\n");
	}
	else {
		transaction_commit();
	}
	release_mysql();

	// ͳ�ƽ��׽��
	swindow->kpi.total_deposits += card_deposit;
	swindow->kpi.flowing_water += card_deposit;
	global_trade_statistics.flowing_water += card_deposit;		//�ۼӽ�����ˮ
	global_trade_statistics.total_deposits += card_deposit;		//�ۼ��ܽ��׶�	
	//���� log
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ��� %.2lf\n",
		swindow->customer->id, swindow->customer->name, card_id, card_deposit);
}

void withdraw_money(SWindow* swindow, int card_id) {
	double card_withdraw = 0;
	printf("\n��������Ҫȡ���Ǯ����");
	scanf("%lf", &card_withdraw);
	// �ж�Ǯ���Ƿ�Ϊ��
	if (card_withdraw < 0)
	{
		printf("\n������Ϣ�������������룡\n");
		return;
	}
	Card card;
	query_card_by_id(&card, card_id);
	if (card.balance < card_withdraw)
	{
		printf("�������㣡����\n");
		// ����log
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ȡ���������\n",
			swindow->customer->id, swindow->customer->name, card.card_id);
		return;
	}
	//ȡ������
	Trade trade;
	trade.card_id = card.card_id;
	trade.to_card_id = card.card_id;		//��������ת���˻�Ҳ�ǵ�ǰ��
	trade.pre_money = card.balance;
	trade.curr_money = card.balance -= card_withdraw;
	trade.trade_type = WITHDRAW;
	initial_mysql();
	transaction_start();
	int effected = update_card(&card);
	effected += insert_trade(&trade);
	if (effected != 2) {
		transaction_rollback();
		printf("�������ݲ���ȷ��ȡ�������ѻع�\n");
	}
	else {
		transaction_commit();
	}
	release_mysql();
	// ͳ�ƽ��׽��
	global_trade_statistics.flowing_water += card_withdraw;
	swindow->kpi.flowing_water += card_withdraw;
	// ���� log
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ȡ�� %.2lf\n",
		swindow->customer->id, swindow->customer->name, card.card_id, card_withdraw);
	check_balance(card.card_id);
}

void transfer_money(SWindow* swindow, int card_id) {
	double transfer_money = 0; // ת�˽��
	int transfer_card = 0;     // ת�˿���
	printf("\n��������Ҫת�˵� ID �� Ǯ�����Կո�ָ�����\n");
	scanf("%d %lf", &transfer_card, &transfer_money);

	if (transfer_money < 0)
	{
		printf("\n������Ϣ�������������룡\n");
		return;
	}

	if (transfer_card == card_id)
	{
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ת�˴����޷�ת�˸��Լ�\n",
			swindow->customer->id, swindow->customer->name, card_id);
		printf("\n����ת�˸��Լ���\n");
		return;
	}
	Card card;
	query_card_by_id(&card, card_id);
	if (card.balance < transfer_money)
	{
		printf("\n�������㣡����\n");
		// ����log
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ת�˴�������.\n",
			swindow->customer->id, swindow->customer->name, card_id);
		return;
	}
	// ��ѯ�Է��˻��Ƿ����
	Card card2;			//�Է����п���Ϣ
	query_card_by_id(&card2, transfer_card);
	if (card2.card_id < 0)
	{
		printf("û�д��˻�������\n");
		// ���� log
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ת�˴����޷�ת�˵������ڵ��˻�\n",
			swindow->customer->id, swindow->customer->name, card_id);
		return;
	}
	//ת������
	Trade trade1, trade2;
	trade1.card_id = card.card_id;
	trade1.to_card_id = transfer_card;
	trade1.trade_type = TRANSFER;
	trade1.pre_money = card.balance;
	trade1.curr_money = card.balance - transfer_money;
	
	trade2.card_id = transfer_card;
	trade2.to_card_id = card.card_id;
	trade2.trade_type = BETRANSFERRED;	//��������Ϊ��ת��
	trade2.pre_money = card2.balance;
	trade2.curr_money = card2.balance + transfer_money;

	card.balance -= transfer_money;
	card2.balance += transfer_money;

	initial_mysql();
	transaction_start();
	int effected = update_card(&card);
	effected += update_card(&card2);
	effected += insert_trade(&trade1);
	effected += insert_trade(&trade2);
	if (effected != 4) {
		transaction_rollback();
		printf("�������ݲ���ȷ��ȡ�������ѻع�\n");
	}
	else {
		transaction_commit();
	}
	release_mysql();
	// ͳ�ƽ��׽��
	global_trade_statistics.flowing_water += transfer_money;
	swindow->kpi.flowing_water += transfer_money;
	// ���� log
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID��%d, name: %s ���ţ�%d)  ת�� %.2lf �� (���ţ�%d)\n",
		swindow->customer->id, swindow->customer->name, card.card_id, transfer_money, transfer_card);
	check_balance(card.card_id);
}

void view_transactions(int card_id) {
	char typeNames[4][10] = {"���", "ȡ��", "ת��", "ת��"};
	ArrayList trade_list;
	arraylist_init(&trade_list);
	query_trade_by_card(&trade_list, card_id);
	printf("\n�𾴵��û������Ŀ������ţ�%d�����׼�¼���£�\n", card_id);
	printf("[       ʱ��        ][��������][  ����ǰ���  ][  ���׺����  ][        ��ע        ]\n");
	for (int i = 0; i < trade_list.size; i++)
	{
		Trade* trade = arraylist_at(&trade_list, i);
		printf("[%8s]", trade->trade_time);					//����ʱ��
		printf("   %s   ", typeNames[trade->trade_type]);		//��������
		printf("   %-12.2lf    %-12.2lf", trade->pre_money, trade->curr_money);	//����ǰ��Ľ��
		//ת�˲���д�뱸ע��Ϣ��
		if (trade->trade_type == TRANSFER)
			printf("    ת���˻� %d", trade->to_card_id);
		if (trade->trade_type == BETRANSFERRED)
			printf("    ���˻� %d ת��", trade->card_id);
		printf("\n");
	}
}