#include "pch.h"
#include "Smtp.h"
#include <iostream>
using namespace std;

int main2()
{
	int port;			//smtp�������˿�
	string srvDomain;	//smtp����������
	string userName;	//�û���
	string password;	//����
	string targetEmail; //Ŀ���ʼ���ַ
	string emailTitle;  //����
	string content;     //����

	//cout << "����smtp�������˿ڣ�";
	//cin >> port;
	//cout << "����smtp������������";
	//cin >> srvDomain;
	//cout << "�����û�����";
	//cin >> userName;
	//cout << "�������룺";
	//cin >> password;
	//cout << "����Ŀ���ʼ���ַ��";
	//cin >> targetEmail;
	//cout << "�������⣺";
	//cin >> emailTitle;
	//cout << "�������ݣ�";
	//cin >> content;

	//CSmtp smtp(
	//	port,			/*smtp�˿�*/
	//	srvDomain,		/*smtp��������ַ*/
	//	userName,		/*��������ַ*/
	//	password,		/*��������*/
	//	targetEmail,	/*Ŀ�������ַ*/
	//	emailTitle,		/*����*/
	//	content			/*�ʼ�����*/
	//);
	CSmtp smtp(
		25,								/*smtp�˿�*/
		"smtp.qq.com",					/*smtp��������ַ*/
		"873278492@qq.com",	/*��������ַ*/
		"grrungivsovmbfbg",					/*��������*/
		"873278492@qq.com",	/*Ŀ�������ַ*/
		"�ð�!",							/*����*/
		"XXXͬѧ����ã��յ���ظ���"		/*�ʼ�����*/
	);


	/**
	//��Ӹ���ʱע��,\һ��Ҫд��\\����Ϊת���ַ���Ե��
	string filePath("D:\\�γ���Ʊ���.doc");
	smtp.AddAttachment(filePath);
	*/

	/*�����Ե���CSmtp::DeleteAttachment����ɾ������������һЩ�������Լ���ͷ�ļ���!*/
	//filePath = "C:\\Users\\��ܲ��\\Desktop\\sendEmail.cpp";
	//smtp.AddAttachment(filePath);

	int err;
	if ((err = smtp.SendEmail_Ex()) != 0)
	{
		if (err == 1)
			cout << "����1: �������粻��ͨ������ʧ��!" << endl;
		if (err == 2)
			cout << "����2: �û�������,��˶�!" << endl;
		if (err == 3)
			cout << "����3: �û����������˶�!" << endl;
		if (err == 4)
			cout << "����4: ���鸽��Ŀ¼�Ƿ���ȷ���Լ��ļ��Ƿ����!" << endl;
	}
	system("pause");
	return 0;
}