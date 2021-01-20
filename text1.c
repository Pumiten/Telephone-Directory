#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	int id;
	char *name;
	char *tel;
	struct Node *pNext;
}List;

List *GetNode();        //构成通讯录的基本信息，返回基本信息单元的地址 pNode
void AddNode(List **ppHead,List **ppEnd,List *pNode);         //获取GetNode生成的地址pNode，并将其接在上一个的下面
int GetId();            //自动生成序号
char *GetName();        //自动生成人名
char *GetTel();         //自动生成电话号码
void InitInfo(List **ppHead,List **ppEnd);        //以上步骤的结合

int main(void)
{
	List *pHead = NULL;
	List *pEnd = NULL;

	InitInfo(&pHead,&pEnd);  //随机生成100个人的通讯信息

	while(pHead != NULL)                //遍历并显示链表内容
	{
		printf("%d\t%s\t%s\n",pHead->id,pHead->name,pHead->tel);
		pHead = pHead->pNext;
	}


	return 0;
}

List *GetNode()
{
	List *pNode = (List*)malloc(sizeof(List));
	pNode->id = GetId();
	pNode->name = GetName();
	pNode->tel = GetTel();
	pNode->pNext = NULL;
	return pNode;
}

void AddNode(List **ppHead,List **ppEnd,List *pNode)
{
	if(*ppHead == NULL)
	{
		*ppHead = pNode;
	}
	else
	{
		(*ppEnd)->pNext = pNode;
	}
	*ppEnd = pNode;
	return;
}

int GetId()
{
	static int id = 1;
	return id++;
}

char *GetName()
{
	char *name = (char*)malloc(6);
	int i;
	for(i=0;i<5;i++)
	{
		name[i] = rand() % 26 + 'a';
	}
	name[i] = '\0';
	return name;
}

char *GetTel()           //使用char *p = "str";初始化的字符串无法更改
{
	char *Tel = (char*)malloc(12);
	int i;
	char num;
	switch(rand()%4)
	{
		case 0:
			strcpy_s(Tel,sizeof(Tel),"111");
			break;
		case 1:
			strcpy_s(Tel,sizeof(Tel),"133");
			break;
		case 2:
			strcpy_s(Tel,sizeof(Tel),"155");
			break;
		case 3:
			strcpy_s(Tel,sizeof(Tel),"177");
			break;
	}
	for(i=3;i<11;i++)
	{
		Tel[i] = rand() % 10 + '0';
	}
	Tel[i] = '\0';
	return Tel;
}

void InitInfo(List **ppHead,List **ppEnd)
{
	int i;
	srand((unsigned int)time(NULL));
	for(i=1;i<=100;i++)
	{
		AddNode(ppHead,ppEnd,GetNode());
	}
	return;
}