#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int language;//1-Chinese,2-English

typedef struct Account
{
	char name[50];
	char idCard[19];
	char tel[12];
	char username[25];
	char password[7];
	float money;
	
	struct Account * next;//下一个结点的地址 
}Account;

Account * head=NULL;//指向头结点的指针
Account * tail=NULL;//指向尾结点的指针 

Account * curAccount=NULL;//记录当前账户 

void loadData() 
{
	FILE* fp=fopen("D:/atm.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			//创建结点 
			Account * newNode=(Account *)malloc(sizeof(Account));
			
			//结点初始化 
			newNode->next=NULL;
			fscanf(fp,"%s %s %s %s %s\n",newNode->name,newNode->idCard,newNode->tel,newNode->username,newNode->password); 
			//添加结点到链表
			if(head==NULL)
			{
				head=newNode;
				tail=newNode;
			} 
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
		fclose(fp);
		printf("加载成功！\n");
	}
}

void saveData()
{
	FILE* fp=fopen("D:/atm.txt","w");
	if(fp==NULL)
	{
		return;
	}
	Account * curP=head;
	while(curP!=NULL)
	{
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\n",curP->name,curP->idCard,curP->tel,curP->username,curP->password);
		curP=curP->next;
	}
	fclose(fp);
}

void signUp()
{
	//申请一块内存空间，将其地址赋值给指针newNodeP 
	Account * newNodeP=(Account *)malloc(sizeof(Account));
	
	//为节点赋值 
	if(language==1)
	{
		printf("输入姓名：\n");
	}
	else if(language==2)
	{
		printf("Input name:\n");
	}
	scanf("%s",newNodeP->name);
	
	if(language==1)
	{
		printf("输入身份证：\n");
	}
	else if(language==2)
	{
		printf("Input idCard:\n");
	}
	scanf("%s",newNodeP->idCard);
	
	if(language==1)
	{
		printf("输入电话：\n");
	}
	else if(language==2)
	{
		printf("Input tel:\n");
	}
	scanf("%s",newNodeP->tel);
	
	if(language==1)
	{
		printf("输入卡号：\n");
	}
	else if(language==2)
	{
		printf("Input username:\n");
	}
	scanf("%s",newNodeP->username);
	if(language==1)
	{
		printf("输入密码：\n");
	}
	else if(language==2)
	{
		printf("Input password:\n");
	}
	scanf("%s",newNodeP->password);
	newNodeP->money=0.0f;
	newNodeP->next=NULL;
	//将结点添加到链表 
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
}

int findAccount(Account a)
{
	Account * curp=head;
	while(curp!=NULL)
	{
		if((strcmp(curp->username,a.username)==0)&&(strcmp(curp->password,a.password)==0))
		{
			curAccount=curp; 
			return 1;
		}
		curp=curp->next;
	}
	return 0;
}

void updatePassword()
{
	printf("请输入旧密码：");
	char oldPassword[100];
	scanf("%s",oldPassword);
	if(strcmp(oldPassword,curAccount->password)==0)
	{
		printf("请输入新密码：");
		scanf("%s",curAccount->password);
		while(strcmp(oldPassword,curAccount->password)==0)
		{
			printf("新旧密码不能相同\n");
			printf("重新输入\n");
			scanf("%s",curAccount->password);
		}
		printf("修改成功");
		
	}
	else
	{
		printf("密码错误！不能修改！\n");
	}
}

void signIn()
{
	for(int i=0;i<3;i++)
	{
		Account a; 
		printf("请输入账号：");
		scanf("%s",a.username);
		
		printf("请输入密码：");
		scanf("%s",a.password);
		
		if(findAccount(a))
		{
			printf("登录成功！\n");
			printf("换密码请按 1 \n");
			int i;
			scanf("%d",&i);
			if(i==1)
			{
				updatePassword();
				break;			
			} 
			else
			{
				break;
			}
		}
		else
		{
			printf("登录失败！\n");
		}
	}
}
//加载成功返回1，加载失败返回0 
void showMenu()
{
	while(1)
	{
		system("cls");
		if(language==1)
		{
			printf("按1, 开户\n");
			printf("按2, 登陆\n");
			printf("按3, 退出\n");
		}
		else if(language==2)
		{
			printf("Press 1, sign up\n");
			printf("Press 2, sign in\n");
			printf("Press 3，sign out\n");
		}
		int n;
		scanf("%d",&n);//选择语言或退出 
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
		printf("%s %s\n",curP->name,curP->password);
		curP=curP->next;
	}
}

int main()
{
	printf("欢迎来到王者银行\n");
	printf("Welcome to XXX bank\n");
	printf("按1，中文服务\n");
	printf("Press 2，English Service\n");
	scanf("%d",&language);
	loadData();
	showMenu();
	saveData();
	printLinkedList();
	return 0;	
}
