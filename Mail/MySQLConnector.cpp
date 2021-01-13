#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"MySQLConnector.h"

using namespace std;

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

//int main1()
//{
//	ConnectDatabase();
//	char password[20],email[255];
//	printf_s("�����û�����");
//	scanf_s("%s", username,20);
//	printf_s("�������룺");
//	scanf_s("%s", password,20);
//	if (!user_login(username, password))	//��¼
//	{
//		printf_s("�û������������\n");
//		sprintf_s(username, "\0");
//		return 0;
//	}
//	printf_s("id: %d username: %s ��¼�ɹ���\n", user_id, username);
//
//
//	//printf_s("�������䣺");
//	//scanf_s("%s", email, 255);
//	//if (user_register(username, password, email) == 0)	//ע��
//	//{
//	//	printf_s("�û����Ѵ��ڣ�\n");
//	//}
//	//else
//	//{
//	//	printf_s("%s ע��ɹ���\n", username);
//	//}
//
//	//char friend_name[20];
//	//printf_s("��������û�����");
//	//scanf_s("%s", friend_name, 20);
//	//if (add_friend(friend_name) == 0)	//��¼
//	//{
//	//	printf_s("���û��������ڣ�\n");
//	//}
//	//else
//	//{
//	//	printf_s("��Ӻ��� %s �ɹ���\n",friend_name);
//	//}
//
//	int total_friend = get_all_friend();
//	printf_s("�����б�\n");
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
	//��ʼ��mysql  
	mysql_init(mysql);
	//����false������ʧ�ܣ�����true�����ӳɹ�  
	//if (!(mysql_real_connect(mysql, "localhost", "root", "123456", "smtp_sys", 3306, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
	if (!(mysql_real_connect(mysql, "cn-zj-dx.sakurafrp.com", "root", "CWJ2933/.", "smtp_sys", 35543, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
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
	sprintf_s(query, "select * from users"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����  
	mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
	//����0 ��ѯ�ɹ�������1��ѯʧ��  
	if (mysql_query(mysql, query))    //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//��ȡ�����  
	if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
	{
		printf("Couldn't get result from %s\n", mysql_error(mysql));
		return false;
	}

	//��ӡ��������  
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysql));

	//��ȡ�ֶε���Ϣ  
	char* str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ  
	for (int i = 0; i < 2; i++)  //����֪�ֶ�����������»�ȡ�ֶ���  
	{
		str_field[i] = mysql_fetch_field(res)->name;
	}
	for (int i = 0; i < 2; i++)  //��ӡ�ֶ�  
		printf("%10s\t", str_field[i]);
	printf("\n");
	//��ӡ��ȡ������  
	while (column = mysql_fetch_row(res))   //����֪�ֶ���������£���ȡ����ӡ��һ��  
	{
		printf("%10s\t%10s\t\n", column[0], column[1]);  //column��������  
	}
	return true;
}

bool user_login(char username[], char password[])
{
	sprintf_s(query, "select * from users where username='%s' and password='%s'",username,password);
	mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
	//����0 ��ѯ�ɹ�������1��ѯʧ��  
	if (mysql_query(mysql, query))    //ִ��SQL���
	{
		return false;	//��ѯʧ��
	}

	//��ȡ�����  
	if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
	{
		return false;	//�޷���ý����
	}

	if (mysql_affected_rows(mysql) == 0)
	{
		return false;	//�û������������
	}
	else
	{
		column = mysql_fetch_row(res);
		user_id = atoi(column[0]);
		return true;	//��¼�ɹ�
	}
}

int user_register(char username[], char password[], char email[])
{
	sprintf_s(query, "select * from users where username='%s'", username);
	mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
	//����0 ��ѯ�ɹ�������1��ѯʧ��  
	if (mysql_query(mysql, query))    //ִ��SQL���
	{
		return 0;	//��ѯʧ��
	}

	//��ȡ�����  
	if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
	{
		return 0;	//�޷���ý����
	}

	if (mysql_affected_rows(mysql) > 0)
	{
		return 0;	//�û����Ѵ���
	}
	
	sprintf_s(query, "insert into users(username,password,email) values ('%s','%s','%s')", username,password,email);
	if (mysql_query(mysql, query))    //ִ��SQL���
	{
		return 0;	//ע��ʧ��
	}
	return mysql_affected_rows(mysql);
}

int add_friend(char friend_name[])
{
	sprintf_s(query, "select * from users where username='%s'", friend_name);
	mysql_query(mysql, "set names gbk"); //���ñ����ʽ��set names gbkҲ�У�������cmd����������  
	//	����0 ��ѯ�ɹ�������1��ѯʧ��  
	if (mysql_query(mysql, query))    //ִ��sql���
	{
		return 0;	//��ѯʧ��
	}

	//��ȡ�����  
	if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
	{
		return 0;	//�޷���ý����
	}

	if (mysql_affected_rows(mysql) == 0)
	{
		return 0;	//ϵͳû�д��û�
	}

	sprintf_s(query, "insert into friends(friend_name,friend_email,user_id) values('%s',(SELECT email from users where username = '%s'),%d)", friend_name,friend_name,user_id);
	if (mysql_query(mysql, query))    //ִ��sql���
	{
		return 0;	//���ʧ��
	}
	return mysql_affected_rows(mysql);
}

int get_all_friend()
{
	sprintf_s(query, "select * from friends where user_id='%d'", user_id);
	mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
	//����0 ��ѯ�ɹ�������1��ѯʧ��  
	if (mysql_query(mysql, query))    //ִ��SQL���
	{
		return 0;	//��ѯʧ��
	}

	//��ȡ�����  
	if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
	{
		return 0;	//�޷���ý����
	}

	if (mysql_affected_rows(mysql) == 0)
	{
		return 0;	//�û������������
	}

	int i = 0;
	while (column = mysql_fetch_row(res))   //����֪�ֶ���������£���ȡÿһ�к�����Ϣ
	{
		sprintf_s(friend_list[i], "%s(%s)\n\0",column[1],column[2]);  //column��������  
		i++;
	}
	return i;
}