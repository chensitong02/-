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
	
	struct Account * next;//��һ�����ĵ�ַ 
}Account;

Account * head=NULL;//ָ��ͷ����ָ��
Account * tail=NULL;//ָ��β����ָ��
Account * curAccount=NULL;//��¼��ǰ�˻� 

typedef struct Transaction
{
	char username[100];
	time_t timestamp;
	char nowdaytime[80];
	char nowtime[80]; 
	char type;//+��ʾȡ�-��ʾ���
	float amount;//����
	
	struct Transaction * next;
}Transaction;

Transaction * tHead=NULL;
Transaction * tTail=NULL;

void loadData()
{
	FILE* fp=fopen("D:/atm.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))//�жϵ�û�е����ļ�ĩβʱ 
		{
			//������� 
			Account * newNode=(Account *)malloc(sizeof(Account));
			
			//����ʼ�� 
			newNode->next=NULL;
			int res=fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%f\n",newNode->name,newNode->idCard,newNode->tel,newNode->username,newNode->password,&newNode->money); 
			
			if(res==EOF)
			{
				return;
			}
			
			//��ӽ�㵽����
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
		printf("���سɹ���\n");
		fclose(fp);
	}
	else
	{
		printf("����ʧ�ܣ�\n"); 
	} 
}

void loadTransaction()
{
    FILE* fp=fopen("D:/Transaction.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			//������� 
			Transaction * newNode=(Transaction *)malloc(sizeof(Transaction));
			
			//����ʼ�� 
			newNode->next=NULL;
			int res=fscanf(fp,"%s\t%s %s\t%c%f\n",newNode->username,newNode->nowdaytime,newNode->nowtime,&newNode->type,&newNode->amount); 
			
			if(res==EOF)
			{
				return;
			}
			
			//��ӽ�㵽����
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
		printf("���سɹ���\n");
		fclose(fp);
	}
	else
	{
		printf("����ʧ�ܣ�\n"); 
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
}
//�ҵ���Ӧ�û�����1������0 
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

void updatePassword()//�������� 
{
	printf("����������룺");
	char oldPassword[100];
	scanf("%s",oldPassword);
	if(strcmp(oldPassword,curAccount->password)==0)
	{
		printf("�����������룺");
		scanf("%s",curAccount->password);
		while(strcmp(oldPassword,curAccount->password)==0)
		{
			printf("�¾����벻����ͬ,���������������룺\n");
			scanf("%s",curAccount->password);
		}
		printf("�������޸ĳɹ�\n��");
	}
	else
	{
		printf("������������󣡲����޸ģ�\n");
	}
}

void drawMoney()
{
	printf("������ȡ���");
	int money;
	scanf("%d",&money);
	
	if(curAccount->money>=money)
	{
		curAccount->money-=money;
		printf("ȡ��ɹ���\n");
		
		//�������׼�¼
		
		//�������
		Transaction * newNode=(Transaction *)malloc(sizeof(Transaction));
		
		//����ʼ��
		newNode->next=NULL;
		strcpy(newNode->username,curAccount->username);
		newNode->timestamp=time(NULL);
	    struct tm * timeinfo;
	    timeinfo=localtime(&newNode->timestamp);
	    strftime(newNode->nowdaytime,sizeof(newNode->nowdaytime),"%Y/%m/%d",timeinfo);
	    strftime(newNode->nowtime,sizeof(newNode->nowtime),"%H:%M:%S",timeinfo);
		newNode->type='-';
		newNode->amount=money;
		
		//��ӽ��׼�¼��㵽���� 
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
	else
	{
		printf("����!\n");
	}
}

void saveMoney()
{
	printf("���������");
	int money;
	scanf("%d",&money);
	
	curAccount->money+=money;
	printf("���ɹ���\n");
	
	//�������׼�¼
		
	//�������
	Transaction * newNode=(Transaction *)malloc(sizeof(Transaction));
	
	//����ʼ��
	newNode->next=NULL;
	strcpy(newNode->username,curAccount->username);
	newNode->timestamp=time(NULL);
	struct tm * timeinfo;
	timeinfo=localtime(&newNode->timestamp);
	strftime(newNode->nowdaytime,sizeof(newNode->nowdaytime),"%Y/%m/%d",timeinfo);
	strftime(newNode->nowtime,sizeof(newNode->nowtime),"%H:%M:%S",timeinfo);
	newNode->type='+';
	newNode->amount=money;
	
	//��ӽ��׼�¼��㵽���� 
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

/*void printTransaction()
{
    Transaction * curP=tHead;
	while(curP!=NULL)
	{
		printf("%s %s %c %f\n",curP->username,curP->nowtime,curP->type,curP->amount);
		curP=curP->next;
	}
}*/

void signIn()
{
	printf("��������������ᣡ\n"); 
	for(int i=0;i<3;i++)
	{
		Account a; 
		printf("�������˺ţ�");
		scanf("%s",a.username);
		
		printf("���������룺");
		scanf("%s",a.password);
		
		if(findAccount(a))
		{
		    system("cls");
			printf("��¼�ɹ���\n");
			printf("�����Ҫ���������밴1\n");
			printf("�����Ҫȡ���밴2\n");
			printf("�����Ҫ����밴3\n"); 
			printf("�����Ҫ��ӡ���׼�¼�밴4\n"); 
			int x;
			scanf("%d",&x);
			switch(x)
			{
				case 1:updatePassword();break;
				case 2:drawMoney();break;
				case 3:saveMoney();break;
				//case 4:printTransaction;break;
				default:break;
			}
			return; 
		}
		else
		{
			printf("��¼ʧ�ܣ�\n");
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
		scanf("%d",&n);//ѡ�����Ի��˳� 
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
		printf("%s\t%s\t%s\t%s\t%s\t%f\n",curP->name,curP->idCard,curP->tel,curP->username,curP->password,curP->money);
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
	
	loadData();
	loadTransaction();
	showMenu();
	saveData();
	saveTransaction();
	printLinkedList();
	
	return 0;	
}
