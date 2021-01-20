#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int E = 1;
typedef struct Node
{
	int id;
	char *name;
	char *tel;
	struct Node *pNext;
}List;

typedef struct PAGE
{
	int CurrentPage;
	int TotalInfo;
	int TotalPage;
	int OnePageInfo;
}Page;

// phase 1
List *GetNode();        //构成通讯录的基本信息，返回基本信息单元的地址 pNode
void AddNode(List **ppHead,List **ppEnd,List *pNode);         //获取GetNode生成的地址pNode，并将其接在上一个的下面
int GetId();            //自动生成序号
char *GetName();        //自动生成人名
char *GetTel();         //自动生成电话号码
void InitInfo(List **ppHead,List **ppEnd);        //以上步骤的结合

// phase 2
Page *GetPage(List *pHead,List *pEnd);           //输入当前页为0，输入每页显示信息条数，遍历链表得到总信息条数和总页数。返回这四个值。
void ShowInfo(Page *page,List *pHead);        //先确立当前页所显示信息的边界，在满足条件后显示通讯录信息。
void ShowMenu(Page *page);                    //显示菜单信息，包括当前是第几页，共几页，共几条，w上一页，s下一页，b返回
void TurnPage(Page *page);                    //翻页功能
char GetKey();          //获取输入的字母（摒除回车）
void Browse(Page *page,List *pHead);    //综合Phase2所有内容

int main(void)
{
	List *pHead = NULL;
	List *pEnd = NULL;


	InitInfo(&pHead,&pEnd);              //随机生成100个人的通讯信息
	Browse(GetPage(pHead,pEnd),pHead);


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

Page *GetPage(List *pHead,List *pEnd)
{
	Page *message = (Page*)malloc(sizeof(Page));
	message->CurrentPage = 1;
	message->OnePageInfo = 10;
	message->TotalInfo = 0;
	while(pHead != NULL)                //遍历链表
	{
		message->TotalInfo++;
		pHead = pHead->pNext;
	}
	if(message->TotalInfo % message->OnePageInfo == 0)
	{
		message->TotalPage = message->TotalInfo / message->OnePageInfo;
	}
	else
	{
		message->TotalPage = message->TotalInfo / message->OnePageInfo + 1;
	}
	return message;
}

void ShowInfo(Page *page,List *pHead)
{
	int begin = (page->CurrentPage - 1) * page->OnePageInfo + 1;
	int end,i = 1;
	if(page->TotalInfo - (page->CurrentPage - 1) * page->OnePageInfo >= page->OnePageInfo)
	{
		end = begin + page->OnePageInfo - 1;
	}
	else
	{
		end = page->TotalInfo;
	}
	while(pHead != NULL)
	{
		if(i >= begin && i <= end)
		{
			printf("%d\t%s\t%s\n",pHead->id,pHead->name,pHead->tel);
		}
		pHead = pHead->pNext;
		i++;
	}
	return;
}

void ShowMenu(Page *page)
{
	printf("第%d页  共%d页  共%d条  w上一页  s下一页  b返回\ne退出\n",page->CurrentPage,page->TotalPage,page->TotalInfo);
	return;
}

void TurnPage(Page **ppage)
{
    static int oldpage = 1;       //初始页只初始化一次
	int dis;
	switch(GetKey())
	{
		case 'w':
			if((*ppage)->CurrentPage != 1)
			{
				oldpage = (*ppage)->CurrentPage;
				(*ppage)->CurrentPage -= 1;
			}
			break;
		case 's':
			if((*ppage)->CurrentPage != (*ppage)->TotalPage)
			{
				oldpage = (*ppage)->CurrentPage;
				(*ppage)->CurrentPage += 1;
			}
			break;
		case 'b':
			dis = (*ppage)->CurrentPage - oldpage;
			(*ppage)->CurrentPage = oldpage;
			oldpage += dis;
			break;
		case 'e':
			E = 0;
			break;
		default:           //按错键就什么也不做
			NULL;
	}

	return;
}

char GetKey()
{
	char c;
	char z;
	int flag = 1;
	while((c = getchar()) != '\n' || flag == 1)
	{
		z = c;
		flag = 0;
	}
	return z;
}

void Browse(Page *page,List *pHead)
{
	while(E == 1)
	{
		ShowInfo(page,pHead);
		ShowMenu(page);
		TurnPage(&page);
	}
	return;
}





	