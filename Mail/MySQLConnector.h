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

extern MYSQL* mysql; //mysql����  
extern MYSQL_FIELD* fd;    //�ֶ�������  
extern char field[32][32];    //���ֶ�����ά����  
extern MYSQL_RES* res; //����ṹ�������е�һ����ѯ�����  
extern MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
extern char query[150]; //��ѯ���  
extern char username[20];	//��ǰ�û���
extern int user_id;	//��ǰ�û�id
extern char friend_list[1024][3][30];
extern char username[20];	//��ǰ�û���
extern char email[30];	//��ǰ�û�������
extern int total_friend;

extern bool ConnectDatabase();
extern bool QueryDatabase1();
extern bool user_login(char username[], char password[]);
extern int user_register(char username[], char password[], char email[]);
extern int add_friend(char friend_name[]);
extern int get_all_friend();
