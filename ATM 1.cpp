#include<stdio.h>
#include<stdlib.h>

int language;//1-Chinese,2-English

typedef struct Account
{
	char name[100];
	char idCard[19];
	char tel[12];
	char username[25];
	char password[7];
	float money;
	
	struct Account * next;//��һ�����ĵ�ַ 
}Account;

Account * head=NULL;//ָ��ͷ����ָ��
Account * tail=NULL;//ָ��β����ָ�� 

void signUp()
{
	//����һ���ڴ�ռ䣬�����ַ��ֵ��ָ��newNodeP 
	Account * newNodeP=(Account *)malloc(sizeof(Account));
	
	//Ϊ�ڵ㸳ֵ 
	if(language==1)
	{
		printf("����������\n");
	}
	else if(language==2)
	{
		printf("Input name:\n");
	}
	scanf("%s",newNodeP->name);
	
	if(language==1)
	{
		printf("�������֤��\n");
	}
	else if(language==2)
	{
		printf("Input idCard:\n");
	}
	scanf("%s",newNodeP->idCard);
	
	if(language==1)
	{
		printf("����绰��\n");
	}
	else if(language==2)
	{
		printf("Input tel:\n");
	}
	scanf("%s",newNodeP->tel);
	
	if(language==1)
	{
		printf("���뿨�ţ�\n");
	}
	else if(language==2)
	{
		printf("Input username:\n");
	}
	scanf("%s",newNodeP->username);
	
	if(language==1)
	{
		printf("�������룺\n");
	}
	else if(language==2)
	{
		printf("Input password:\n");
	}
	scanf("%s",newNodeP->password);
	
	newNodeP->money=0.0f;
	newNodeP->next=NULL;
	
	//�������ӵ����� 
	if(head==NULL)
	{
		head=newNodeP;
		tail=newNodeP;
	}
	else
	{
		tail->next=newNodeP;
		tail=newNodeP;
	}
	
	if(language==1)
	{
		printf("��ӳɹ���\n");
	}
	else if(language==2)
	{
		printf("added��\n");
	}
}

void signIn()
{
	
}

void showMenu()
{
	while(1)
	{
		system("cls");
		if(language==1)
		{
			printf("��1, ����\n");
			printf("��2, ��½\n");
			printf("��3, �˳�\n");
		}
		else if(language==2)
		{
			printf("Press 1, sign up\n");
			printf("Press 2, sign in\n");
			printf("Press 3��sign out\n");
		}
		int n;
		scanf("%d",&n);
		if(n==1)
		{
			signUp();
		}
		else if(n==2)
		{
			signIn();
		}
		else if(n==3)
		{
			return; 
		}
	}
}

void printLinkedList()
{
	Account * curP=head;
	while(curP!=NULL)
	{
		printf("%s %s\n",curP->name,curP->username);
		curP=curP->next;
	}
}

int main()
{
	printf("��ӭ��������\n");
	printf("Welcome to bank\n");
	
	printf("��1�����ķ���\n");
	printf("Press 2��English Service\n");
	scanf("%d",&language);
	
	showMenu();
	
	printLinkedList();
	
	return 0;	
}
