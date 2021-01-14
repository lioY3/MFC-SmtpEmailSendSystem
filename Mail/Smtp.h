#include <iostream>
#include <list>
#include <WinSock2.h>
using namespace std;

#pragma  comment(lib, "ws2_32.lib")	/*����ws2_32.lib��̬���ӿ�*/

const int MAXLEN = 1024;
const int MAX_FILE_LEN = 6000;

static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct FILEINFO // ��¼�ļ�Щ��Ϣ
{
	char fileName[128]; //�ļ�����
	char filePath[256]; //�ļ�����·��
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
	list <FILEINFO*> listFile;	// Ϊ�˷�������ļ���ɾ���ļ���ʹ��list����

	char buff[MAXLEN + 1];
	int buffLen;
	SOCKET sockClient;	// �ͻ����׽���

public:
	CSmtp(
		int port,
		string srvDomain,	//smtp����������
		string userName,	//�û���
		string password,	//����
		string targetEmail, //Ŀ���ʼ���ַ
		string CC,			//����
		string BCC,			//����
		string emailTitle,  //����
		string content      //����
	);
	~CSmtp(); //��������,�������ڵĺ����ѵ������ʱ,��������������,�Զ�ִ�����������ͷ�ϵͳ��Դ

public:
	bool CreateConn();						// ��������
	bool Send(string& message);				// ��������
	bool Recv();							// ��������
	int Login();							// ��½SMTP������
	bool SendEmailHead();					// �����ʼ�ͷ����Ϣ
	void FormatEmailHead(string& email);	// ��ʽ��Ҫ���͵��ʼ�ͷ��
	bool SendTextBody();					// �����ı���Ϣ	
	void AddAttachment(string& filePath);	// ��Ӹ���
	int SendAttachment_Ex();				// ���͸���
	bool SendEnd();							// ���ͽ�β��Ϣ
	int SendEmail_Ex();						// ����1.��������µĴ��� 2.�û������� 3.������� 4.�ļ������� 0.�ɹ�
	char* Base64Encode(char const* origSigned, unsigned origLength); // ת��ΪBase64����

	//void DeleteAttachment(string& filePath); //ɾ������
	//void DeleteAllAttachment(); //ɾ�����еĸ���

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