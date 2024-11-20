//
//  P22000820-B2.cpp
//  B2
//
//  Created by 张哲瑞 on 2024/11/11.
//

#include <iostream>
#include<stdlib.h>
#include<string.h>
#define count 20

void menu();//主菜单
void read_origin(struct record* item1);//读取源数据文件函数
void read_cost(struct cost* item2);//读取费率文件函数
void read_information(struct user* item4);//读取用户文件函数
void calculat_bill(struct record* item1, struct cost* item2, struct bill* item3);//计算话费函数
void display_bill(struct record* item1, struct bill* item3);//统计通话费用函数
void save_bill(struct record* item1, struct bill* item3);//保存通话费用函数
void search_num(struct record* item1, struct user* item4, struct bill* item3);//通话费用查询函数
void search_paper(struct record* item1, struct user* item4);//通话记录查询函数
void show_origin(struct record* item1);//显示源数据文件函数
void show_cost(struct cost* item2);//显示长话费率文件函数
void show_information(struct user* item4);//显示用户文件函数

struct record {//通话记录结构体，包含：主叫区号，被叫区号，主叫电话号码，被叫电话号码，数据类型，通话时长
    char area_num1[5];
    char area_num2[5];
    char call1[10];
    char call2[10];
    char type[10];
    int  time;
    int Time;
};

struct cost {//费率结构体，包含：区号，费率
    char area_num[5];
    float money;
};

struct bill {//费用结构体，包含：本地通话费用，长途通话费用，总通话费用
    float bill_local;
    float bill_long;
    float bill_zong;
};

struct user {//用户结构体，包含：用户名，电话号码，本地话费，长途话费，总话费
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
    struct user item4[10];//存放用户信息
    read_origin(item1);//读取源数据文件
    read_cost(item2);//读取费率文件
    read_information(item4);//读取用户文件
    calculat_bill(item1, item2, item3);//计算话费


    while (1)
    {
        menu();
        scanf_s("%d", &choose);
        printf("-----------------------------------------------\n");
        switch (choose)
        {
        case 1:     display_bill(item1, item3);
            break;
        case 2:     save_bill(item1, item3);
            break;
        case 3:     search_num(item1, item4, item3);
            break;
        case 4:     search_paper(item1, item4);
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
// 读取源数据文件模块
void read_origin(struct record* item1)
{
    FILE* fp = nullptr;
    errno_t err = fopen_s(&fp, "C://Users//Administrator//Desktop//P22000820-张哲瑞-软件设计//hd.dat", "r");
    if (err != 0 || fp == nullptr) {
        printf("无法打开源数据文件，请检查路径。\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fscanf_s(fp, "%4s %9s %4s %9s %d",
            item1[i].area_num1, (unsigned)_countof(item1[i].area_num1),
            item1[i].call1, (unsigned)_countof(item1[i].call1),
            item1[i].area_num2, (unsigned)_countof(item1[i].area_num2),
            item1[i].call2, (unsigned)_countof(item1[i].call2),
            &item1[i].time);
        item1[i].Time = item1[i].time;
    }
    fclose(fp);
}
// 读取费率文件模块
void read_cost(struct cost* item2)
{
    FILE* fp = nullptr;
    errno_t err = fopen_s(&fp, "C://Users//Administrator//Desktop//P22000820-张哲瑞-软件设计//fl.dat", "r");
    if (err != 0 || fp == nullptr) {
        printf("无法打开费率文件，请检查路径。\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++) {
        fscanf_s(fp, "%4s %f", item2[i].area_num, (unsigned)_countof(item2[i].area_num), &item2[i].money);
    }
    fclose(fp);
}
// 读取用户文件模块
void read_information(struct user* item4)
{
    FILE* fp = nullptr;
    errno_t err = fopen_s(&fp, "C://Users//Administrator//Desktop//P22000820-张哲瑞-软件设计//yh.dat", "r");
    if (err != 0 || fp == nullptr) {
        printf("无法打开用户文件，请检查路径。\n");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        fscanf_s(fp, "%9s %10s", item4[i].call, (unsigned)_countof(item4[i].call), item4[i].name, (unsigned)_countof(item4[i].name));
    }
    fclose(fp);
}
//计算话费模块
void calculat_bill(struct record* item1, struct cost* item2, struct bill* item3)
{
    int i, j;
    int k = 0;
    float temp = 0.0;
    int block[20] = { 0 };

    for (i = 0; i < count; i++)
    {
        if (strcmp(item1[i].area_num1, item1[i].area_num2) == 0) // 比较区号是否相等，相等则为本地通话
        {
            temp = 0.0;
            item3[i].bill_local = 0.0;
                while (item1[i].time > temp * 180)
                {
                    item3[i].bill_local += 0.5f + temp * 0.2f;
                        temp++;
                }
            block[k] = i; // 记录本地通话序号
            k++;
        }
        else // 不相等即为长途通话
        {
            for (j = 0; j < 4; j++) // 逐个对比区号
            {
                if (strcmp(item1[i].area_num2, item2[j].area_num) == 0) // 区号相等，按相应的费率计算
                {
                    item3[i].bill_long = item2[j].money * (int(item1[i].time * 1.0 / 60) + 1); // 向上取整
                    break;
                }
            }
        }
    }

    k = 0; // 重置计数器
    for (i = 0; i < count; i++)
    {
        if (block[k] == i) // 是一条本地通话
        {
            item3[i].bill_zong = item3[i].bill_local; // 计入本地通话费用
            strcpy_s(item1[i].type, "本地通话"); // 写入相应的数据类型
            k++;
        }
        else // 是一条长途通话
        {
            item3[i].bill_zong = item3[i].bill_long; // 计入长途通话费用
            strcpy_s(item1[i].type, "长途通话"); // 写入相应的数据类型
        }
    }
}
//统计通话费用模块
void display_bill(struct record* item1, struct bill* item3)
{
    int i;
    printf("主叫电话号码  通话类型   话费金额\n");
    for (i = 0;i < count;i++)
    {
        printf("%-10s    %-10s    %.1f\n", item1[i].call1, item1[i].type, item3[i].bill_zong);
    }
    printf("---------------按回车键继续-------------------\n");
    getchar();
    getchar();
}
// 保存通话费用模块
void save_bill(struct record* item1, struct bill* item3)
{
    FILE* fp = nullptr;
    errno_t err = fopen_s(&fp, "C://Users//Administrator//Desktop//P22000820-张哲瑞-软件设计//fy.dat", "w");
    if (err != 0 || fp == nullptr) {
        printf("无法打开费用文件，请检查路径。\n");
        exit(1);
    }

    fprintf(fp, "主叫电话号码  通话类型  话费金额\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%-10s       %-10s    %.1f\n", item1[i].call1, item1[i].type, item3[i].bill_zong);
    }

    fclose(fp);
    printf("\n\t已保存到 fy.dat 文件\n\n");
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//通话费用查询模块
void search_num(struct record* item1, struct user* item4, struct bill* item3)
{
    int i, j;
    int k = 0;
    int flag = 0;
    int flag2 = 0;
    int select[count] = { 0 };
    char input_num[10]; // 存放要查询的电话号码

    printf("请输入要查询的电话号码：");
    scanf_s("%s", input_num, (unsigned)_countof(input_num));

    // 查找通话记录中匹配的号码
    for (i = 0; i < count; i++)
    {
        if (strcmp(input_num, item1[i].call1) == 0) // 要查询的号码和数据中的号码相等
        {
            select[k] = i; // 存放查询到的记录
            k++; // 指向下一个
        }
    }

    // 查找用户文件中是否存在该号码
    for (i = 0; i < 5; i++)
    {
        if (strcmp(input_num, item4[i].call) == 0) // 查询对应的用户
        {
            flag = i; // 找到对应的人的序号
            break;
        }
    }

    // 如果未找到记录
    if (k == 0) // 通话记录中没有找到
    {
        printf("输入的号码尚无记录！\n");
        printf("---------------按回车键回到菜单----------------\n");
        getchar();
        getchar();
        return;
    }

    // 有记录，统计费用
    item4[flag].user_local = 0;
    item4[flag].user_long = 0; // 清零
    for (j = 0; j < k; j++)
    {
        if (strcmp(item1[select[j]].area_num1, item1[select[j]].area_num2) == 0) // 本地通话
        {
            item4[flag].user_local += item3[select[j]].bill_local; // 累加本地话费
        }
        else // 长途通话
        {
            item4[flag].user_long += item3[select[j]].bill_long; // 累加长途话费
        }
    }

    // 输出结果
    printf("用户名  电话号码  本地话费  长途话费  话费总计\n");
    printf("%-10s %-7s       %.1f      %.1f      %.1f\n",
        item4[flag].name,
        item4[flag].call,
        item4[flag].user_local,
        item4[flag].user_long,
        item4[flag].user_local + item4[flag].user_long);
    printf("\n");
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//通话记录查询模块
void search_paper(struct record* item1, struct user* item4)
{
    int i;
    int flag = -1; // 初始化为-1，表示未找到用户
    int flag2 = 0; // 未找到记录的计数器
    char input_num[10]; // 存放要查询的电话号码
    int select[count] = { 0 };
    int k = 0; // 相应记录的数量

    printf("请输入要查询的电话号码：");
    scanf_s("%s", input_num, (unsigned)_countof(input_num));

    // 查找用户文件中是否存在该号码
    for (i = 0; i < 5; i++)
    {
        if (strcmp(input_num, item4[i].call) == 0)
        {
            flag = i; // 找到对应的人的序号
            break;
        }
    }

    // 查找通话记录中匹配的号码
    for (i = 0; i < count; i++)
    {
        if (strcmp(input_num, item1[i].call1) == 0)
        {
            select[k] = i; // 存放查询到的记录
            k++; // 增加匹配记录计数
        }
    }

    // 如果用户文件中没有找到号码或没有匹配的通话记录
    if (flag == -1 || k == 0)
    {
        printf("输入的号码尚无记录！\n");
        printf("---------------按回车键回到菜单----------------\n");
        getchar();
        getchar();
        return;
    }

    // 有记录，输出结果
    printf("用户名  主叫电话号码  被叫电话号码  通话时长\n");
    for (i = 0; i < k; i++) // 遍历找到的记录并输出
    {
        printf("%-10s    %-7s     %-8s     %-4d\n",
            item4[flag].name, // 用户名
            item1[select[i]].call1, // 主叫电话号码
            item1[select[i]].call2, // 被叫电话号码
            item1[select[i]].Time); // 通话时长
    }
    printf("\n");
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}

//显示源数据文件模块
void show_origin(struct record* item1)
{
    int i;
    printf("主叫区号   主叫电话号码      被叫区号       被叫电话号码     通话时长（秒）\n");
    for (i = 0;i < count;i++)
    {
        printf(" %-10s %-15s %-10s %-15s %-5d\n",
            item1[i].area_num1,
            item1[i].call1,
            item1[i].area_num2,
            item1[i].call2,
            item1[i].Time);
    }
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//显示长话费率文件模块
void show_cost(struct cost* item2)
{
    int i;
    printf("区号      费率\n");
    for (i = 0;i < 4;i++)
    {
        printf("%-10s%-1.2f\n", item2[i].area_num, item2[i].money);
    }
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
//显示用户文件
void show_information(struct user* item4)
{
    int i;
    printf("电话号码   用户姓名\n");
    for (i = 0;i < 5;i++)
    {
        printf("%-11s%-10s\n", item4[i].call, item4[i].name);
    }
    printf("---------------按回车键回到菜单----------------\n");
    getchar();
    getchar();
}
