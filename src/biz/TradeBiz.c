#include "../include/biz/TradeBiz.h"

void start_trade()
{
	
	while (1) {
		//选择窗口
		printf("\n");
		swindow_show_customers();
		printf("\n请输入办理业务的服务窗口号：");
		int swindow_no;
		scanf("%d", &swindow_no);
		fflush(stdin);
		if (swindow_no > COUNT_WINDOWS || swindow_no <= 0) {
			printf("无效窗口号！\n");
			return;
		}
		SWindow* curr_window = arraylist_at(swindow_list, swindow_no - 1);
		if (!curr_window->customer) {
			printf("\n窗口%d当前没有客户！\n", swindow_no);
			return;
		}
		int choose_card = -1;
#ifdef DEBUG
		system("cls");
#endif // DEBUG
		int card_count = show_cards(curr_window->customer);
		if (card_count == 0) {	//如果没有银行卡，选择新建卡或办理其他业务
			printf("您没有卡，输入 0 进行办卡，输入其他结束业务办理：");
			scanf("%d", &choose_card);
			if (choose_card != 0)
			{
				end_trade(curr_window);
				return;
			}
			create_card(curr_window->customer->id);
		}
		else { //如果已有银行卡，输入要办理的卡号开始办理业务
			printf("请输入办理业务的卡号（输入 0 进行办卡，输入其他数字结束业务办理）：");
			scanf("%d", &choose_card);
			if (choose_card != 0)
			{
				// 检查卡号是否存在
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
				Card newCard;			//新建的卡
				query_card_latest(&newCard);
				//更新id
				choose_card = newCard.card_id;
			}
		}
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID：%d, name: %s 卡号：%d) 在柜台 %d 开始业务办理\n",
			curr_window->customer->id, curr_window->customer->name,
			choose_card, curr_window->no);
#ifndef DEBUG
		system("cls");
#endif
		//交易菜单选择
		int exit_flag = 0; // 退出标志
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
			case '1':	//交易余额
				check_balance(choose_card);
				break;
			case '2':	//存款
				deposit_money(curr_window, choose_card);
				break;
			case '3':	//取款
				withdraw_money(curr_window, choose_card);
				break;
			case '4':	//转账
				transfer_money(curr_window, choose_card);
				break;
			case '5':	//查看交易记录
				view_transactions(choose_card);
				break;
			case '0':	//结束业务办理
				end_trade(curr_window);
				exit_flag = 1;
				break;
			default:
				printf("非法字符，请重新输入！！！\n");
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
		printf("缺少顾客信息，请重新取号办理业务\n");
		return;
	}
	ArrayList* card_list = arraylist_create();
	query_cards(card_list, customer->id);
	printf("\n尊敬的<%s>，",customer->name);
	int card_count = card_list->size;
	printf("您在本行拥有 %d 张卡片：\n", card_count);
	if (card_count != 0) {	//如果已有银行卡，输入要办理的卡号开始办理业务		
		for (int i = 0; i < card_count; i++) {
			Card* card = arraylist_at(card_list, i);
			printf("\t卡号：%d，余额：%.2lf\n", card->card_id, card->balance);
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
		printf("\n您的卡（卡号 %d）办理成功！！！\n\n", card_id);
	}
	else {
		printf("您的银行卡办理失败，请检查后再试！\n");
	}
	system("pause");
}

void end_trade(SWindow* swindow)
{
	printf("\n欢迎下次光临：）\n");
	swindow_leave_customer(swindow, swindow->customer);
	swindow->customer = NULL;
	call_next(swindow);
}

void call_next(SWindow* swindow) {
	if (waiting_queue->size > 0) {
		Customer* customer = pq_pop(waiting_queue);	//去除并返回队首元素
		swindow_assign_customer(swindow, customer);	//分配服务窗口
		printf("请 Vip%d-%d 到柜台 %d 办理业务！\n", 
			swindow->customer->vip_level, swindow->customer->pick_number_vip, swindow->no);
	}
	else {
		printf("当前排队的客户为0\n");
	}
}

void check_balance(int card_id) {
	Card card;
	query_card_by_id(&card, card_id);
	if (card.card_id == -1) {
		printf("没有找到对应的卡片信息，请检查卡号：%d是否正确\n", card_id);
		return;
	}
	printf("\n卡号：%d，余额：%.2lf\n\n", card.card_id, card.balance);
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (卡号：%d)  查询到余额为 %.2lf\n", card.card_id, card.balance);
}

void deposit_money(SWindow* swindow, int card_id) {
	Card card;
	Trade trade;
	query_card_by_id(&card, card_id);
	double card_deposit = -1;
	while (card_deposit < 0)
	{
		printf("\n请输入您要存款的钱数：");
		scanf("%lf", &card_deposit);
		if (card_deposit < 0) {
			printf("\n输入信息错误，请重新输入！\n");
		}
	}
	trade.card_id = card.card_id;
	trade.pre_money = card.balance;
	card.balance += card_deposit;
	trade.curr_money = card.balance;
	trade.trade_type = DEPOSIT;
	//更新卡的余额及插入交易记录 -> 一个整体的事务
	initial_mysql();
	transaction_start();
	int effected = update_card(&card);
	effected += insert_trade(&trade);
	if (effected != 2) {
		transaction_rollback();
		printf("交易数据不正确，存款事务已回滚\n");
	}
	else {
		transaction_commit();
	}
	release_mysql();

	// 统计交易金额
	swindow->kpi.total_deposits += card_deposit;
	swindow->kpi.flowing_water += card_deposit;
	global_trade_statistics.flowing_water += card_deposit;		//累加交易流水
	global_trade_statistics.total_deposits += card_deposit;		//累加总交易额	
	//生成 log
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  存款 %.2lf\n",
		swindow->customer->id, swindow->customer->name, card_id, card_deposit);
}

void withdraw_money(SWindow* swindow, int card_id) {
	double card_withdraw = 0;
	printf("\n请输入您要取款的钱数：");
	scanf("%lf", &card_withdraw);
	// 判断钱数是否为负
	if (card_withdraw < 0)
	{
		printf("\n输入信息错误，请重新输入！\n");
		return;
	}
	Card card;
	query_card_by_id(&card, card_id);
	if (card.balance < card_withdraw)
	{
		printf("您的余额不足！！！\n");
		// 生成log
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  取款错误：余额不足\n",
			swindow->customer->id, swindow->customer->name, card.card_id);
		return;
	}
	//取款事务
	Trade trade;
	trade.card_id = card.card_id;
	trade.to_card_id = card.card_id;		//存款操作，转入账户也是当前卡
	trade.pre_money = card.balance;
	trade.curr_money = card.balance -= card_withdraw;
	trade.trade_type = WITHDRAW;
	initial_mysql();
	transaction_start();
	int effected = update_card(&card);
	effected += insert_trade(&trade);
	if (effected != 2) {
		transaction_rollback();
		printf("交易数据不正确，取款事务已回滚\n");
	}
	else {
		transaction_commit();
	}
	release_mysql();
	// 统计交易金额
	global_trade_statistics.flowing_water += card_withdraw;
	swindow->kpi.flowing_water += card_withdraw;
	// 生成 log
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  取款 %.2lf\n",
		swindow->customer->id, swindow->customer->name, card.card_id, card_withdraw);
	check_balance(card.card_id);
}

void transfer_money(SWindow* swindow, int card_id) {
	double transfer_money = 0; // 转账金额
	int transfer_card = 0;     // 转账卡号
	printf("\n请输入您要转账的 ID 与 钱数（以空格分隔）：\n");
	scanf("%d %lf", &transfer_card, &transfer_money);

	if (transfer_money < 0)
	{
		printf("\n输入信息错误，请重新输入！\n");
		return;
	}

	if (transfer_card == card_id)
	{
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  转账错误：无法转账给自己\n",
			swindow->customer->id, swindow->customer->name, card_id);
		printf("\n不能转账给自己！\n");
		return;
	}
	Card card;
	query_card_by_id(&card, card_id);
	if (card.balance < transfer_money)
	{
		printf("\n您的余额不足！！！\n");
		// 生成log
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  转账错误：余额不足.\n",
			swindow->customer->id, swindow->customer->name, card_id);
		return;
	}
	// 查询对方账户是否存在
	Card card2;			//对方银行卡信息
	query_card_by_id(&card2, transfer_card);
	if (card2.card_id < 0)
	{
		printf("没有此账户！！！\n");
		// 生成 log
		show_date(out_target, get_cur_date());
		fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  转账错误：无法转账到不存在的账户\n",
			swindow->customer->id, swindow->customer->name, card_id);
		return;
	}
	//转账事务
	Trade trade1, trade2;
	trade1.card_id = card.card_id;
	trade1.to_card_id = transfer_card;
	trade1.trade_type = TRANSFER;
	trade1.pre_money = card.balance;
	trade1.curr_money = card.balance - transfer_money;
	
	trade2.card_id = transfer_card;
	trade2.to_card_id = card.card_id;
	trade2.trade_type = BETRANSFERRED;	//交易类型为被转账
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
		printf("交易数据不正确，取款事务已回滚\n");
	}
	else {
		transaction_commit();
	}
	release_mysql();
	// 统计交易金额
	global_trade_statistics.flowing_water += transfer_money;
	swindow->kpi.flowing_water += transfer_money;
	// 生成 log
	show_date(out_target, get_cur_date());
	fprintf(out_target, " (ID：%d, name: %s 卡号：%d)  转账 %.2lf 至 (卡号：%d)\n",
		swindow->customer->id, swindow->customer->name, card.card_id, transfer_money, transfer_card);
	check_balance(card.card_id);
}

void view_transactions(int card_id) {
	char typeNames[4][10] = {"存款", "取款", "转出", "转入"};
	ArrayList trade_list;
	arraylist_init(&trade_list);
	query_trade_by_card(&trade_list, card_id);
	printf("\n尊敬的用户，您的卡（卡号：%d）交易记录如下：\n", card_id);
	printf("[       时间        ][交易类型][  交易前余额  ][  交易后余额  ][        备注        ]\n");
	for (int i = 0; i < trade_list.size; i++)
	{
		Trade* trade = arraylist_at(&trade_list, i);
		printf("[%8s]", trade->trade_time);					//交易时间
		printf("   %s   ", typeNames[trade->trade_type]);		//交易类型
		printf("   %-12.2lf    %-12.2lf", trade->pre_money, trade->curr_money);	//交易前后的金额
		//转账操作写入备注信息中
		if (trade->trade_type == TRANSFER)
			printf("    转入账户 %d", trade->to_card_id);
		if (trade->trade_type == BETRANSFERRED)
			printf("    从账户 %d 转入", trade->card_id);
		printf("\n");
	}
}