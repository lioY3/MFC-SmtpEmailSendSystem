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
MYSQL* mysql = new MYSQL; //mysql连接  
MYSQL_FIELD* fd;    //字段列数组  
char field[32][32];    //存字段名二维数组  
MYSQL_RES* res; //这个结构代表返回行的一个查询结果集  
MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列  
char query[150]; //查询语句  
char username[20];	//当前用户名
int user_id;	//当前用户id
char friend_list[1024][1024];

bool ConnectDatabase();
bool QueryDatabase1();
bool user_login(char username[], char password[]);
int user_register(char username[], char password[], char email[]);
int add_friend(char friend_name[]);
int get_all_friend();