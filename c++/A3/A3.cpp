//
//  main.cpp
//  A3
//
//  Created by zzr on 2024/11/11.
//

#include <iostream>
#include <stdlib.h>
void menu();
void new_edit();
void open();//各功能函数的声明
int main()
{
    menu();
    return 0;
}
void menu()
{
    printf("1.打开文本\n");
    printf("2.增加新文本\n");
    printf("3.退出\n");
    printf("请输入要执行的功能：");
    int choose;
    scanf("%d",&choose);
    switch(choose)
    {
    case 1: open();
        break;
    case 2: new_edit();
        break;
    case 3: exit(0);
        break;
    default:
        printf("请输入正确序号\n");
    }
}
void new_edit()//新建
{
    char ch;
    FILE *fp=0;
    char filename[50];
    char wenben[10000];
    int i=0;
    int j=0;
    printf("请输入文本内容(以#结束)\n");
    while((ch=getchar())!='#')
    {
        wenben[i++]=ch;//字长
    }
    getchar();
    printf("请输入需要保存的文件名及路径：");
    scanf("%s",filename);
    fp=fopen(filename,"w+");//打开
    getchar();
    for(j=0;j<i;j++)
        putc(wenben[j],fp);//写入
    printf("\n新文件已保存!现文件内容如下：\n");
    rewind(fp);//返回写入的信息
    do
    {
        ch=getc(fp);
        putchar(ch);
    }while(ch!=EOF);
    putchar('\n');
    fclose(fp);//关闭
    
}
void open()//打开
{
    char ch;
    FILE *fp;
    int i=0;
    int j=0;
    char filename[50];
    char wenben[10000];
    printf("请输入需要打开的文件名及路径：");
    scanf("%s",filename);
    fp=fopen(filename,"a+");
    getchar();
    if(!fp)//路径错误
    {
        printf("文件无法打开\n");
    }
    //system("cls");
    while((ch=fgetc(fp))!=EOF)
    {
        putchar(ch);
    }
    printf("\n");
       int xuanze;
    printf("1.继续编辑此文本   2.重新编辑此文本   3.回到主菜单   4.退出\n");
    printf("请选择下一步操作：");
    scanf("%d",&xuanze);
    if(xuanze==4)
        exit(0);
    else if(xuanze==3)
        menu();
    else if(xuanze==2)//原理同新建
    {
        i=0;
        //system("cls");
        fclose(fp);
        fp=fopen(filename,"w+");
        printf("请输入内容(以#结束)\n");
        while((ch=getchar())!='#')
        {
             wenben[i++]=ch;
        }
        getchar();
    }
    else if(xuanze==1)
    {
        i=0;
        system("cls");
        printf("请输入内容(以#结束)\n");
        rewind(fp);
        do
        {
            ch=getc(fp);
            putchar(ch);
        }while(ch!=EOF);
        fseek(fp,sizeof(EOF),SEEK_END);
    
        while((ch=getchar())!='#')
        {
            wenben[i++]=ch;
        }
        getchar();
    }
    else
        printf("请正确输入选项");
        printf("是否保存新文档？1.是   2.否，退出程序\n");
        int xuanze2;
        scanf("%d",&xuanze2);
        if(xuanze2==2)
            exit(0);
        else
            for(j=0;j<i;j++)
                putc(wenben[j],fp);
            printf("\n新文件已保存!现文件内容如下：\n");
            rewind(fp);
        do
        {
            ch=getc(fp);
            putchar(ch);
        }while(ch!=EOF);
        putchar('\n');
        fclose(fp);
}


