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
	
	struct Account * next;//��һ�����ĵ�ַ 
}Account;

Account * head=NULL;//ָ��ͷ����ָ��
Account * tail=NULL;//ָ��β����ָ�� 

Account * curAccount=NULL;//��¼��ǰ�˻� 

void loadData() 
{
	FILE* fp=fopen("D:/atm.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			//������� 
			Account * newNode=(Account *)malloc(sizeof(Account));
			
			//����ʼ�� 
			newNode->next=NULL;
			fscanf(fp,"%s %s %s %s %s\n",newNode->name,newNode->idCard,newNode->tel,newNode->username,newNode->password); 
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
		fclose(fp);
		printf("���سɹ���\n");
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
	printf("����������룺");
	char oldPassword[100];
	scanf("%s",oldPassword);
	if(strcmp(oldPassword,curAccount->password)==0)
	{
		printf("�����������룺");
		scanf("%s",curAccount->password);
		while(strcmp(oldPassword,curAccount->password)==0)
		{
			printf("�¾����벻����ͬ\n");
			printf("��������\n");
			scanf("%s",curAccount->password);
		}
		printf("�޸ĳɹ�");
		
	}
	else
	{
		printf("������󣡲����޸ģ�\n");
	}
}

void signIn()
{
	for(int i=0;i<3;i++)
	{
		Account a; 
		printf("�������˺ţ�");
		scanf("%s",a.username);
		
		printf("���������룺");
		scanf("%s",a.password);
		
		if(findAccount(a))
		{
			printf("��¼�ɹ���\n");
			printf("�������밴 1 \n");
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
			printf("��¼ʧ�ܣ�\n");
		}
	}
}
//���سɹ�����1������ʧ�ܷ���0 
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
		printf("%s %s\n",curP->name,curP->password);
		curP=curP->next;
	}
}

int main()
{
	printf("��ӭ������������\n");
	printf("Welcome to XXX bank\n");
	printf("��1�����ķ���\n");
	printf("Press 2��English Service\n");
	scanf("%d",&language);
	loadData();
	showMenu();
	saveData();
	printLinkedList();
	return 0;	
}
