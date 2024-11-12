//
//  main.cpp
//  B2
//
//  Created by zzr on 2024/11/11.
//

#include <iostream>
#include<stdlib.h>
#include<string.h>
#define count 20

void menu();//主菜单
void read_origin(struct record *item1);//读取源数据文件函数
void read_cost(struct cost *item2);//读取费率文件函数
void read_information(struct user *item4);//读取用户文件函数
void calculat_bill(struct record *item1,struct cost *item2,struct bill *item3);//计算话费函数
void display_bill(struct record *item1,struct bill *item3);//统计通话费用函数
void save_bill(struct record *item1,struct bill *item3);//保存通话费用函数
void search_num(struct record *item1,struct user *item4,struct bill *item3);//通话费用查询函数
void search_paper(struct record *item1,struct user *item4);//通话记录查询函数
void show_origin(struct record *item1);//显示源数据文件函数
void show_cost(struct cost *item2);//显示长话费率文件函数
void show_information(struct user *item4);//显示用户文件函数

struct record{//通话记录结构体，包含：主叫区号，被叫区号，主叫电话号码，被叫电话号码，数据类型，通话时长
     char area_num1[5];
     char area_num2[5];
     char call1[10];
     char call2[10];
     char type[10];
     int  time;
     int Time;
 };

struct cost{//费率结构体，包含：区号，费率
     char area_num[5];
     float money;
 };

struct bill{//费用结构体，包含：本地通话费用，长途通话费用，总通话费用
     float bill_local;
     float bill_long;
     float bill_zong;
 };

struct user{//用户结构体，包含：用户名，电话号码，本地话费，长途话费，总话费
     char name[10];
     char call[10];
     float user_local;
     float user_long;
     float user_zong;
 };


int main()
{
    int choose;
    struct record item1[20];//存放通话记录信息
    struct cost item2[5];//存放费率信息
    struct bill item3[20];//存放话费信息并计费
    struct user item4[20];//存放用户信息
    read_origin(item1);//读取源数据文件
    read_cost(item2);//读取费率文件
    read_information(item4);//读取用户文件
    calculat_bill(item1,item2,item3);//计算话费
    
    
    while(1)
    {
        menu();
        scanf("%d",&choose);
        printf("-----------------------------------------------\n");
        switch(choose)
        {
            case 1:     display_bill(item1,item3);
             break;
         case 2:     save_bill(item1,item3);
             break;
           case 3:     search_num(item1,item4,item3);
            break;
         case 4:     search_paper(item1,item4);
            break;
            case 5:     show_origin(item1);
            break;
         case 6:     show_cost(item2);
            break;
         case 7:     show_information(item4);
            break;
         case 0:     return 0;
            break;
         default:
              printf("请正确输入选项！\n");
        }
    }
    return 0;
}

void menu()
{
    printf(" -------------- 模拟电信计费系统 --------------\n");
    printf(" |               1.统计通话费用               |\n");
    printf(" |               2.保存通话费用               |\n");
    printf(" |               3.通话费用查询               |\n");
    printf(" |               4.通话记录查询               |\n");
    printf(" |               5.显示源数据文件             |\n");
    printf(" |               6.显示长话费率文件           |\n");
    printf(" |               7.显示用户文件               |\n");
    printf(" --------------- 0.退出 -----------------------\n");
    printf("请输入要执行的功能：");
}
//读取源数据文件模块
void read_origin(struct record *item1)
{
    int i;
    FILE *fp;
    fp=fopen("/Users/jiawei/Desktop/software/B2/hd.dat","r");
    for(i=0;i<count;i++)
    {
        fscanf(fp,"%s%s%s%s%d\n",
               item1[i].area_num1,
               item1[i].call1,
               item1[i].area_num2,
               item1[i].call2,
               &item1[i].time);//读取到为int*类型
        //成员依次为：主叫区号、主叫电话号码、被叫区号、被叫电话号码、通话时长（秒）
        item1[i].Time=item1[i].time;
    }
    fclose(fp);
 }
//读取费率文件模块
void read_cost(struct cost *item2)
{
    int i;
    FILE *fp;
    fp=fopen("/Users/jiawei/Desktop/software/B2/fl.dat","r");
    for(i=0;i<4;i++)
    {
        fscanf(fp,"%s%f\n",item2[i].area_num,&item2[i].money);
        //成员依次为：区号、费率
    }
    fclose(fp);
}
//读取用户文件模块
void read_information(struct user *item4)
{
    int i;
    FILE *fp;
    fp=fopen("/Users/jiawei/Desktop/software/B2/yh.dat","r");
    for(i=0;i<5;i++)
    {
        fscanf(fp,"%s%s\n",item4[i].call,&item4[i].name);
        //电话号码、用户姓名
    }
    fclose(fp);
}
//计算话费模块
void calculat_bill(struct record *item1,struct cost *item2,struct bill *item3)
{
    int i,j;
    int k=0;
    int block[20];
    for(i=0;i<count;i++)
    {
        if(strcmp(item1[i].area_num1,item1[i].area_num2)==0)//比较区号是否相等，相等则为本地通话
        {
            item3[i].bill_local = 0.5f + int( (item1[i].time-180)/*超过三分钟的部分*/ *1.0/180+0.5f )*0.2f;//每个成员的本地话费
            //本地电话费为：3分钟及以内0.5元，以后每3分钟”递增“0.2元，第二个3分钟0.7元，第三个3分钟0.9元……
            block[k]=i;//本地通话序号
            k++;
        }
        else//不相等即为长途通话
            for(j=0;j<4;j++)//逐个对比区号
            {
                if(strcmp(item1[i].area_num2,item2[j].area_num)==0)//区号相等，按相应的费率计算
                {
                    item3[i].bill_long = item2[j].money * (int(item1[i].time*1.0/60)+1)/*向上取整*/;
                    //长途电话费＝费率（元/分钟）× 通话时长（分钟）(通话时长不满1分钟按1分钟计算)

                }
            }
    }
    k=0;//清零
    for(i=0;i<count;i++)
    {
        if(block[k]==i)//是一条本地通话
        {
            item3[i].bill_zong=item3[i].bill_local;//计入本地通话费用
            strcpy(item1[i].type,"本地通话");//写入相应的数据类型
            k++;
        }
        else//是一条长途通话
        {
            item3[i].bill_zong=item3[i].bill_long;//计入长途通话费用
            strcpy(item1[i].type,"长途通话");//写入相应的数据类型
        }
    }
}
//统计通话费用模块
void display_bill(struct record *item1,struct bill *item3)
{
    int i;
    printf("主叫电话号码  通话类型   话费金额\n");
    for(i=0;i<count;i++)
    {
        printf("%-10s    %-10s    %.1f\n",item1[i].call1,item1[i].type,item3[i].bill_zong);
    }
    printf("---------------按回车键继续-------------------\n");
    getchar();
    getchar();
}
//保存通话费用模块
void save_bill(struct record *item1,struct bill *item3)
{
    int i;
    FILE *fp;
    fp=fopen("/Users/jiawei/Desktop/software/B2/fy.dat","w");
    if(fp==0)//打开文件失败
    {
        printf("文件打开失败\n");
        exit(1);
    }
    //打开文件成功：
    fprintf(fp,"主叫电话号码  通话类型  话费金额\n");
    for(i=0;i<count;i++)
    {
        fprintf(fp,"%-10s       %-10s    %.1f\n",item1[i].call1,item1[i].type,item3[i].bill_zong);
        
    }
    fclose(fp);
    printf("\n\t已保存到fy.dat文件 \n\n");
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//通话费用查询模块
void search_num(struct record *item1, struct user *item4, struct bill *item3)
{
    int i,j;
    int k=0;
    int flag=0;//
    int flag2=0;//
    int select[count];//存放查询到的号码对应通话记录的序号
    char input_num[10];//存放要查询的电话号码
    printf("请输入要查询的电话号码：");
    scanf("%s",input_num);
    for(i=0;i<count;i++)
    {
        if( strcmp(input_num,item1[i].call1) == 0 )//要查询的号码和数据中的号码相等
        {
            select[k]=i;//存放查询到的记录
            k++;//指向下一个
        }
    }
    for(i=0;i<5;i++)
    {
        if(strcmp(input_num,item4[i].call)==0)//查询对应的用户
        {
            flag=i;//找到对应的人的序号
        }
    }
    for(i=0;i<5;i++)
    {
        if(strcmp(input_num,item4[i].call)!=0)//这次没查到
        {
            flag2++;
        }
    }
    if(flag2 > 4)//查遍了都没有记录
    {
        printf("输入的号码尚无记录！\n");
        printf("---------------按回车键回到菜单----------------\n");
        getchar();
        getchar();
        return;
    }
    //有记录：
    item4[flag].user_local=0;
    item4[flag].user_long=0;//清零
    printf("\n");
    for(j=0;j<k;j++)
    {
        if(strcmp( item1[select[j]].area_num1 , item1[select[j]].area_num2) == 0)//目标号码的主叫区号和被叫区号相等
        {
            item4[flag].user_local+=item3[select[j]].bill_local;//计入相应用户的本地话费
        }
        else//目标号码的区号和被叫区号不相等
        {
            item4[flag].user_long+=item3[select[j]].bill_long;//计入相应用户的长途话费
        }
    }
    printf("用户名  电话号码  本地话费  长途话费  话费总计\n");
    printf("%-7s %-7s       %.1f      %.1f      %.1f\n",
           item4[flag].name,
           item4[flag].call,
           item4[flag].user_local,
           item4[flag].user_long,
           item4[flag].user_local+item4[flag].user_long) ;
    printf("\n");
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//通话记录查询模块
void search_paper(struct record *item1, struct user *item4)
{
    int i;
    int flag;
    int flag2=0;
    char input_num[10];
    int select[count];
    int k=0;//相应记录的数量
    printf("请输入要查询的电话号码：");
    scanf("%s",input_num);
    for(i=0;i<5;i++)
    {
        if(strcmp(input_num,item4[i].call)==0)
        {
            flag=i;
        }
    }
    for(i=0;i<count;i++)
    {
        if(strcmp(input_num,item1[i].call1)==0)
        {
            select[k]=i;
            k++;
        }
    }
    for(i=0;i<5;i++)
    {
        if(strcmp(input_num,item4[i].call)!=0)
        {
            flag2++;
        }
    }
    if(flag2>4)//没有记录
    {
        printf("输入的号码尚无记录！\n");
        printf("---------------按回车键回到菜单----------------\n");
        getchar();
        getchar();
        return;
    }
    //有记录
    printf("用户名  主叫电话号码  被叫电话号码  通话时长\n");
    for(i=0;i<k;i++)//同上一个的理，名字引用同样的，记录引用值依次遍历
    {
        printf("%-7s    %-7s     %-8s     %-4d\n",
               item4[flag].name,
               item1[select[i]].call1,
               item1[select[i]].call2,
               item1[select[i]].Time) ;
    }
    printf("\n");
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//显示源数据文件模块
void show_origin(struct record *item1)
{
    int i;
    printf("主叫区号   主叫电话号码      被叫区号       被叫电话号码     通话时长（秒）\n");
    for(i=0;i<count;i++)
    {
        printf(" %-10s %-15s %-10s %-15s %-5d\n",
               item1[i].area_num1,
               item1[i].call1,
               item1[i].area_num2,
               item1[i].call2,
               item1[i].Time) ;
    }
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
 }
//显示长话费率文件模块
void show_cost(struct cost *item2)
{
    int i;
    printf("区号      费率\n");
    for(i=0;i<4;i++)
    {
        printf("%-10s%-1.2f\n",item2[i].area_num,item2[i].money);
    }
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//显示用户文件
void show_information(struct user *item4)
{
    int i;
    printf("电话号码   用户姓名\n");
    for(i=0;i<5;i++)
    {
        printf("%-11s%-10s\n",item4[i].call,item4[i].name);
    }
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}




