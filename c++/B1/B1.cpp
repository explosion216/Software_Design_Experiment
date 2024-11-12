//
//  main.cpp
//  B1
//
//  Created by zzr on 2024/11/11.
//

#include <iostream>
#include<string.h>
#include<stdlib.h>
void menu();//显示菜单
int read_dat(struct student *item);//读成绩
void calculate_zong(struct student *item,int count);//计算总分
void calculate_average(struct student *item,int count);//计算平均分
void calculate_situtation(struct student *item,int count);//计算总评
void area_divide(struct student *item,int count);//显示学生情况
void output_dat(struct student *item,int count);//保存（输出）评定

struct student{//学生结构体，包括姓名（学号），平时成绩，期中成绩，期末成绩，总分，等级
     char num[6];
     float score1,score2,score3;
     float zong_score;
     char rank;
 }stu;

int main()
{
    int choose;
    int count=0;
    struct student item[20];
    while(1)
    {
        menu();
        scanf("%d",&choose);
        switch(choose)
        {
         case 1: count=read_dat(item);
             break;
         case 2: calculate_zong(item,count);
             break;
           case 3: calculate_average(item,count);
            break;
         case 4: calculate_situtation(item,count);
            break;
            case 5: area_divide(item,count);
            break;
         case 6: output_dat(item,count);
            break;
         case 0:
            return 0;
         default:
              printf("请正确输入选项！\n");
        }
    }
    return 0;
}

void menu()
{
    printf(" -------------- 学生成绩核算系统 -------------- \n");
    printf(" |              1.读取学生成绩                | \n");
    printf(" |              2.计算总评成绩                | \n");
    printf(" |              3.计算平均成绩                | \n");
    printf(" |              4.计算总评情况                | \n");
    printf(" |              5.显示学生情况                | \n");
    printf(" |              6.保存学生评定                | \n");
    printf(" ----------------- 0.退出 --------------------- \n");
    printf("请输入要执行的功能：");
}
//读取学生成绩模块：
int read_dat(struct student *item)
{
    int n;
    int i;
    FILE *fp;
    fp=fopen("/Users/jiawei/Desktop/software/B1/note.dat","r");
    fscanf(fp,"%d",&n);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%s%f%f%f\n",item[i].num,&item[i].score1,&item[i].score2,&item[i].score3);//从文件读入学生成绩到结构体数组
    }
    printf("\t学号  平时成绩 期中成绩 期末成绩\n");
    for(i=0;i<n;i++)
    {
        printf("\t%s\t%5.1lf\t%5.1lf\t%5.1lf\n",item[i].num,item[i].score1,item[i].score2,item[i].score3);
    }
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar();
    getchar();
    fclose(fp);//关闭
    return n;
 }
//计算总评成绩模块
void calculate_zong(struct student *item,int count)
{
    int i;
    printf("\t学号  总评成绩\n");
    for(i=0;i<count;i++)
    {
        item[i].zong_score=item[i].score1*0.3f+item[i].score2*0.3f+item[i].score3*0.4f;//平时成绩，期中成绩，期末成绩占比依次为30%，30%，40%
        printf("\t%s\t%5.1lf\n",item[i].num,item[i].zong_score);
    }
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar();
    getchar();
}
//计算平均成绩模块
void calculate_average(struct student *item,int count)
{
    int i;
    float sum=0;
    float ave=0;
    for(i=0;i<count;i++)
    {
        sum+=item[i].zong_score;//累加
    }
    ave=sum/count;
    printf("\n");
    printf("本次考试 %d 人参加      总分：%2.1lf      平均分：%2.1lf\n",count,sum,ave);
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar();
    getchar();
}

void calculate_situtation(struct student *item,int count)
{
    int i=0;
    int count_you=0;//优（A）为90分及以上
    int count_liang=0;//良（B）为80-89分
    int count_zhong=0;//中（C）为70-79分
    int count_ji=0;//及格（D）为60-69分
    int count_bu=0;//不及格（E）为60分以下
    for(i=0;i<count;i++)//多层if-else记录相应分数段人数
    {
        if(item[i].zong_score>=90)
        {
            item[i].rank='A';
            count_you++;
        }
        else if(item[i].zong_score>=80)
        {
            item[i].rank='B';
            count_liang++;
        }
        else if(item[i].zong_score>=70)
        {
            item[i].rank='C';
            count_zhong++;
        }
        else if(item[i].zong_score>=60)
        {
            item[i].rank='D';
            count_ji++;
        }
        else
        {
            item[i].rank='E';
            count_bu++;
        }
    }
    printf("本次考试处于   优   的学生有 %d 人，占总人数的%.1lf%%\n",count_you,count_you*100.0/count);
    printf("本次考试处于   良   的学生有 %d 人，占总人数的%.1lf%%\n",count_liang,count_liang*100.0/count);
    printf("本次考试处于   中   的学生有 %d 人，占总人数的%.1lf%%\n",count_zhong,count_zhong*100.0/count);
    printf("本次考试处于  及格  的学生有 %d 人，占总人数的%.1lf%%\n",count_ji,count_ji*100.0/count);
    printf("本次考试处于 不及格 的学生有 %d 人，占总人数的%.1lf%%\n",count_bu,count_bu*100.0/count);
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar();
    getchar();
}

//显示学生情况模块
void area_divide(struct student *item,int count)
{
    int i;
    printf("       学生学号   总评成绩  成绩等级\n");

    printf("  优：\n");
    for(i=0;i<count;i++)
    {
        if(item[i].zong_score>=90)//遍历到符合条件的学生
        {
            printf("\t%s\t  %5.1lf\t      %c\n",item[i].num,item[i].zong_score,item[i].rank);
        }
    }
    printf("\n");

    printf("  良：\n");
    for(i=0;i<count;i++)
    {
        if(item[i].zong_score>=80&&item[i].zong_score<90)
        {
            printf("\t%s\t  %5.1lf\t      %c\n",item[i].num,item[i].zong_score,item[i].rank);
        }
    }
    printf("\n");

    printf("  中：\n");
    for(i=0;i<count;i++)
    {
        if(item[i].zong_score>=70&&item[i].zong_score<80)
        {
            printf("\t%s\t  %5.1lf\t      %c\n",item[i].num,item[i].zong_score,item[i].rank);
        }
    }
    printf("\n");

    printf(" 及格：\n");
    for(i=0;i<count;i++)
    {
        if(item[i].zong_score>=60&&item[i].zong_score<70)
        {
            printf("\t%s\t  %5.1lf\t      %c\n",item[i].num,item[i].zong_score,item[i].rank);
        }
    }
    printf("\n");

    printf("不及格：\n");
    for(i=0;i<count;i++)
    {
        if(item[i].zong_score<60)
        {
            printf("%s\t  %5.1lf\t      %c\n",item[i].num,item[i].zong_score,item[i].rank);
        }
    }
    printf("\n");
        
   
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar();
    getchar();
}

//保存学生评定模块
void output_dat(struct student *item,int count)
{
    int i;
    FILE *fp;
    fp = fopen("/Users/jiawei/Desktop/software/B1/out.dat","w");//打开事先建立好的空文件
    if(fp==0)
    {
        printf("文件打开失败\n");
        exit(1);
    }
    fprintf(fp,"\t\t学号\t总评\t等级\n");
    for(i=0;i<count;i++)
    {
        fprintf(fp,"\t\t%s\t%5.1f\t%c\n",item[i].num,item[i].zong_score,item[i].rank);//将学生结构体数组的内容依次写入
    }
    fclose(fp);
    printf("\n\t已保存到out.dat文件 \n\n");
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar();
    getchar();
}


