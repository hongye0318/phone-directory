#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define INSERT 1
#define QUERY 2
#define LIST 3
#define COMBINE 4
#define DELETE 5
#define QUIT 0

FILE *fp;//定义文件指针
typedef struct
{
    char name[100];
    char phone[100];
    char mail[100];
    char add[100];
    char qq[100];
}TX;

TX tx1[100]; //记录通讯录的数组，最多100人
int last=0;  //当前通讯录人数
void showMenu();
void doChoice(int);
int getChoice();
void save();
void doInsert();
void doList();
void doQuery();
void doQuit();
void init();
void doCombine();
void doDelete();
int main()
{
    int choice;//用户的功能选择
    init();    //从文件中读入初始化通讯录信息
    while(1)
    {
        showMenu(); //显示功能主菜单
        choice=getChoice();//获取用户功能选择
        doChoice(choice);//根据选择执行相应的功能
        system("pause>nul");//暂停，让用户看清楚，按任意键继续
    }
    return 0;
}
void init()
{
    int i=0;
    if((fp=fopen("tx1.dat","rb"))==NULL)
    {
        last=0;//不存在数据文件，通讯录为空
    }
    else
    {
        while(!feof(fp))
        {
            if(fread(&tx1[i],sizeof(TX),1,fp)==1)
            {
                i++;
            }
        }
        last=i;
    }
    fclose(fp);
}
void save()//保存通讯录到文件tx1.dat中
{
    int i=0;
    if((fp=fopen("tx1.dat","wb"))==NULL)
    {
        printf("不能打开电话簿信息文件\n");
        exit(0);
    }
    while(i<last)
    {
     fwrite(&tx1[i],sizeof(TX),1,fp);
     i++;
    }
    fclose(fp);
}
void showMenu()
{
    system("cls");//调用DOS命令cla清屏
    printf("******电话簿管理系统******\n");
    printf("\t1.增加联系人\n");
    printf("\t2.查找联系人\n");
    printf("\t3.列出所有联系人\n");
    printf("\t4.合并相同联系人\n");
    printf("\t0.退出系统\n");
    printf("**************\n");
    printf("请输入你的选择：");
}

void doQuit()
{
    printf("\n欢迎下次使用，再见！");
    exit(0);
}

void doInsert()
{
    printf("处理增加......\n");
    printf("姓名：");
    scanf("%s",&tx1[last].name);
    printf("电话：");
    scanf("%s",&tx1[last].phone);
    printf("电子邮件：");
    scanf("%s",&tx1[last].mail);
    printf("地址：");
    scanf("%s",&tx1[last].add);
    printf("QQ：");
    scanf("%s",&tx1[last].qq);
    printf("增加同学成功！\n");
    last++;//成功增加一名同学，人数加1
    save();
}

void doList()
{
        int i,j;
        TX temp;
        printf("通讯录共有%d个联系人信息:\n",last);
        for(i=0;i<last-1;i++)
        {
            for(j=i;j<last;j++)
            {
                if(strcmp(tx1[i].name,tx1[j].name)>0)
                {
                    temp=tx1[i];
                    tx1[i]=tx1[j];
                    tx1[j]=temp;
                }
            }
        }
         for(i=0;i<last;i++)
         {
             printf("*********************\n");
             printf("姓名：%-11s\t",tx1[i].name);
             printf("电话：%-11s\t",tx1[i].phone);
             printf("电子邮件：%-20s\t",tx1[i].mail);
             printf("地址：%-11s\t",tx1[i].add);
             printf("QQ：%-11s\t",tx1[i].qq);
         }
         printf("*********************\n");
}

void doQuery()
{
    char tname[100];//临时存放输入的姓名
    int i;
    int f=0;  //找到所查找联系人的判断标志
    printf("处理查询.....\n");
    printf("请输入查询人：");
    scanf("%s",&tname);

    for(i=0;i<last&&!f;i++)
    {
        if(!strcmp(tname,tx1[i].name))
        {
            f=1;
            printf("你找的联系人的信息如下：\n");
            printf("**********************\n");
            printf("姓名：%11s\t",tx1[i].name);
            printf("电话：%11s\t",tx1[i].phone);
            printf("电子邮件：%11s\t",tx1[i].mail);
            printf("地址：%11s\t",tx1[i].add);
            printf("QQ：%11s\t",tx1[i].qq);
        }
    }
    if(!f)
    {
        printf("未找到该联系人\n");
    }
}

int getChoice()
{
    int choice;
    scanf("%d",&choice);
    return choice;
}

void doChoice(int choice)
{
    printf("正在处理第%d个选择\n",choice);
    switch(choice)
    {
    case INSERT:
        doInsert();
        break;
    case QUERY:
        doQuery();
        break;
    case LIST:
        doList();
        break;
    case COMBINE:
        doCombine();
        break;
    case DELETE:
        doDelete();
        break;
    case QUIT:
        doQuit();
    }
}

void doCombine()
{
    char tname[100];
    int i;
    int find=0;
    int index;
    printf("请输入要合并的联系人....\n");
    scanf("%s",&tname);
    for(i=0;i<last&&!find;i++)
    {
        if(!strcmp(tname,tx1[i].name))
        {
            find=1;
            index=i;
            break;
        }
    }
    if(!find)
    {
        printf("抱歉，该联系人未录入通讯录中\n");
    }
    else
    {
        for(i=index+1;i<=last;i++)
        {
            if(!strcmp(tname,tx1[i].name))
            {
                strcpy(tx1[i].name,tx1[i+1].name);
                strcpy(tx1[i].phone,tx1[i+1].phone);
                strcpy(tx1[i].mail,tx1[i+1].mail);
                strcpy(tx1[i].add,tx1[i+1].add);
                strcpy(tx1[i].qq,tx1[i+1].qq);
            }
            last--;
        }
        printf("合并联系人成功");
        save();
    }
}
void doDelete()
{
    char tname[100];
    int i;
    int find=0;
    int index;
    printf("处理删除.....\n");
    printf("请输入联系人姓名：");
    scanf("%s",&tname);
    for(i=0;i<last&&!find;i++)
    {
        if(!strcmp(tname,tx1[i].name))
        {
            find=1;
            index=i;
            break;
        }
    }
    if(!find)
    {
        printf("抱歉，未找到该联系人\n");
    }
    else
    {
        for(i=index;i<=last;i++)
        {
            strcpy(tx1[i].name,tx1[i+1].name);
            strcpy(tx1[i].phone,tx1[i+1].phone);
            strcpy(tx1[i].mail,tx1[i+1].mail);
            strcpy(tx1[i].add,tx1[i+1].add);
            strcpy(tx1[i].qq,tx1[i+1].qq);
        }
        last--;
        printf("姓名为%s的联系人已成功删除！",tname);
        save();
    }
}
