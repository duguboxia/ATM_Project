#include <stdio.h>
//���֧���û�����
#define MAXUSER  10
//ÿ�е���󳤶�
#define MAXLEN   128
typedef struct accountinfo
{
	int id;
	char username[10];
	char password[10];
	float money;
} ACCOUNT;


ACCOUNT g_users[MAXUSER];  //ȫ�����飬�����û���Ϣ
ACCOUNT g_loginuser; //��¼��ǰ�ĵ�¼�û�
int g_pos;    //��ǰ�û��������е�λ��
int g_count;  //�û�������
void getUserString1(char* str,const ACCOUNT user);
int init1();
int saveinfo();