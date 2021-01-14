#include <iostream>
#include <list>
#include <WinSock2.h>
using namespace std;

#pragma  comment(lib, "ws2_32.lib")	/*链接ws2_32.lib动态链接库*/

const int MAXLEN = 1024;
const int MAX_FILE_LEN = 6000;

static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct FILEINFO // 记录文件些信息
{
	char fileName[128]; //文件名称
	char filePath[256]; //文件绝对路径
};

class CSmtp
{
public:
	int port;
	string domain;
	string user;
	string pass;
	string targetAddr;
	string cc;
	string bcc;
	string title;
	string content;
	list <FILEINFO*> listFile;	// 为了方便添加文件，删除文件，使用list容器

	char buff[MAXLEN + 1];
	int buffLen;
	SOCKET sockClient;	// 客户端套接字

public:
	CSmtp(
		int port,
		string srvDomain,	//smtp服务器域名
		string userName,	//用户名
		string password,	//密码
		string targetEmail, //目的邮件地址
		string CC,			//抄送
		string BCC,			//密送
		string emailTitle,  //主题
		string content      //内容
	);
	~CSmtp(); //析构函数,对象所在的函数已调用完毕时,结束其生命周期,自动执行析构函数释放系统资源

public:
	bool CreateConn();						// 创建连接
	bool Send(string& message);				// 发送数据
	bool Recv();							// 接收数据
	int Login();							// 登陆SMTP服务器
	bool SendEmailHead();					// 发送邮件头部信息
	void FormatEmailHead(string& email);	// 格式化要发送的邮件头部
	bool SendTextBody();					// 发送文本信息	
	void AddAttachment(string& filePath);	// 添加附件
	int SendAttachment_Ex();				// 发送附件
	bool SendEnd();							// 发送结尾信息
	int SendEmail_Ex();						// 错误1.网络错误导致的错误 2.用户名错误 3.密码错误 4.文件不存在 0.成功
	char* Base64Encode(char const* origSigned, unsigned origLength); // 转换为Base64编码

	//void DeleteAttachment(string& filePath); //删除附件
	//void DeleteAllAttachment(); //删除所有的附件

	//void SetSrvDomain(string& domain);
	//void SetUserName(string& user);
	//void SetPass(string& pass);
	//void SetTargetEmail(string& targetAddr);
	//void SetCC(string& cc);
	//void SetBCC(string& bcc);
	//void SetEmailTitle(string& title);
	//void SetContent(string& content);
	//void SetPort(int port);
};