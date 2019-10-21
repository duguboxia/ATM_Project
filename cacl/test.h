#include <stdio.h>
//最多支持用户数量
#define MAXUSER  10
//每行的最大长度
#define MAXLEN   128
typedef struct accountinfo
{
	int id;
	char username[10];
	char password[10];
	float money;
} ACCOUNT;


ACCOUNT g_users[MAXUSER];  //全局数组，保存用户信息
ACCOUNT g_loginuser; //记录当前的登录用户
int g_pos;    //当前用户在数组中的位置
int g_count;  //用户的数量
void getUserString1(char* str,const ACCOUNT user);
int init1();
int saveinfo();