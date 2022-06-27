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
		if(language==1)
		{
			printf("加载成功！\n");
		}
		else if(language==2)
		{
			printf("Load successful！\n");
		}
		fclose(fp);
	}
	else
	{
		if(language==1)
		{
			printf("加载失败\n");
		}
		else if(language==2)
		{
			printf("Loading failed！\n");
		}
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
		}
		if(language==1)
		{
			printf("加载成功！\n");
		}
		else if(language==2)
		{
			printf("Load successful！\n");
		}
		fclose(fp);
	}
	else
	{
		if(language==1)
		{
			printf("加载失败\n");
		}
		else if(language==2)
		{
			printf("Loading failed！\n");
		} 
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

//判断创建的银行卡号是否已存在 
int findUsername(char username[])
{
	Account *curP=head;
	while(curP!=NULL)
	{
		if(strcmp(curP->username,username)==0)
		{
			if(language==1)
			{
				printf("开户失败，该卡号已经存在！\n");
			}
			else if(language==2)
			{
				printf("Account opening failed, the username already exists！\n");
			} 
			system("pause");
			return 0;
		}
		curP=curP->next;
	} 
	if(language==1)
	{
		printf("开户成功！\n");
	}
	else if(language==2)
	{
		printf("Account opening successful！\n");
	} 
	system("pause");
	return 1; 	
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
		printf("Input telephone:\n");
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
	if(findUsername(newNodeP->username))
	{
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
	if(language==1)
	{
		printf("请输入旧密码：");
	}
	else if(language==2)
	{
		printf("Input old password:");
	}
	char oldPassword[100];
	scanf("%s",oldPassword);
	if(strcmp(oldPassword,curAccount->password)==0)
	{
		if(language==1)
		{
			printf("请输入新密码：");
		}
		else if(language==2)
		{
			printf("Input new password:");
		}
		scanf("%s",curAccount->password);
		while(strcmp(oldPassword,curAccount->password)==0)
		{
			if(language==1)
			{
				printf("新旧密码不能相同,请重新输入新密码：\n");
			}
			else if(language==2)
			{
				printf("The old and new passwords cannot be the same, please re-enter the new password：\n");
			}
			scanf("%s",curAccount->password);
		}
		if(language==1)
		{
			printf("密码已修改成功！\n");
		}
		else if(language==2)
		{
			printf("The password was modified successfully ！\n");
		}
	}
	else
	{
		if(language==1)
		{
			printf("旧密码输入错误！不能修改！\n");
		}
		else if(language==2)
		{
			printf("Old password entered incorrectly！ Cannot be modified！\n");
		}
	}
	system("pause");
	return;
}

void drawMoneyTransaction(Account * curAccount,float money)
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
	if(language==1)
	{
		printf("请输入取款金额：");
	}
	else if(language==2)
	{
		printf("Please enter the withdrawal amount：");
	} 
	float money;
	scanf("%f",&money);
	
	if(curAccount->money>=money)
	{
		curAccount->money-=money;
		if(language==1)
		{
			printf("取款成功！\n");
		}
		else if(language==2)
		{
			printf("Withdrawal was successful！");
		} 
		drawMoneyTransaction(curAccount,money);//产生取款交易记录 
	}
	else
	{
		if(language==1)
		{
			printf("余额不足！\n");
		}
		else if(language==2)
		{
			printf("Insufficient balance！\n");
		}
	}
	system("pause");
	return;
}
 
void saveMoneyTransaction(Account * curAccount,float money)
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
	if(language==1)
	{
		printf("请输入存款金额：");
	}
	else if(language==2)
	{
		printf("Please enter the deposit amount:");
	}
	float money;
	scanf("%f",&money);
	
	curAccount->money+=money;
	if(language==1)
	{
		printf("存款成功！\n");
	}
	else if(language==2)
	{
		printf("Deposit successful！\n");
	} 
	saveMoneyTransaction(curAccount,money);//产生存款交易记录
	system("pause");
	return;
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
	if(language==1)
	{
		printf("请输入对方账户：");
	}
	else if(language==2)
	{
		printf("Please enter the other username：");
	}
	char otherUsername[100];
	scanf("%s",otherUsername);
	
	//验证账户的合法性
	if(findOtherAccount(otherUsername))
	{
		if(language==1)
		{
			printf("请输入转账金额：");
		}
		else if(language==2)
		{
			printf("Please enter the transfer amount：");
		}
		float money;
		scanf("%f",&money); 
		
		//验证金额的合法性
		if(curAccount->money>=money)
		{
			//转账（当前账户余额减少，对方账户余额增加） 
			curAccount->money -= money;
			drawMoneyTransaction(curAccount,money);//产生取款交易记录 
			
			otherAccount->money += money;
			saveMoneyTransaction(otherAccount,money);//产生存款交易记录		
			if(language==1)
			{
				printf("转账成功！\n"); 
			}
			else if(language==2)
			{
				printf("The transfer was successful！\n"); 
			}				
		}
		else
		{
			if(language==1)
			{
				printf("余额不足！\n");
			}
			else if(language==2)
			{
				printf("Insufficient balance！\n");
			}
		}
	} 
	else
	{
		if(language==1)
		{
			printf("转账失败！\n");
		}
		else if(language==2)
		{
			printf("Transfer failed！\n");
		}
	}
	system("pause");
	return;
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
			printf("%s\t%s %s\t%c%f\n",curP->username,curP->nowdaytime,curP->nowtime,curP->type,curP->amount);
			order++; 
		}
		curP=curP->next;
	}
	if(order!=0)
	{
		if(language==1)
		{
			printf("在此银行进行过%d次交易 (*^_^*)\n\n",order);
		}
		else if(language==2)
		{
			printf("A total of %d transactions have been made at this bank (*^_^*)\n\n",order);
		}
	}
	else
	{
		if(language==1)
		{
			printf("还未进行过任何交易~\n");
		}
		else if(language==2)
		{
			printf("No transactions have been made yet~\n");
		}
	}
	system("pause");
	return;
}

void printCurAccount(char username[])
{
	Account * curP=head;
	while(curP!=NULL)
	{
		if(strcmp(curP->username,username)==0)
		{
			if(language==1)
			{
				printf("姓名:%s\n",curP->name);
				printf("身份证:%s\n",curP->idCard);
				printf("电话:%s\n",curP->tel);
				printf("卡号:%s\n",curP->username);
				printf("密码:%s\n",curP->password);
				printf("金额:%f\n",curP->money);
			}
			else if(language==2)
			{
				printf("name:%s\n",curP->name);
				printf("idCard:%s\n",curP->idCard);
				printf("telephone:%s\n",curP->tel);
				printf("username:%s\n",curP->username);
				printf("password:%s\n",curP->password);
				printf("money:%f\n",curP->money);
			}
		}
		curP=curP->next;
	}
	system("pause");
	return;	
}

void signIn()
{
	if(language==1)
	{
		printf("仅有三次输入机会！\n"); 
	}
	else if(language==2)
	{
		printf("There are only three input opportunities！\n"); 
	}
	for(int i=0;i<3;i++)
	{
		Account a; 
		if(language==1)
		{
			printf("请输入账号：");
		}
		else if(language==2)
		{
			printf("Input username:");
		}
		scanf("%s",a.username);
		
		if(language==1)
		{
			printf("请输入密码：");
		}
		else if(language==2)
		{
			printf("Input password:");
		}
		scanf("%s",a.password);
		
		if(findAccount(a))
		{
			while(1)
			{
				system("cls");
				if(language==1)
				{
				    printf("登录成功！\n");
				    printf("\n---------------------------------------------------------------------------------\n");
				    printf("\n|◆                          * 欢迎来到行星银行 *                              ◆|\n");
				    printf("\n---------------------------------------------------------------------------------\n\n");
				    printf("        -----------------------------------------------------------------\n");
				    printf("        |◆                         请选择操作                        ◆|\n");
				    printf("        |◆                                                           ◆|\n");
				    printf("        |◆                   ☆ 修改密码    请按 1                   ◆|\n"); 
				    printf("        |◆                   ☆ 取款业务    请按 2                   ◆|\n");
				    printf("        |◆                   ☆ 存款业务    请按 3                   ◆|\n");
				    printf("        |◆                   ☆ 转账业务    请按 4                   ◆|\n");
				    printf("        |◆                   ☆ 查询交易    请按 5                   ◆|\n");
				    printf("        |◆                   ☆ 查询信息    请按 6                   ◆|\n");
				    printf("        |◆                                                           ◆|\n");
				    printf("        -----------------------------------------------------------------\n");
				    printf("\n---------------------------------------------------------------------------------\n");
				    printf("\n|◆                                                                            ◆|\n");
				    printf("\n---------------------------------------------------------------------------------\n\n");
				}
				else if(language==2)
				{
				    printf("Login successful！\n");
				    printf("\n---------------------------------------------------------------------------------\n");
				    printf("\n|◆                     * Welcome to the Planet Bank *                         ◆|\n");
				    printf("\n---------------------------------------------------------------------------------\n\n");
				    printf("        -----------------------------------------------------------------\n");
				    printf("        |◆                  Please select the action                 ◆|\n");
				    printf("        |◆                                                           ◆|\n");
				    printf("        |◆              ☆ Change password      Press 1              ◆|\n"); 
				    printf("        |◆              ☆ Draw money           Press 2              ◆|\n");
				    printf("        |◆              ☆ Save money           Press 3              ◆|\n");
				    printf("        |◆              ☆ Transfer money       Press 4              ◆|\n");
				    printf("        |◆              ☆ Transaction records  Press 5              ◆|\n");
				    printf("        |◆              ☆ personal information Press 6              ◆|\n");
				    printf("        |◆                                                           ◆|\n");
				    printf("        -----------------------------------------------------------------\n");
				    printf("\n---------------------------------------------------------------------------------\n");
				    printf("\n|◆                                                                            ◆|\n");
				    printf("\n---------------------------------------------------------------------------------\n\n");
				}
				int x;
				if(language==1)
				{
					printf("请输入你的选择（如果想要退出此账户请按其他）：");
				}
				else if(language==2)
				{
					printf("Please enter your choice(Press other options if you want to exit this account)：");
				} 
				scanf("%d",&x);
				switch(x)
				{
					case 1:updatePassword();break;
					case 2:drawMoney();break;
					case 3:saveMoney();break;				
					case 4:transfer();break;
					case 5:printTransaction(a.username);break;
					case 6:printCurAccount(a.username);break;
					default:return; 
				}
			}
		}
		else
		{
			if(language==1)
			{
				printf("登录失败！\n");
			}
			else if(language==2)
			{
				printf("Login failed！\n");
			}
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
		    printf("\n---------------------------------------------------------------------------------\n");
		    printf("\n|◆                           * 欢迎来到行星银行 *                             ◆|\n");
		    printf("\n---------------------------------------------------------------------------------\n\n");
		    printf("        -----------------------------------------------------------------\n");
		    printf("        |◆                          请选择操作                       ◆|\n");
		    printf("        |◆                                                           ◆|\n");
		    printf("        |◆                      ☆ 开户    请按 1                    ◆|\n"); 
		    printf("        |◆                      ☆ 登录    请按 2                    ◆|\n");
		    printf("        |◆                      ☆ 退出    请按 3                    ◆|\n");
		    printf("        |◆                                                           ◆|\n");
		    printf("        -----------------------------------------------------------------\n");
		    printf("\n---------------------------------------------------------------------------------\n");
		    printf("\n|◆                                                                            ◆|\n");
		    printf("\n---------------------------------------------------------------------------------\n\n");
		}
		else if(language==2)
		{
		    printf("\n---------------------------------------------------------------------------------\n");
		    printf("\n|◆                      * Welcome to the Planet Bank *                        ◆|\n");
		    printf("\n---------------------------------------------------------------------------------\n\n");
		    printf("        -----------------------------------------------------------------\n");
		    printf("        |◆                   Please select the action                ◆|\n");
		    printf("        |◆                                                           ◆|\n");
		    printf("        |◆                    ☆ sign up    Press 1                  ◆|\n"); 
		    printf("        |◆                    ☆ sign in    Press 2                  ◆|\n");
		    printf("        |◆                    ☆ sign out   Press 3                  ◆|\n");
		    printf("        |◆                                                           ◆|\n");
		    printf("        -----------------------------------------------------------------\n");
		    printf("\n---------------------------------------------------------------------------------\n");
		    printf("\n|◆                                                                            ◆|\n");
		    printf("\n---------------------------------------------------------------------------------\n\n");
		}
		int n;
		if(language==1)
		{
			printf("请输入你的选择：");
		}
		else if(language==2)
		{
			printf("Please enter your choice：");
		} 
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

int main()
{
	printf("\n---------------------------------------------------------------------------------\n");
	printf("\n|◆                           * 欢迎来到行星银行 *                            ◆|\n");
	printf("\n|◆                      * Welcome to the Planet Bank *                       ◆|\n");
	printf("\n---------------------------------------------------------------------------------\n\n");
	printf("        -----------------------------------------------------------------\n");
	printf("        |◆                         请选择语言                        ◆|\n");
	printf("        |◆                                                           ◆|\n");
	printf("        |◆                   ☆ 中文服务    请按 1                   ◆|\n"); 
	printf("        |◆                   ☆ 英文服务    请按 2                   ◆|\n");
	printf("        |◆                                                           ◆|\n");
	printf("        -----------------------------------------------------------------\n");
	printf("\n---------------------------------------------------------------------------------\n");
	printf("\n|◆                                                                            ◆|\n");
	printf("\n---------------------------------------------------------------------------------\n\n");
	printf("请输入你的选择："); 
	scanf("%d",&language);
	   
	loadData();
	loadTransaction();
	showMenu();
	saveData();
	saveTransaction();
	
	return 0;	
}
