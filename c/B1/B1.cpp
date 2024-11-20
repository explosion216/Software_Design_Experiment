//
//  P22000820-B1.cpp
//  B1
//
//  Created by 张哲瑞 on 2024/11/11.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>

// 学生结构体
struct student {
    char num[7];        // 学号
    float score1;       // 平时成绩
    float score2;       // 期中成绩
    float score3;       // 期末成绩
    float zong_score;   // 总评成绩
    char rank;          // 成绩等级
};

// 函数声明
void menu();
int read_dat(struct student* item);
void calculate_zong(struct student* item, int count);
void calculate_average(struct student* item, int count);
void calculate_situtation(struct student* item, int count);
void area_divide(struct student* item, int count);
void output_dat(struct student* item, int count);

// 主函数
int main()
{
    int choose;
    int count = 0;
    struct student item[20];
    while (1)
    {
        menu();
        if (scanf_s("%d", &choose) != 1) { // 使用安全输入函数 scanf_s
            printf("输入错误，请输入数字！\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }
        switch (choose)
        {
        case 1: count = read_dat(item); break;
        case 2: calculate_zong(item, count); break;
        case 3: calculate_average(item, count); break;
        case 4: calculate_situtation(item, count); break;
        case 5: area_divide(item, count); break;
        case 6: output_dat(item, count); break;
        case 0: return 0;
        default: printf("请正确输入选项！\n");
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

// 读取学生成绩模块
int read_dat(struct student* item)
{
    int n = 0;
    FILE* fp;
    errno_t err = fopen_s(&fp, "C:\\Users\\Administrator\\Desktop\\P22000820-张哲瑞-软件设计\\note.dat", "r"); // 使用安全函数 fopen_s
    if (err != 0 || fp == nullptr) {
        printf("文件打开失败，请检查文件路径和名称。\n");
        return 0;
    }

    fscanf_s(fp, "%d", &n); // 读取学生总人数
    for (int i = 0; i < n; i++)
    {
        fscanf_s(fp, "%s %f %f %f", item[i].num, (unsigned)_countof(item[i].num),
            &item[i].score1, &item[i].score2, &item[i].score3); // 读取学生信息
    }

    printf("\t学号  平时成绩 期中成绩 期末成绩\n");
    for (int i = 0; i < n; i++)
    {
        printf("\t%s\t%5.1f\t%5.1f\t%5.1f\n", item[i].num, item[i].score1, item[i].score2, item[i].score3);
    }
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar(); getchar();
    fclose(fp);
    return n;
}

// 计算总评成绩模块
void calculate_zong(struct student* item, int count)
{
    printf("\t学号  总评成绩\n");
    for (int i = 0; i < count; i++)
    {
        item[i].zong_score = item[i].score1 * 0.3f + item[i].score2 * 0.3f + item[i].score3 * 0.4f;
        printf("\t%s\t%5.1f\n", item[i].num, item[i].zong_score);
    }
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar(); getchar();
}

// 计算平均成绩模块
void calculate_average(struct student* item, int count)
{
    float sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += item[i].zong_score;
    }
    float ave = sum / count;
    printf("\n本次考试 %d 人参加      总分：%5.1f      平均分：%5.1f\n", count, sum, ave);
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar(); getchar();
}

// 计算总评情况模块
void calculate_situtation(struct student* item, int count)
{
    int count_you = 0, count_liang = 0, count_zhong = 0, count_ji = 0, count_bu = 0;
    for (int i = 0; i < count; i++)
    {
        if (item[i].zong_score >= 90) { item[i].rank = 'A'; count_you++; }
        else if (item[i].zong_score >= 80) { item[i].rank = 'B'; count_liang++; }
        else if (item[i].zong_score >= 70) { item[i].rank = 'C'; count_zhong++; }
        else if (item[i].zong_score >= 60) { item[i].rank = 'D'; count_ji++; }
        else { item[i].rank = 'E'; count_bu++; }
    }

    printf("优的学生有 %d 人，占总人数的 %.1f%%\n", count_you, count_you * 100.0 / count);
    printf("良的学生有 %d 人，占总人数的 %.1f%%\n", count_liang, count_liang * 100.0 / count);
    printf("中的学生有 %d 人，占总人数的 %.1f%%\n", count_zhong, count_zhong * 100.0 / count);
    printf("及格的学生有 %d 人，占总人数的 %.1f%%\n", count_ji, count_ji * 100.0 / count);
    printf("不及格的学生有 %d 人，占总人数的 %.1f%%\n", count_bu, count_bu * 100.0 / count);
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar(); getchar();
}

// 显示学生情况模块
void area_divide(struct student* item, int count)
{
    printf("       学生学号   总评成绩  成绩等级\n");

    printf("  优：\n");
    for (int i = 0; i < count; i++)
    {
        if (item[i].rank == 'A') {
            printf("\t%s\t%5.1f\t%c\n", item[i].num, item[i].zong_score, item[i].rank);
        }
    }

    printf("  良：\n");
    for (int i = 0; i < count; i++)
    {
        if (item[i].rank == 'B') {
            printf("\t%s\t%5.1f\t%c\n", item[i].num, item[i].zong_score, item[i].rank);
        }
    }

    printf("  中：\n");
    for (int i = 0; i < count; i++)
    {
        if (item[i].rank == 'C') {
            printf("\t%s\t%5.1f\t%c\n", item[i].num, item[i].zong_score, item[i].rank);
        }
    }

    printf(" 及格：\n");
    for (int i = 0; i < count; i++)
    {
        if (item[i].rank == 'D') {
            printf("\t%s\t%5.1f\t%c\n", item[i].num, item[i].zong_score, item[i].rank);
        }
    }

    printf(" 不及格：\n");
    for (int i = 0; i < count; i++)
    {
        if (item[i].rank == 'E') {
            printf("\t%s\t%5.1f\t%c\n", item[i].num, item[i].zong_score, item[i].rank);
        }
    }
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar(); getchar();
}

// 保存学生评定模块
void output_dat(struct student* item, int count)
{
    FILE* fp;
    errno_t err = fopen_s(&fp, "C:\\Users\\Administrator\\Desktop\\P22000820-张哲瑞-软件设计\\out.dat", "w"); // 使用安全函数 fopen_s
    if (err != 0 || fp == nullptr) {
        printf("文件保存失败，请检查文件路径和权限。\n");
        return;
    }

    fprintf(fp, "\t学号\t总评\t等级\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "\t%s\t%5.1f\t%c\n", item[i].num, item[i].zong_score, item[i].rank); // 保存评定结果
    }

    fclose(fp);
    printf("\n\t已保存到 out.dat 文件\n\n");
    printf(" --------------按回车键回到菜单--------------- \n");
    getchar(); getchar();
}