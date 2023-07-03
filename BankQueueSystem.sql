SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

drop database if exists `BankQueueSystem`;
create database `BankQueueSystem`;

use `BankQueueSystem`;

drop table if exists `admin`;
create table `admin`(
	`id` int auto_increment,
	`login_name` varchar(50) not null		comment '管理员id',
	`password`	 varchar(200) not null		comment '登录密码',
	`login_time` datetime default now()		comment '上次登录时间',
	primary key (`id`) using btree
)ENGINE=InnoDB comment '管理员表';

drop table if exists `customer`;
create table `customer`(
	`id` int auto_increment					comment '客户编号',
	`name` varchar(50) not null				comment '客户名称',
	`vip_level` int default null			comment 'vip等级，null为非vip客户',
	`begin_time` datetime					comment '排号开始时间',
	`end_time` datetime						comment '排号结束时间',
	primary key (`id`) using btree
)ENGINE=InnoDB AUTO_INCREMENT=50000 comment '客户信息表';

drop table if exists `card`;
create table `card`(
	`card_id` int auto_increment			comment '卡号',
	`user_id` int null default null			comment '用户id',
	`balance`	double null default null	comment '余额',
	primary key (`card_id`) using btree
)ENGINE=InnoDB AUTO_INCREMENT = 12000 comment '银行卡信息表';

drop table if exists `trade`;
create table `trade`(
	`id` int auto_increment					comment '交易id',
	`card_id`	int not null				comment '银行卡id',
	`to_card_id` int null					comment '转账到的银行卡id',
	`trade_type` int default null			comment '交易类型',
	`trade_time` datetime default now()		comment '交易时间',
	`pre_money` double						comment '交易前余额',
	`curr_money` double						comment '交易后余额',
	primary key (`id`) using btree
)ENGINE=InnoDB AUTO_INCREMENT = 10000 comment '交易信息表';

-- # 存款
-- update card set balance=balance + 10000 where card_id=12001;
-- insert into trade values(default, 12001, 12001, 1, now(), preBalance, postBalance);

-- # 取款
-- update card set balance=balance - 10000 where card_id=12001;
-- insert into trade values(default, 12001, 12001, 1, now(), preBalance, postBalance);

-- # 转账 12001 -> 12002
-- update card set balance=balance - 10000 where card_id=12001;
-- update card set balance=balance + 10000 where card_id=12002;
-- insert into trade values(default, 12001, 12002, 1, now(), preBalance, postBalance);

SET FOREIGN_KEY_CHECKS = 1;











