#include <stdio.h>
#include "account.h"
#include <stdlib.h>
#include <windows.h>
#include <conio.h> 

struct account a[10];  //�����˻���Ϣ
int g_accountNum;  //ϵͳ���˻�����
struct account g_loginUser;//��ǰ��½���˻�
void saveinfo();
int now;//���嵱ǰ�ǵڼ����û��˻�
int lang;//���� 
int system(const char *string);//���� 

void init()
{
	FILE * p = fopen("atm.txt","r");

	if(p ==NULL)
	{
	//	printf("���ļ�ʧ��\n");
		return;
	}
	else
	{
	//	printf("���ļ��ɹ�\n");
	}

//	printf("             ���ݼ�����.......\n");
	int i = 0;
	while(feof(p)==0)  //feof(p) �ж��ļ��Ƿ����������ֵ0����ʾ�ļ�û�������������
	{
		fscanf(p,"id:%d �˻�:%s ����:%d ���:%f\n",&a[i].id,a[i].name,&a[i].password,&a[i].balance); //��ȡ�ļ���Ϣ
	//	printf("��ȡ������Ϣ:id:%d �˺�:%s ����:%d ���:%f\n",a[i].id,a[i].name,a[i].password,a[i].balance); //��ӡ������Ϣ
		i++;
	}

	g_accountNum = i;
}

//��ϵͳ�в�������Ŀ���:����ֵΪ-1,��ʾû�в��ҵ�������ֵΪ��������ʾid���ڵ�λ��
int searchId(int kahao)
{
	int ret = -1;

	for(int i = 0 ;i < g_accountNum;i++)	
	{
		if(kahao == a[i].id)
		{
			g_loginUser = a[i];
			ret = i;
			//printf("��ǰiֵΪ%d",i);
			break;
		}
	
	}

	return ret;
}

//���ҵ�ǰ�˻������������������Ƿ���ȷ������ֵΪ0����ʾ����������󣬷���ɹ���
int checkPassword()
{
	if(lang==1)
	{
	int ret = 0;
	int pw;
	
	printf("Please input your password:");
	scanf("%d",& pw);

	for( int j= 0;j<2;j++)//bug�޸�:�޸��˵�������������󣬼�ʹ����������ȷ����Ȼ�����bug ��else����Ӷ�pw == g_loginUser.password���ж�
	{
		if(pw == g_loginUser.password)
		{
			ret = 1;
			break;
		}
		else
		{
			printf("Please input your password again:");
			scanf("%d",& pw);//����bugԭ�������һ�����������ֵ��Ȼ������pw����ж�����else֮ǰ������ѭ����ֱ�ӷ���retֵ����ʱretֵ��δ���޸�
			if(pw == g_loginUser.password)
			{
				ret = 1;
				break;
			}
		}
	}
	return ret;
    }
	
	if(lang==2)
	{
	int ret = 0;
	int pw;
	
	printf("����������:");
	scanf("%d",& pw);

	for( int j= 0;j<2;j++)//bug�޸�:�޸��˵�������������󣬼�ʹ����������ȷ����Ȼ�����bug ��else����Ӷ�pw == g_loginUser.password���ж�
	{
		if(pw == g_loginUser.password)
		{
			ret = 1;
			break;
		}
		else
		{
			printf("���ٴ���������:");
			scanf("%d",& pw);//����bugԭ�������һ�����������ֵ��Ȼ������pw����ж�����else֮ǰ������ѭ����ֱ�ӷ���retֵ����ʱretֵ��δ���޸�
			if(pw == g_loginUser.password)
			{
				ret = 1;
				break;
			}
		}
	}
	return ret;
	}
}

int login()
{
	int ret = 0;
	int num;
	int times= 0;

	printf("    Welcome to Red River Bank��\n");
	printf("   Please choose your language!\n");
	printf(">1< English\t>2< Simple Chinese\n");
	scanf("%d",&lang);
	system("cls");
	if(lang==1)
	{
	printf("Please enter your card number:");
	scanf("%d",& num);
	
	 if(-1!=searchId(num)) //��鿨��
	{
		now=searchId(num);
		printf("Card number recognition success!\n");
		
		if(checkPassword() == 1) ret = 1;//�������
		else printf("Password input is too frequent. Please take back the card and try again later.\n");
	}
	 else
		printf("Invalid card\n");
	system("cls");
	return ret;
	}
	if(lang==2)
	{
	printf("�����뿨��:");
	scanf("%d",& num);
	
	 if(searchId(num)!=-1) //��鿨��
	{
		now=searchId(num);
		printf("����ʶ��ɹ�!\n");
		
		if(checkPassword() == 1) ret = 1;//�������
		else
		{
			printf("��������������࣬��ȡ�ؿ�Ƭ���Ժ��ٳ��ԡ�\n");
		}
	}
	 else
		printf("��Ч��\n");
	
	system("cls");
	return ret;
	}
}

void welcom()
{
	if(lang==1)
	{
	printf("\n\n\n\n\n\t  Red Driver bank system\t\n\n");
	printf("\t>1< Withdraw\t>2< Transfer\n\n");
	printf("\t>3< Modify the password\n\n\t>4< Inquire\n\n");
	printf("\t>5< Sign out\n\n\n\n\n");

	}
	
	if(lang==2)
	{
	printf("\n\n\n\n\n\t      �ന����ϵͳ\t\n\n");
	printf("\t>1< ȡ��\t>2< ת��\n\n");
	printf("\t>3< ����\t>4< ��ѯ\n\n");
	printf("\t>5< ȡ��\n\n\n\n\n");
	}
}

void withDraw()
{
	if(lang==1)
	{
	printf("Withdraw money.......\n");
	printf("Please enter the amount of withdrawals:");

	int moneyNum;//�˴����ʵ�ʸ�Ϊint�ͣ�ȡǮֻ��ȡ��100������
	scanf("%d",&moneyNum);

	if(moneyNum>a[now].balance)printf("Sorry, your current account balance is not enough.\n");
	else
	{
		if(moneyNum<=100000)
		{
			if(moneyNum%100==0)
			{		
					a[now].balance-=moneyNum;
					printf("Your current account balance:%f\n",a[now].balance);
			}
			else
			{
				printf("Sorry, the amount of money can only be a multiple of one hundred.\n");
			}
		}
		else printf("Sorry, Red River bank's non VIP users can get a maximum of 100000 RMB per time.\n");
	}
	}
	
	if(lang==2)
	{
	printf("ȡ����.......\n");
	printf("������ȡ����:");

	int moneyNum;//�˴����ʵ�ʸ�Ϊint�ͣ�ȡǮֻ��ȡ��100������
	scanf("%d",&moneyNum);

	if(moneyNum>a[now].balance)printf("��Ǹ������ǰ���˻����㡣\n");
	else
	{
		if(moneyNum<=100000)
		{
			if(moneyNum%100==0)
			{		
					a[now].balance-=moneyNum;
					printf("��Ŀǰ�˻����Ϊ:%f\n",a[now].balance);
			}
			else
			{
				printf("�ܱ�Ǹ��ȡ����ֻ����100������ֵ\n");
			}
		}
		else printf("��Ǹ���ന���з�VIP�û�һ����߿�ȡ100000�����\n");
	}
	}
}

void transfer()
{
	if(lang==1)
	{
	printf("Transfer.......\n");
	printf("Please enter the target card number:");

	int id;
	float moneyNum;
	scanf("%d",&id);
	if(id == g_loginUser.id)
	{
		printf("Can't send money to yourself'\n");
		return;
	}

	int pos = searchId(id);  //��Ҫ���ҶԷ��˺��Ƿ����
	if(-1!= pos)
	{
		printf("Please enter the amount to be turned out\n");
		scanf("%f",&moneyNum);
		if(moneyNum>a[now].balance)printf("Sorry, your current account balance is not enough.\n");
		else
		{
			a[now].balance-=moneyNum;
			a[pos].balance+=moneyNum;
			printf("You have transferred the %f account to the %d account, and your current account balance is%f\n",a[pos].id,moneyNum,a[now].balance);
		}
	}
	else
		printf("The number is wrong\n");
	}
	
	if(lang==2)
	{
	printf("ת����.......\n");
	printf("������Է�����:");

	int id;
	float moneyNum;
	scanf("%d",&id);
	if(id == g_loginUser.id)
	{
		printf("����ת���Լ�\n");
		return;
	}

	int pos = searchId(id);  //��Ҫ���ҶԷ��˺��Ƿ����
	if(-1!= pos)
	{
		printf("������Ҫת���Ľ��\n");
		scanf("%f",&moneyNum);
		if(moneyNum>a[now].balance)printf("��Ǹ������ǰ���˻����㡣\n");
		else
		{
			a[now].balance-=moneyNum;
			a[pos].balance+=moneyNum;
			printf("������%d�˻���ת��%fԪ������ǰ�˻����Ϊ%f\n",a[pos].id,moneyNum,a[now].balance);
		}
	}
	else
		printf("����Ŀ���������\n");
	}
}
int mainMenu()
{

	if(lang==1)
	{
	
	int changePassword();
	int i = 1; //����ѭ���ж�ֵ 
	while(i)
	{
		system("cls");
		welcom();

		printf("Please choose the service what you need\n");
		int service;
		scanf("%d",&service);

		switch(service)
		{
			case 1:
				system("cls");
				withDraw(); //ȡ��
				printf("Enter any character to continue."); 
				getch(); 
				break;
			case 2:
				system("cls");
				transfer();//ת�� 
				printf("Enter any character to continue.");
				getch();
				break;
			case 3:
				system("cls");
				changePassword();//���� 
				printf("Enter any character to continue.");
				getch();
				break;
			case 4:
				system("cls");
				printf("id:%d\nAccount:%s\nBalance:%f\n",a[now].id,a[now].name,a[now].balance);
				printf("Enter any character to continue.");
				getch();
				break;
			case 5:
				system("cls");
				printf("Please take back the card\n");
				i = 0; 
				break;
			default:
				system("cls");
				printf("No option XD\n");
				printf("Enter any character to continue.");
				getch();
		}
	}
	}
	
	if(lang==2)
	{
	
	int changePassword();
	int i = 1; //����ѭ���ж�ֵ 
	while(i)
	{
		system("cls");
		welcom();

		printf("��ѡ������ķ���\n");
		int service;
		scanf("%d",&service);

		switch(service)
		{
			case 1:
				system("cls");
				withDraw(); //ȡ��
				printf("�����κΰ����Լ�������..."); 
				getch(); 
				break;
			case 2:
				system("cls");
				transfer();//ת�� 
				printf("�����κΰ����Լ�������..."); 
				getch(); 
				break;
			case 3:
				system("cls");
				changePassword();//���� 
				printf("�����κΰ����Լ�������..."); 
				getch(); 
				break;
			case 4:
				system("cls");
				printf("id:%d\n�˻�:%s\n���:%f\n",a[now].id,a[now].name,a[now].balance);
				printf("�����κΰ����Լ�������...");
				getch();
				break;
			case 5:
				system("cls");
				printf("��ȡ�ؿ�Ƭ\n");
				i = 0; 
				break;
			default:
				system("cls");
				printf("û�д�ѡ��\n");
				printf("�����κΰ����Լ�������...");
				getch();
		}
	}
	}
	return 0;

}

//�������˻���Ϣ���浽�ļ���
void saveinfo()
{
	FILE * p = fopen("atm.txt","w");

	if(p==NULL&&lang==1)
	{
		printf("There is an unknown error, please contact the bank staff for operationXD\n");
		return;
	}
	if(p==NULL&&lang==2)
	{
		printf("����δ֪��������ϵ���й�����Ա���в���XD\n");
		return;
	}

	int i = 0;
	for(;i<g_accountNum;i++)
		fprintf(p,"id:%d �˻�:%s ����:%d ���:%f\n",a[i].id,a[i].name,a[i].password,a[i].balance);
}

void changePassword()//���� 
{
	if(lang==1)
	{ 
	int checkPassword2(int pw);
	int nowpassword=0;//���� 
	int fnpassword1=0;//������1 
	int fnpassword2=0;//������2 
	printf("Please enter your current password\n");
	scanf("%d",&nowpassword);
	if(0!=checkPassword2(nowpassword))
	{
		printf("Please enter a new password\n");
		scanf("%d",&fnpassword1);
		if(fnpassword1>999999||fnpassword1<100000)
		{
			printf("The password is six digits, and your input does not conform to the specification��\n");
			return;
		}
		else
		{
			printf("Please enter a new password again\n");
			scanf("%d",&fnpassword2);
			if(fnpassword2>999999||fnpassword2<100000)
			{
				printf("Your input does not conform to the specification.\n");
				return;
			}
			if(fnpassword1==fnpassword2)
			{
				a[now].password=fnpassword2;
				printf("Password modification is successful!\n");
			} 
			else printf("The new password for the two input is not consistent, please try again!\n"); 
		}
	}
	else
	{
		printf("Wrong password!\n");
		return; 
	}
	} 
	
	if(lang==2)
	{ 
	int checkPassword2(int pw);
	int nowpassword=0;//���� 
	int fnpassword1=0;//������1 
	int fnpassword2=0;//������2 
	printf("����������ǰ������\n");
	scanf("%d",&nowpassword);
	if(0!=checkPassword2(nowpassword))
	{
		printf("������������\n");
		scanf("%d",&fnpassword1);
		if(fnpassword1>999999||fnpassword1<100000)
		{
			printf("����Ϊ��λ���֣��������벻���Ϲ淶!\n");
			return;
		}
		else
		{
			printf("���ٴ�����������\n");
			scanf("%d",&fnpassword2);
			if(fnpassword2>999999||fnpassword2<100000)
			{
				printf("�������벻���Ϲ淶!\n");
				return;
			}
			if(fnpassword1==fnpassword2)
			{
				a[now].password=fnpassword2;
				printf("�����޸ĳɹ���\n");
			} 
			else printf("��������������벻һ�£������ԣ�\n"); 
		}
	}
	else
	{
		printf("��������������\n");
		return; 
	}
	} 
}

int checkPassword2(int pw)//�ж������Ƿ���ȷ����ѭ�� 
{
	int ret = 0;

	if(pw == g_loginUser.password)
	{
		ret = 1;
	}
	return ret;
}


int main()
{
	system("color 1F");
	init();
	if(login()==1) //��½�ɹ�
	{
		mainMenu();
		saveinfo();
		//saveinfo();�˴���ʦ����ԭ����bug����mainMenu()����ִ�е�5ʱ��return��������򣬲�����ִ�е�saveinfo()����͵�����Ϣ�޷���txt�ĵ��и���
		
	}
	else
	{
		if(lang==2)printf("��½ʧ��\n");
		else if(lang==1)printf("Login fail.\n");
	}

	return 0;
}


