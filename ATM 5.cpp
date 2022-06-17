#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
Account * otherAccount=NULL;//记录对方账户

typedef struct Transaction
{
	char username[100];
	time_t timestamp;
	char nowdaytime[80];
	char nowtime[80]; 
	char type;//+表示存款，-表示取款
	float amount;//数额
	
	struct Transaction * next;
}Transaction;

Transaction * tHead=NULL;
Transaction * tTail=NULL;

void loadData()
{
	FILE* fp=fopen("D:/atm.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))//判断当没有到达文件末尾时 
		{
			//创建结点 
			Account * newNode=(Account *)malloc(sizeof(Account));
			
			//结点初始化 
			newNode->next=NULL;
			int res=fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%f\n",newNode->name,newNode->idCard,newNode->tel,newNode->username,newNode->password,&newNode->money); 
			
			if(res==EOF)
			{
				return;
			}
			
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
		printf("加载成功！\n");
		fclose(fp);
	}
	else
	{
		printf("加载失败！\n"); 
	} 
}

void loadTransaction()
{
    FILE* fp=fopen("D:/Transaction.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			//创建结点 
			Transaction * newNode=(Transaction *)malloc(sizeof(Transaction));
			
			//结点初始化 
			newNode->next=NULL;
			int res=fscanf(fp,"%s\t%s %s\t%c%f\n",newNode->username,newNode->nowdaytime,newNode->nowtime,&newNode->type,&newNode->amount); 
			
			if(res==EOF)
			{
				return;
			}
			
			//添加结点到链表
			if(tHead==NULL)
			{
				tHead=newNode;
				tTail=newNode;
			} 
			else
			{
				tTail->next=newNode;
				tTail=newNode;
			}
			if(feof(fp))
			{
				break;
			} 
		}
		printf("加载成功！\n");
		fclose(fp);
	}
	else
	{
		printf("加载失败！\n"); 
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
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%f\n",curP->name,curP->idCard,curP->tel,curP->username,curP->password,curP->money);
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

//找到对应用户返回1，否则0 
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

//对登录账户进行更改密码操作 
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
			printf("新旧密码不能相同,请重新输入新密码：\n");
			scanf("%s",curAccount->password);
		}
		printf("密码已修改成功\n！");
	}
	else
	{
		printf("旧密码输入错误！不能修改！\n");
	}
}

void drawMoneyTransaction(Account * curAccount,int money)
{
	//产生取款交易记录
		
	//创建结点
	Transaction * newNode=(Transaction *)malloc(sizeof(Transaction));
	
	//结点初始化
	newNode->next=NULL;
	strcpy(newNode->username,curAccount->username);
	newNode->timestamp=time(NULL);
    struct tm * timeinfo;
    timeinfo=localtime(&newNode->timestamp);
    strftime(newNode->nowdaytime,sizeof(newNode->nowdaytime),"%Y/%m/%d",timeinfo);
    strftime(newNode->nowtime,sizeof(newNode->nowtime),"%H:%M:%S",timeinfo);
	newNode->type='-';
	newNode->amount=money;
	
	//添加交易记录结点到链表 
	if(tHead==NULL)
	{
		tHead=newNode;
		tTail=newNode;
	}
	else
	{
		tTail->next=newNode;
		tTail=newNode;
	}
} 
//对登录账号进行取款操作 
void drawMoney()
{
	printf("请输入取款金额：");
	int money;
	scanf("%d",&money);
	
	if(curAccount->money>=money)
	{
		curAccount->money-=money;
		printf("取款成功！\n");
		drawMoneyTransaction(curAccount,money);//产生取款交易记录 
	}
	else
	{
		printf("余额不足!\n");
	}
}
 
void saveMoneyTransaction(Account * curAccount,int money)
{
	//产生存款交易记录
		
	//创建结点
	Transaction * newNode=(Transaction *)malloc(sizeof(Transaction));
	
	//结点初始化
	newNode->next=NULL;
	strcpy(newNode->username,curAccount->username);
	newNode->timestamp=time(NULL);
	struct tm * timeinfo;
	timeinfo=localtime(&newNode->timestamp);
	strftime(newNode->nowdaytime,sizeof(newNode->nowdaytime),"%Y/%m/%d",timeinfo);
	strftime(newNode->nowtime,sizeof(newNode->nowtime),"%H:%M:%S",timeinfo);
	newNode->type='+';
	newNode->amount=money;
	
	//添加交易记录结点到链表 
	if(tHead==NULL)
	{
		tHead=newNode;
		tTail=newNode;
	}
	else
	{
		tTail->next=newNode;
		tTail=newNode;
	}
}

//对登录账户进行存款操作 
void saveMoney()
{
	printf("请输入存款金额：");
	int money;
	scanf("%d",&money);
	
	curAccount->money+=money;
	printf("存款成功！\n");
	saveMoneyTransaction(curAccount,money);//产生存款交易记录
}

//保存所有交易信息 
void saveTransaction()
{
	FILE *fp=fopen("D:/transaction.txt","w");
	if(fp!=NULL)
	{
		Transaction * curp=tHead;
		while(curp!=NULL)
		{
			fprintf(fp,"%s\t%s %s\t%c%f\n",curp->username,curp->nowdaytime,curp->nowtime,curp->type,curp->amount);
			curp=curp->next;
		}	
	}
	fclose(fp);
}

//根据卡号查找账户，找到返回1，否则返回0 
int findOtherAccount(char otherUsername[])
{
	Account *curP=head;
	while(curP!=NULL)
	{
		if(strcmp(curP->username,otherUsername)==0)
		{
			otherAccount=curP;
			return 1;
		}
		curP=curP->next;
	} 
	return 0;
}

//对登录账户进行转账操作 
void transfer()
{
	printf("请输入对方账户：");
	char otherUsername[100];
	scanf("%s",otherUsername);
	
	//验证账户的合法性
	if(findOtherAccount(otherUsername))
	{
		printf("请输入转账金额：");
		int money;
		scanf("%d",&money); 
		
		//验证金额的合法性
		if(curAccount->money>=money)
		{
			//转账（当前账户余额减少，对方账户余额增加） 
			curAccount->money -= money;
			drawMoneyTransaction(curAccount,money);//产生取款交易记录 
			
			otherAccount->money += money;
			saveMoneyTransaction(otherAccount,money);//产生存款交易记录		
			printf("转账成功！\n"); 				
		}
		else
		{
			printf("余额不足！\n");
		}
	} 
	else
	{
		printf("转账失败！\n");
	}
}

//打印登录账户的所有交易信息
void printTransaction(char curUnsername[]) 
{
	int order=0;//定义一个指令来判断账户有无进行交易; 
    Transaction * curP=tHead;
	while(curP!=NULL)
	{
		if(strcmp(curP->username,curUnsername)==0)
		{
			printf("%s %s %c %f\n",curP->username,curP->nowtime,curP->type,curP->amount);
			order++; 
		}
		curP=curP->next;
	}
	if(order!=0)
	{
		printf("在此银行进行过%d次交易 (*^_^*)\n",order);
	}
	else
	{
		printf("还未进行过任何交易~\n");
	}
	system("pause");
}

void signIn()
{
	printf("仅有三次输入机会！\n"); 
	for(int i=0;i<3;i++)
	{
		Account a; 
		printf("请输入账号：");
		scanf("%s",a.username);
		
		printf("请输入密码：");
		scanf("%s",a.password);
		
		if(findAccount(a))
		{
		    system("cls");
			printf("登录成功！\n");
			printf("如果想要更换密码请按1\n");
			printf("如果想要取款请按2\n");
			printf("如果想要存款请按3\n"); 
			printf("如果想要转账请按4\n"); 
			printf("如果想要打印交易记录请按5\n");
			int x;
			scanf("%d",&x);
			switch(x)
			{
				case 1:updatePassword();break;
				case 2:drawMoney();break;
				case 3:saveMoney();break;				
				case 4:transfer();break;
				case 5:printTransaction(a.username);break;
				default:break;
			}
			return; 
		}
		else
		{
			printf("登录失败！\n");
		}
	}
}
 
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

//打印所有用户信息
void printLinkedList() 
{
	Account * curP=head;
	while(curP!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%f\n",curP->name,curP->idCard,curP->tel,curP->username,curP->password,curP->money);
		curP=curP->next;
	}
}

//打印所有用户交易信息
void printAllTransaction() 
{
    Transaction * curP=tHead;
	while(curP!=NULL)
	{
		printf("%s\t%s %s\t%c%f\n",curP->username,curP->nowdaytime,curP->nowtime,curP->type,curP->amount);
		curP=curP->next;
	}
} 

int main()
{
	printf("欢迎来到银行\n");
	printf("Welcome to bank\n");
	
	printf("按1，中文服务\n");
	printf("Press 2，English Service\n");
	scanf("%d",&language);
	
	loadData();
	loadTransaction();
	showMenu();
	saveData();
	saveTransaction();
	printLinkedList();
	printAllTransaction(); 
	
	return 0;	
}
