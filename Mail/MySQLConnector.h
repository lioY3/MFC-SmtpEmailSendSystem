#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<Windows.h>
#include<WinSock.h>
#include<mysql.h>

using namespace std;
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")

extern MYSQL* mysql; //mysql连接  
extern MYSQL_FIELD* fd;    //字段列数组  
extern char field[32][32];    //存字段名二维数组  
extern MYSQL_RES* res; //这个结构代表返回行的一个查询结果集  
extern MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列  
extern char query[150]; //查询语句  
extern char username[20];	//当前用户名
extern int user_id;	//当前用户id
extern char friend_list[1024][3][30];
extern char username[20];	//当前用户名
extern char email[30];	//当前用户的邮箱
extern int total_friend;

extern bool ConnectDatabase();
extern bool QueryDatabase1();
extern bool user_login(char username[], char password[]);
extern int user_register(char username[], char password[], char email[]);
extern int add_friend(char friend_name[]);
extern int get_all_friend();
