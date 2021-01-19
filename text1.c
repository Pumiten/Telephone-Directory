#include <stdio.h>
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
void InitInfo(List **ppHead,List **ppEnd,List *pNode);        //以上步骤的结合

int main(void)
{
	List *pHead = NULL;
	List *pEnd = NULL;
	srand((unsigned int)time(NULL));

	InitInfo(&pHead,&pEnd,GetNode());  //随机生成100个人的通讯信息

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
	static int id = 0;
	return id++;
}

char *GetName()
{
	//必须使用pMark才好使，直接对name做改变不起效，这是为什么呢？
	char *name = (char*)malloc(6);
	char *pMark = name;
	int i;
	for(i=1;i<=5;i++)
	{
		*pMark = rand() % 26 + 'a';
		pMark++;
	}
	*pMark = '\0';
	return name;
}

char *GetTel()
{
	char *Tel = (char*)malloc(12);
	char *pMark = Tel;
	int i;
	char num;
	int Head = rand() % 4;
	switch(Head)
	{
		case 0:
			Tel = "111";
			break;
		case 1:
			Tel = "133";
			break;
		case 2:
			Tel = "155";
			break;
		case 3:
			Tel = "177";
			break;
	}
	pMark += 3;
	for(i=0;i<8;i++)
	{
		num = rand() % 10 + '0';
		*pMark = num;
		pMark++;
	}
	*pMark = '\0';
	return Tel;
}

void InitInfo(List **ppHead,List **ppEnd,List *pNode)
{
	int i;
	srand((unsigned int)time(NULL));
	for(i=1;i<=100;i++)
	{
		AddNode(ppHead,ppEnd,GetNode());
	}
	return;
}