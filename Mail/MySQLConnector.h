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
MYSQL* mysql = new MYSQL; //mysql����  
MYSQL_FIELD* fd;    //�ֶ�������  
char field[32][32];    //���ֶ�����ά����  
MYSQL_RES* res; //����ṹ�������е�һ����ѯ�����  
MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
char query[150]; //��ѯ���  
char username[20];	//��ǰ�û���
int user_id;	//��ǰ�û�id
char friend_list[1024][1024];

bool ConnectDatabase();
bool QueryDatabase1();
bool user_login(char username[], char password[]);
int user_register(char username[], char password[], char email[]);
int add_friend(char friend_name[]);
int get_all_friend();