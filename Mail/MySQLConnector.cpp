#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"MySQLConnector.h"

using namespace std;

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

//int main1()
//{
//	ConnectDatabase();
//	char password[20],email[255];
//	printf_s("输入用户名：");
//	scanf_s("%s", username,20);
//	printf_s("输入密码：");
//	scanf_s("%s", password,20);
//	if (!user_login(username, password))	//登录
//	{
//		printf_s("用户名或密码错误！\n");
//		sprintf_s(username, "\0");
//		return 0;
//	}
//	printf_s("id: %d username: %s 登录成功！\n", user_id, username);
//
//
//	//printf_s("输入邮箱：");
//	//scanf_s("%s", email, 255);
//	//if (user_register(username, password, email) == 0)	//注册
//	//{
//	//	printf_s("用户名已存在！\n");
//	//}
//	//else
//	//{
//	//	printf_s("%s 注册成功！\n", username);
//	//}
//
//	//char friend_name[20];
//	//printf_s("输入好友用户名：");
//	//scanf_s("%s", friend_name, 20);
//	//if (add_friend(friend_name) == 0)	//登录
//	//{
//	//	printf_s("该用户名不存在！\n");
//	//}
//	//else
//	//{
//	//	printf_s("添加好友 %s 成功！\n",friend_name);
//	//}
//
//	int total_friend = get_all_friend();
//	printf_s("好友列表：\n");
//	for (int i = 0;i < total_friend;i++)
//	{
//		printf_s("%s", friend_list[i]);
//	}
//
//	//system("pause");
//	mysql_close(mysql);
//	return 0;
//}

bool ConnectDatabase()
{
	//初始化mysql  
	mysql_init(mysql);
	//返回false则连接失败，返回true则连接成功  
	//if (!(mysql_real_connect(mysql, "localhost", "root", "123456", "smtp_sys", 3306, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去  
	if (!(mysql_real_connect(mysql, "cn-zj-dx.sakurafrp.com", "root", "CWJ2933/.", "smtp_sys", 35543, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去  
	{
		printf("Error connecting to database:%s\n", mysql_error(mysql));
		return false;
	}
	else
	{
		printf("Connected...\n");
		return true;
	}
	return true;
}

bool QueryDatabase1()
{
	sprintf_s(query, "select * from users"); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以  
	mysql_query(mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
	//返回0 查询成功，返回1查询失败  
	if (mysql_query(mysql, query))    //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//获取结果集  
	if (!(res = mysql_store_result(mysql)))   //获得sql语句结束后返回的结果集  
	{
		printf("Couldn't get result from %s\n", mysql_error(mysql));
		return false;
	}

	//打印数据行数  
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysql));

	//获取字段的信息  
	char* str_field[32];  //定义一个字符串数组存储字段信息  
	for (int i = 0; i < 2; i++)  //在已知字段数量的情况下获取字段名  
	{
		str_field[i] = mysql_fetch_field(res)->name;
	}
	for (int i = 0; i < 2; i++)  //打印字段  
		printf("%10s\t", str_field[i]);
	printf("\n");
	//打印获取的数据  
	while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行  
	{
		printf("%10s\t%10s\t\n", column[0], column[1]);  //column是列数组  
	}
	return true;
}

bool user_login(char username[], char password[])
{
	sprintf_s(query, "select * from users where username='%s' and password='%s'",username,password);
	mysql_query(mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
	//返回0 查询成功，返回1查询失败  
	if (mysql_query(mysql, query))    //执行SQL语句
	{
		return false;	//查询失败
	}

	//获取结果集  
	if (!(res = mysql_store_result(mysql)))   //获得sql语句结束后返回的结果集  
	{
		return false;	//无法获得结果集
	}

	if (mysql_affected_rows(mysql) == 0)
	{
		return false;	//用户名或密码错误
	}
	else
	{
		column = mysql_fetch_row(res);
		user_id = atoi(column[0]);
		return true;	//登录成功
	}
}

int user_register(char username[], char password[], char email[])
{
	sprintf_s(query, "select * from users where username='%s'", username);
	mysql_query(mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
	//返回0 查询成功，返回1查询失败  
	if (mysql_query(mysql, query))    //执行SQL语句
	{
		return 0;	//查询失败
	}

	//获取结果集  
	if (!(res = mysql_store_result(mysql)))   //获得sql语句结束后返回的结果集  
	{
		return 0;	//无法获得结果集
	}

	if (mysql_affected_rows(mysql) > 0)
	{
		return 0;	//用户名已存在
	}
	
	sprintf_s(query, "insert into users(username,password,email) values ('%s','%s','%s')", username,password,email);
	if (mysql_query(mysql, query))    //执行SQL语句
	{
		return 0;	//注册失败
	}
	return mysql_affected_rows(mysql);
}

int add_friend(char friend_name[])
{
	sprintf_s(query, "select * from users where username='%s'", friend_name);
	mysql_query(mysql, "set names gbk"); //设置编码格式（set names gbk也行），否则cmd下中文乱码  
	//	返回0 查询成功，返回1查询失败  
	if (mysql_query(mysql, query))    //执行sql语句
	{
		return 0;	//查询失败
	}

	//获取结果集  
	if (!(res = mysql_store_result(mysql)))   //获得sql语句结束后返回的结果集  
	{
		return 0;	//无法获得结果集
	}

	if (mysql_affected_rows(mysql) == 0)
	{
		return 0;	//系统没有此用户
	}

	sprintf_s(query, "insert into friends(friend_name,friend_email,user_id) values('%s',(SELECT email from users where username = '%s'),%d)", friend_name,friend_name,user_id);
	if (mysql_query(mysql, query))    //执行sql语句
	{
		return 0;	//添加失败
	}
	return mysql_affected_rows(mysql);
}

int get_all_friend()
{
	sprintf_s(query, "select * from friends where user_id='%d'", user_id);
	mysql_query(mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
	//返回0 查询成功，返回1查询失败  
	if (mysql_query(mysql, query))    //执行SQL语句
	{
		return 0;	//查询失败
	}

	//获取结果集  
	if (!(res = mysql_store_result(mysql)))   //获得sql语句结束后返回的结果集  
	{
		return 0;	//无法获得结果集
	}

	if (mysql_affected_rows(mysql) == 0)
	{
		return 0;	//用户名或密码错误
	}

	int i = 0;
	while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取每一行好友信息
	{
		sprintf_s(friend_list[i], "%s(%s)\n\0",column[1],column[2]);  //column是列数组  
		i++;
	}
	return i;
}