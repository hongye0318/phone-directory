#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define INSERT 1
#define QUERY 2
#define LIST 3
#define COMBINE 4
#define DELETE 5
#define QUIT 0

FILE *fp;//�����ļ�ָ��
typedef struct
{
    char name[100];
    char phone[100];
    char mail[100];
    char add[100];
    char qq[100];
}TX;

TX tx1[100]; //��¼ͨѶ¼�����飬���100��
int last=0;  //��ǰͨѶ¼����
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
    int choice;//�û��Ĺ���ѡ��
    init();    //���ļ��ж����ʼ��ͨѶ¼��Ϣ
    while(1)
    {
        showMenu(); //��ʾ�������˵�
        choice=getChoice();//��ȡ�û�����ѡ��
        doChoice(choice);//����ѡ��ִ����Ӧ�Ĺ���
        system("pause>nul");//��ͣ�����û�������������������
    }
    return 0;
}
void init()
{
    int i=0;
    if((fp=fopen("tx1.dat","rb"))==NULL)
    {
        last=0;//�����������ļ���ͨѶ¼Ϊ��
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
void save()//����ͨѶ¼���ļ�tx1.dat��
{
    int i=0;
    if((fp=fopen("tx1.dat","wb"))==NULL)
    {
        printf("���ܴ򿪵绰����Ϣ�ļ�\n");
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
    system("cls");//����DOS����cla����
    printf("******�绰������ϵͳ******\n");
    printf("\t1.������ϵ��\n");
    printf("\t2.������ϵ��\n");
    printf("\t3.�г�������ϵ��\n");
    printf("\t4.�ϲ���ͬ��ϵ��\n");
    printf("\t0.�˳�ϵͳ\n");
    printf("**************\n");
    printf("���������ѡ��");
}

void doQuit()
{
    printf("\n��ӭ�´�ʹ�ã��ټ���");
    exit(0);
}

void doInsert()
{
    printf("��������......\n");
    printf("������");
    scanf("%s",&tx1[last].name);
    printf("�绰��");
    scanf("%s",&tx1[last].phone);
    printf("�����ʼ���");
    scanf("%s",&tx1[last].mail);
    printf("��ַ��");
    scanf("%s",&tx1[last].add);
    printf("QQ��");
    scanf("%s",&tx1[last].qq);
    printf("����ͬѧ�ɹ���\n");
    last++;//�ɹ�����һ��ͬѧ��������1
    save();
}

void doList()
{
        int i,j;
        TX temp;
        printf("ͨѶ¼����%d����ϵ����Ϣ:\n",last);
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
             printf("������%-11s\t",tx1[i].name);
             printf("�绰��%-11s\t",tx1[i].phone);
             printf("�����ʼ���%-20s\t",tx1[i].mail);
             printf("��ַ��%-11s\t",tx1[i].add);
             printf("QQ��%-11s\t",tx1[i].qq);
         }
         printf("*********************\n");
}

void doQuery()
{
    char tname[100];//��ʱ������������
    int i;
    int f=0;  //�ҵ���������ϵ�˵��жϱ�־
    printf("�����ѯ.....\n");
    printf("�������ѯ�ˣ�");
    scanf("%s",&tname);

    for(i=0;i<last&&!f;i++)
    {
        if(!strcmp(tname,tx1[i].name))
        {
            f=1;
            printf("���ҵ���ϵ�˵���Ϣ���£�\n");
            printf("**********************\n");
            printf("������%11s\t",tx1[i].name);
            printf("�绰��%11s\t",tx1[i].phone);
            printf("�����ʼ���%11s\t",tx1[i].mail);
            printf("��ַ��%11s\t",tx1[i].add);
            printf("QQ��%11s\t",tx1[i].qq);
        }
    }
    if(!f)
    {
        printf("δ�ҵ�����ϵ��\n");
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
    printf("���ڴ����%d��ѡ��\n",choice);
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
    printf("������Ҫ�ϲ�����ϵ��....\n");
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
        printf("��Ǹ������ϵ��δ¼��ͨѶ¼��\n");
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
        printf("�ϲ���ϵ�˳ɹ�");
        save();
    }
}
void doDelete()
{
    char tname[100];
    int i;
    int find=0;
    int index;
    printf("����ɾ��.....\n");
    printf("��������ϵ��������");
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
        printf("��Ǹ��δ�ҵ�����ϵ��\n");
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
        printf("����Ϊ%s����ϵ���ѳɹ�ɾ����",tname);
        save();
    }
}
