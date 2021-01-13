#include "pch.h"
#include "Smtp.h"
#include <iostream>
using namespace std;

int main2()
{
	int port;			//smtp服务器端口
	string srvDomain;	//smtp服务器域名
	string userName;	//用户名
	string password;	//密码
	string targetEmail; //目的邮件地址
	string emailTitle;  //主题
	string content;     //内容

	//cout << "输入smtp服务器端口：";
	//cin >> port;
	//cout << "输入smtp服务器域名：";
	//cin >> srvDomain;
	//cout << "输入用户名：";
	//cin >> userName;
	//cout << "输入密码：";
	//cin >> password;
	//cout << "输入目的邮件地址：";
	//cin >> targetEmail;
	//cout << "输入主题：";
	//cin >> emailTitle;
	//cout << "输入内容：";
	//cin >> content;

	//CSmtp smtp(
	//	port,			/*smtp端口*/
	//	srvDomain,		/*smtp服务器地址*/
	//	userName,		/*你的邮箱地址*/
	//	password,		/*邮箱密码*/
	//	targetEmail,	/*目的邮箱地址*/
	//	emailTitle,		/*主题*/
	//	content			/*邮件正文*/
	//);
	CSmtp smtp(
		25,								/*smtp端口*/
		"smtp.qq.com",					/*smtp服务器地址*/
		"873278492@qq.com",	/*你的邮箱地址*/
		"grrungivsovmbfbg",					/*邮箱密码*/
		"873278492@qq.com",	/*目的邮箱地址*/
		"好啊!",							/*主题*/
		"XXX同学，你好！收到请回复！"		/*邮件正文*/
	);


	/**
	//添加附件时注意,\一定要写成\\，因为转义字符的缘故
	string filePath("D:\\课程设计报告.doc");
	smtp.AddAttachment(filePath);
	*/

	/*还可以调用CSmtp::DeleteAttachment函数删除附件，还有一些函数，自己看头文件吧!*/
	//filePath = "C:\\Users\\李懿虎\\Desktop\\sendEmail.cpp";
	//smtp.AddAttachment(filePath);

	int err;
	if ((err = smtp.SendEmail_Ex()) != 0)
	{
		if (err == 1)
			cout << "错误1: 由于网络不畅通，发送失败!" << endl;
		if (err == 2)
			cout << "错误2: 用户名错误,请核对!" << endl;
		if (err == 3)
			cout << "错误3: 用户密码错误，请核对!" << endl;
		if (err == 4)
			cout << "错误4: 请检查附件目录是否正确，以及文件是否存在!" << endl;
	}
	system("pause");
	return 0;
}