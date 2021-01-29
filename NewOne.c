#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//通讯录节点结构体
typedef struct Node
{
    int id;
    char *name;
    char *tel;
    struct Node *pNext;
} List;
//页数信息结构体
typedef struct PAGE
{
    int TotalPage;
    int CurrentPage;
    int TotalInfo;
    int OnePageInfo;
} Page;

//全局变量：节点的头指针和尾指针
List *pHead = NULL;
List *pEnd = NULL;
//全局变量，控制Browse函数是否继续循环的全局变量
int CONTINUEBROWSE = 1;

//添加通讯录并查看
void AddNode();  //生成和添加节点函数
int GetId();     //编纂通讯录序号，没使用一次该函数，值便+1
char *GetName(); //自动生成5个字母的人名，                     用到了随机数
char *GetTel();  //自动生成11位的电话，                     用到了随机数]
void InitInfo(); //自动生成通讯录，给了前几个函数srand()

//页面查看功能
Page *GetPage();  //生成关于页码的信息，返回页码的结构体
void ShowInfo(Page *pPage); //显示页面
void ShowMenu(Page *pPage);        //显示按钮菜单
void TurnPage(Page *pPage);        //翻页功能
char GetKey();   //获取输入的字符
void Browse(Page *pPage);   //浏览页面，结合了整个页面查看功能

//关键词查询功能
char *GetString();  //获取输入的字符串，并使之储存在一个合理大小的堆区内存里
List *GetNodeIn();  //手动将节点输入进链表内
void DeleteNode(); //通过id删除节点
void ChangeInfo();  //修改节点信息
void Query();      //查询功能

//整体界面系统
void Blank();

int main(void)
{
    Blank();
    //InitInfo();
    //GetNodeIn();
    //Browse(GetPage());
    return 0;
}
//生成和添加节点函数
void AddNode()
{
    //节点信息初始化
    List *pNode = (List*)malloc(sizeof(List));
    pNode->id = GetId();
    pNode->name = GetName();
    pNode->tel = GetTel();
    pNode->pNext = NULL;

    //将该节点接入链表
    List **ppHead = &pHead;
    List **ppEnd = &pEnd;
    if(pHead == NULL)
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
//编纂通讯录序号，没使用一次该函数，值便+1
int GetId()
{
    static int i = 1;
    return i++;
}
//自动生成5个字母的人名，                     用到了随机数
char *GetName()
{
    int i;
    char *pName = (char *)malloc(6);
    char *pMark = pName;
    for (i = 0; i < 5;i++)
    {
        pMark[i] = rand() % 26 + 'a';
    }
    pMark[i] = '\0';
    return pName;
}
//自动生成11位的电话，                     用到了随机数
char *GetTel()
{
    int i;
    char *pTel = (char *)malloc(12);
    //前3位号码选择
    switch(rand() % 4)
    {
        case 0:
            strcpy_s(pTel, sizeof(pTel), "133");
            break;
        case 1:
            strcpy_s(pTel, sizeof(pTel), "155");
            break;
        case 2:
            strcpy_s(pTel, sizeof(pTel), "168");
            break;
        case 3:
            strcpy_s(pTel, sizeof(pTel), "177");
            break;
    }

    //后8位数字随机生成
    for (i = 3; i < 11;i++)
    {
        pTel[i] = rand() % 10 + '0';
    }
    pTel[i] = '\0';
    return pTel;
}
//自动生成通讯录，给了前几个函数srand()
void InitInfo()
{
    int i;
    srand((unsigned int)time(NULL));
    //生成100个通讯录成员
    for (i = 0; i < 100;i++)
    {
        AddNode();
    }
}
//生成关于页码的信息，返回页码的结构体
Page *GetPage()
{
    List *pMark = pHead;
    //初始化页数信息结构体
    Page *pPage = (Page *)malloc(sizeof(Page));
    pPage->OnePageInfo = 10;     //一页显示联络人的个数
    pPage->CurrentPage = 1;      //当前页。这里填打开时展示的那一页
    pPage->TotalInfo = 0;        //初始化总共的联络人个数
    while(pMark != NULL)
    {
        (pPage->TotalInfo)++;
        pMark = pMark->pNext;
    }
    if(pPage->TotalInfo % pPage->OnePageInfo == 0)
    {
        pPage->TotalPage = pPage->TotalInfo / pPage->OnePageInfo;
    }
    else
    {
        pPage->TotalPage = pPage->TotalInfo / pPage->OnePageInfo + 1;
    }
    return pPage;
}
//显示页面
void ShowInfo(Page *pPage)
{
    int begin = (pPage->CurrentPage - 1) * 10 + 1;
    int end = begin + pPage->OnePageInfo - 1;
    int count = 0;
    List *pMark = pHead;
    //遍历链表，显示应该显示的内容
    while(pMark != NULL)
    {
        count++;
        if(count >= begin && count <= end)
        {
            printf("%d\t%s\t%s\n", pMark->id, pMark->name, pMark->tel);
        }
        pMark = pMark->pNext;
    }
    return;
}
//显示菜单信息
void ShowMenu(Page *pPage)
{
    printf("第%d页  共%d页  共%d条  w上一页  s下一页  b返回主菜单\n",pPage->CurrentPage,pPage->TotalPage,
            pPage->TotalInfo);
    return;
}
//翻页功能
void TurnPage(Page *pPage)
{
    //换页
    switch(GetKey())
    {
            case 'w':
                if(pPage->CurrentPage > 1)
                {
                    pPage->CurrentPage -= 1;
                }  
                break;
            case 's':
                if(pPage->CurrentPage < pPage->TotalPage)
                {
                    pPage->CurrentPage += 1;
                }   
                break;
            case 'b':
                printf("通讯录已关闭\n");
                CONTINUEBROWSE = 0;
                break;
            default:
                printf("输入有误，请重试\n");         
    }
    return;
}
//获取输入的字符
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
//浏览页面，结合了整个页面查看功能
void Browse(Page *pPage)
{
    while(1)
    {
        CONTINUEBROWSE = 1;
        ShowInfo(pPage);
        ShowMenu(pPage);
        TurnPage(pPage);
        if(CONTINUEBROWSE != 1)
        {
            free(pPage);
            break;
        }
    }
    return;
}
//获取输入的字符串，并使之储存在一个合理大小的堆区内存里
char *GetString()
{
    int size = 5;
    int count = 0;
    char c;
    char *str = (char *)malloc(size);
    char *newstr = NULL;
    char *pMark = str;              //固定在头部的信标

    while((c = getchar()) != '\n')
    {
        *str = c;
        str++;
        count++;
        if(count + 1 >= size)
        {
            size += 5;
            *str = '\0';
            newstr = (char *)malloc(size);
            strcpy_s(newstr, size, pMark);
            str = newstr + count;
            free(pMark);
            pMark = newstr;
            newstr = NULL;
        }
        *str = '\0';
    }
    return pMark;
}
//手动将节点输入进链表内
List *GetNodeIn()
{
    List *pNodeIn = (List *)malloc(sizeof(List));
    List **ppEnd = &pEnd;          //使用双重指针，才能改变pEnd的值
    pNodeIn->id = GetId();
    printf("请输入新添加联系人的姓名：\n");
    pNodeIn->name = GetString();
    printf("请输入新添加联系人的电话：\n");
    pNodeIn->tel = GetString();
    pNodeIn->pNext = NULL;

    (*ppEnd)->pNext = pNodeIn;
    *ppEnd = pNodeIn;

    return pNodeIn;
}
//通过id删除节点
void DeleteNode()
{
    List **ppHead = &pHead;
    List **ppEnd = &pEnd;
    List *pMark = NULL;
    List *pTemp = *ppHead;
    int id;

    printf("请输入要删除的节点序号：\n");
    id = atoi(GetString());
    //输入内容有误
    if(id == 0)
    {
        printf("输入内容有误，删除节点失败\n");
        return;
    }
    //删除第一个节点
    if(id == pHead->id)
    {
        pMark = pHead;
        *ppHead = (*ppHead)->pNext;
        free(pMark);
        pMark = NULL;
        printf("头节点已删除\n");
        return;
    }
    //删除中间节点
    while((pTemp->pNext->pNext) != NULL)
    {
        if(id == pTemp->pNext->id)
        {
            pMark = pTemp->pNext;
            pTemp->pNext = pTemp->pNext->pNext;
            free(pMark);
            pMark = NULL;
            printf("中间节点已删除\n");
            return;
        }
        pTemp = pTemp->pNext;
    }
    //删除尾节点
    pMark = pTemp->pNext;
    pTemp->pNext = NULL;
    *ppEnd = pTemp;
    free(pMark);
    pMark = NULL;
    printf("最终节点已删除\n");
    return;
}
//查询功能
void Query()
{
    List *pMark = pHead;
    char *pQuery;
    char c = 'a';
    //查询循环
    while(c != 'q')
    {
        printf("请输入您想查询的内容\n");
        pQuery = GetString();      //输入的内容
        while(pMark != NULL)
        {
            if((strncmp(pMark->name,pQuery,strlen(pQuery)) == 0) || (strncmp(pMark->tel,pQuery,strlen(pQuery)) == 0)  )
            {
                printf("%d\t%s\t%s\n", pMark->id, pMark->name, pMark->tel);
            }
            pMark = pMark->pNext;
        }
        pMark = pHead;
        printf("输入q键退出查询，其他任意键继续查询\n");
        c = GetKey();
    }
    return;
}
//修改节点信息
void ChangeInfo()
{
    List *pMark = pHead;
    char *pQuery;
    char c = 'c';
    int id;

    //查询需要修改的内容
    while(c == 'c')
    {
        printf("输入你想修改的内容\n");
        pQuery = GetString();      //输入的内容
        while(pMark != NULL)
        {
            if((strncmp(pMark->name,pQuery,strlen(pQuery)) == 0) || (strncmp(pMark->tel,pQuery,strlen(pQuery)) == 0)  )
            {
                printf("%d\t%s\t%s\n", pMark->id, pMark->name, pMark->tel);
            }
            pMark = pMark->pNext;
        }
        pMark = pHead;
        printf("c键重新检索  其他任意键确认\n");
        c = GetKey();
    }
    //根据序号修改内容
    printf("请输入要修改的节点序号：\n");
    id = atoi(GetString());
    //遍历链表，找到该节点
    while(pMark != NULL)
    {
        if(pMark->id == id)
        {
            printf("请输入修改后的联系人姓名：\n");
            pMark->name = GetString();
            printf("请输入修改后的联系人电话：\n");
            pMark->tel = GetString();
            printf("修改完成。修改结果如下：\n");
            printf("%d\t%s\t%s\n", pMark->id, pMark->name, pMark->tel);
            return;
        }
        pMark = pMark->pNext;
    }
    printf("未找到该联系人，修改失败\n");
    return;
}

void Blank()
{
    char c;
    int delnode;
    int chanode;
    int WORK = 1;
    InitInfo();
    while(WORK == 1)
    {
        printf("1.查看通讯录\n2.添加信息\n3.查询信息\n4.删除信息\n5.修改信息\nq退出\n");
        switch(c = GetKey())
        {   
            case '1':
                printf("===============\n查看通讯录\n===============\n");
                Browse(GetPage());
                break;

            case '2':
                printf("===============\n添加信息\n===============\n");
                GetNodeIn();
                break;

            case '3':
                printf("===============\n查询信息\n===============\n");
                Query();
                break;

            case '4':
                printf("===============\n删除信息\n===============\n");
                delnode = 1;
                while(delnode == 1)
                {
                    DeleteNode();
                    printf("b返回上一级  其他键继续删除联系人\n");
                    if('b' == GetKey())
                        delnode = 0;
                }
                break;

            case '5':
                printf("===============\n修改信息\n===============\n");
                chanode = 1;
                while(chanode == 1)
                {
                    ChangeInfo();
                    printf("b返回上一级  其他键继续修改联系人信息\n");
                    if('b' == GetKey())
                        chanode = 0;
                }
                break;

            case 'q':
                printf("已退出程序\n");
                WORK = 0;
                break;
        }
    }
    return;
}


