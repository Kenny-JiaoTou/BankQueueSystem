SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

drop database if exists `BankQueueSystem`;
create database `BankQueueSystem`;

use `BankQueueSystem`;

drop table if exists `admin`;
create table `admin`(
	`id` int auto_increment,
	`login_name` varchar(50) not null		comment '����Աid',
	`password`	 varchar(200) not null		comment '��¼����',
	`login_time` datetime default now()		comment '�ϴε�¼ʱ��',
	primary key (`id`) using btree
)ENGINE=InnoDB comment '����Ա��';

drop table if exists `customer`;
create table `customer`(
	`id` int auto_increment					comment '�ͻ����',
	`name` varchar(50) not null				comment '�ͻ�����',
	`vip_level` int default null			comment 'vip�ȼ���nullΪ��vip�ͻ�',
	`begin_time` datetime					comment '�źſ�ʼʱ��',
	`end_time` datetime						comment '�źŽ���ʱ��',
	primary key (`id`) using btree
)ENGINE=InnoDB AUTO_INCREMENT=50000 comment '�ͻ���Ϣ��';

drop table if exists `card`;
create table `card`(
	`card_id` int auto_increment			comment '����',
	`user_id` int null default null			comment '�û�id',
	`balance`	double null default null	comment '���',
	primary key (`card_id`) using btree
)ENGINE=InnoDB AUTO_INCREMENT = 12000 comment '���п���Ϣ��';

drop table if exists `trade`;
create table `trade`(
	`id` int auto_increment					comment '����id',
	`card_id`	int not null				comment '���п�id',
	`to_card_id` int null					comment 'ת�˵������п�id',
	`trade_type` int default null			comment '��������',
	`trade_time` datetime default now()		comment '����ʱ��',
	`pre_money` double						comment '����ǰ���',
	`curr_money` double						comment '���׺����',
	primary key (`id`) using btree
)ENGINE=InnoDB AUTO_INCREMENT = 10000 comment '������Ϣ��';

SET FOREIGN_KEY_CHECKS = 1;











