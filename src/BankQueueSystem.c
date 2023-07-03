// BankQueueSystem_CMake.cpp: 定义应用程序的入口点。
//

#include "../include/BankQueueSystem.h"

void start_system()
{
	init_system();
	show_welcome_message();		//显示欢迎信息
	int exit_flag = 0;			// 退出菜单标志
	while (!exit_flag)
	{
		
		show_main_menu();
		fflush(stdin);
		char choice = getch();
		fflush(stdin);
		switch (choice)
		{
		case '0':
			show_exit_message();
			exit_flag = 1;
			break;
		case '1':
			pick_number();
			break;
		case '2':
			start_trade();
			break;
		case '3':
			check_all_trade();
			break;
		case '4':
			update_VIP();
			break;
		default:
			printf("\n非法字符，请重新输入！！！%d\n", choice);
			break;
		}
		system("pause");
	}
	pq_free(waiting_queue);
	arraylist_free(swindow_list);
#ifndef DEBUG
	fclose(out_target);
#endif
}

void pick_number()
{
	printf("\n请输入客户名称 (新客户将自动注册):\n");
	//int waiting_count = waiting_queue->size;			//当前等待总数
	char name[20];
	printf("客户名称：");
	scanf("%s", name);
	Customer* customer = customer_sign_in(name);		//顾客签到
	update_pick(customer);
	printf("尊敬的<%s>，欢迎来到本银行，您当前的总取号是：%d。\n", customer->name, customer->pick_number_normal);
	printf("您的VIP等级为%d，当前VIP取号为：Vip%d-%d，您最多可提前 %d 号进入\n", 
		customer->vip_level, customer->vip_level, customer->pick_number_vip, customer->vip_level * 3);
	//查询空窗口/柜台
	int serve_flag = 0;
	if (waiting_queue->size == 0) {
		for (int i = 0; i < swindow_list->size; i++) {
			SWindow* swindow = arraylist_at(swindow_list, i);
			if (swindow->customer == NULL) {
				printf("柜台 %d 为空, 您可以在这里办理业务.\n", swindow->no);
				swindow_assign_customer(swindow, customer);
				serve_flag = 1;
				break;
			}
		}
	}
	// 如果没有空柜台，进入等待队列
	if (!serve_flag)
	{
		printf("还未轮到您, 请稍等...\n");
		pq_push(waiting_queue, customer);
	}
	printf("\n");
}

int login_admin()
{
	char login_name[40];
	char password[40];

	printf("\n此为**内部**功能，请登录管理员账号...\n");
	printf("账号：");
	scanf("%s", login_name);
	printf("密码：");
	scanf("%s", password);
	// 判断 ID 与密码是否符合
	return admin_login(login_name, password);
}

void check_all_trade()
{
	int admin_enter = 0;			//登录次数
	int login_flag = 0;				//是否登录
	while (admin_enter < 3)
	{
		if (login_admin())
		{
			login_flag = 1;
			break;
		}
		admin_enter++;
		printf("\n 账号或密码错误！！！ 请重新输入 ！！！\n\n");
		system("pause");
#ifndef DEBUG
		system("cls");
#endif
	}
	if (!login_flag)
		printf("登录失败次数太多，请稍后再试\n");
	else
	{
#ifndef DEBUG
		system("cls");
#endif
		printf("\n登录成功 :) 尊敬的管理员\n\n");
		printf("此为银行总交易信息：\n");
		ts_show_info(&global_trade_statistics);
		for (int i = 0; i < swindow_list->size; i++)
		{
			printf("\n>>>>\t服务窗口%d 的交易信息：\n", i + 1);
			SWindow* swindow = arraylist_at(swindow_list, i);
			ts_show_info(&global_trade_statistics);
			ts_show_info(&swindow->kpi);
		}
	}
}

void update_VIP()
{
	printf("\n请输入您的姓名:\n");
	char name[20];
	scanf("%s", name);
	Customer* customer = customer_sign_in(name);
#ifndef DEBUG
	system("cls");
#endif

	printf("\nVIP升级规则为：\n0:现有存款大于0\n");
	printf("1: 现有存款大于100000.00\n2: 现有存款大于500000.00\n\n");
	//获取用户总存款
	ArrayList card_list;
	arraylist_init(&card_list);
	query_cards(&card_list, customer->id);
	double total_balance = 0;
	for (int i = 0; i < card_list.size; i++) {
		Card* card = arraylist_at(&card_list, i);
		total_balance += card->balance;
	}
	printf("您目前的VIP等级为：%d\n", customer->vip_level);
	printf("您目前的总存款总额为：%.2lf\n", total_balance);
	printf("正在为您查询. . .\n\n");

	int vip_level = 0;
	if (total_balance >= 500000)
		vip_level = 2;
	else if (total_balance >= 100000)
		vip_level = 1;

	if (customer->vip_level < vip_level)
	{
		customer->vip_level = vip_level;
		update_customer(customer);
		printf("您的vip等级已为您升级至%d级\n", customer->vip_level);
	}
	else
	{
		if (customer->vip_level == 2)
		{
			printf("您已升到最高级！\n");
			return;
		}
		else
		{
			printf("您未达到升级要求！\n");
			return;
		}
	}
}

void init_system()
{
	//初始化输出目标对象
#ifdef DEBUG
	out_target = stdout;		//debug模式下输出到标准控制台
#else
	//printf("当前非DEBUG模式\n");
	out_target = fopen("BankQueueSystem.log", "a");
#endif
	//初始化数据结构
	waiting_queue = pq_create(customer_compare);
	swindow_list = create_swindows(COUNT_WINDOWS);
	ts_create(&global_trade_statistics);

	//初始化管理员数据
	Admin admin;
	query_admin(&admin, "admin");
	if(admin.id < 0){
		strcpy(admin.login_name, "admin");
		strcpy(admin.password, "123456");
		insert_admin(&admin);
	}
	
}