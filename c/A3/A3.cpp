//
//  P22000820-A3.cpp
//  A3
//
//  Created by 张哲瑞 on 2024/11/11.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// 函数声明
void menu();      // 菜单函数
void new_edit();  // 新建文本函数
void open();      // 打开文本函数

int main()
{
    menu();
    return 0;
}

// 显示菜单
void menu()
{
    int choose;
    do {
        printf("文本编辑器功能菜单：\n");
        printf("1. 打开文本\n");
        printf("2. 增加新文本\n");
        printf("3. 退出\n");
        printf("请输入要执行的功能：");
        if (scanf_s("%d", &choose) != 1) {
            printf("输入错误，请重新输入！\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }
        switch (choose)
        {
        case 1:
            open();
            break;
        case 2:
            new_edit();
            break;
        case 3:
            exit(0);
        default:
            printf("请输入正确序号！\n");
        }
    } while (choose != 3);
}

// 新建文本函数
void new_edit()
{
    char ch;
    FILE* fp = nullptr;
    char filename[256] = { 0 };  // 文件名
    char wenben[10000] = { 0 };  // 文本内容
    int i = 0;

    printf("请输入文本内容 (以 # 结束)：\n");
    while ((ch = getchar()) != '#') // 输入内容，直到遇到 #
    {
        wenben[i++] = ch;
    }
    getchar(); // 清除缓冲区中的换行符
    printf("请输入需要保存的文件名及路径：");
    scanf_s("%255s", filename, (unsigned)_countof(filename)); // 读取文件名

    // 使用 fopen_s 打开文件
    errno_t err = fopen_s(&fp, filename, "w");
    if (err != 0 || fp == nullptr) {
        printf("文件无法创建，请检查路径或权限。\n");
        return;
    }

    for (int j = 0; j < i; j++) {
        putc(wenben[j], fp); // 写入文件
    }

    printf("\n新文件已保存！现文件内容如下：\n");
    rewind(fp); // 将文件指针移动到文件开头
    while ((ch = getc(fp)) != EOF) {
        putchar(ch); // 输出文件内容
    }
    putchar('\n');
    fclose(fp); // 关闭文件
}

// 打开文本函数
void open()
{
    char ch;
    FILE* fp = nullptr;
    char filename[256] = { 0 };  // 文件名
    char wenben[10000] = { 0 };  // 文本内容
    int i = 0;

    printf("请输入需要打开的文件名及路径：");
    scanf_s("%255s", filename, (unsigned)_countof(filename)); // 读取文件名

    // 使用 fopen_s 打开文件
    errno_t err = fopen_s(&fp, filename, "r+");
    if (err != 0 || fp == nullptr) {
        printf("文件无法打开，请检查路径或文件是否存在。\n");
        return;
    }

    printf("文件内容如下：\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch); // 输出文件内容
    }
    printf("\n");

    printf("1. 继续编辑此文本\n");
    printf("2. 重新编辑此文本\n");
    printf("3. 回到主菜单\n");
    printf("4. 退出\n");
    printf("请选择下一步操作：");
    int xuanze;
    if (scanf_s("%d", &xuanze) != 1) { // 读取选择
        printf("输入错误！\n");
        fclose(fp);
        return;
    }

    if (xuanze == 4) {
        fclose(fp);
        exit(0);
    }
    else if (xuanze == 3) {
        fclose(fp);
        menu();
    }
    else if (xuanze == 2) {
        i = 0;
        fclose(fp);
        err = fopen_s(&fp, filename, "w+");
        if (err != 0 || fp == nullptr) {
            printf("文件无法重新打开，请检查路径或权限。\n");
            return;
        }
        printf("请输入内容 (以 # 结束)：\n");
        while ((ch = getchar()) != '#') {
            wenben[i++] = ch;
        }
        getchar(); // 清空缓冲区
    }
    else if (xuanze == 1) {
        i = 0;
        printf("请输入内容 (以 # 结束)：\n");
        fseek(fp, 0, SEEK_END); // 将文件指针移动到文件末尾
        while ((ch = getchar()) != '#') {
            wenben[i++] = ch;
        }
        getchar(); // 清空缓冲区
    }
    else {
        printf("请正确输入选项！\n");
        fclose(fp);
        return;
    }

    printf("是否保存新文档？1. 是   2. 否，退出程序\n");
    int xuanze2;
    if (scanf_s("%d", &xuanze2) != 1) {
        printf("输入错误！\n");
        fclose(fp);
        return;
    }
    if (xuanze2 == 2) {
        fclose(fp);
        exit(0);
    }
    else {
        for (int j = 0; j < i; j++) {
            putc(wenben[j], fp); // 写入文件
        }
    }

    printf("\n新文件已保存！现文件内容如下：\n");
    rewind(fp); // 将文件指针移动到文件开头
    while ((ch = getc(fp)) != EOF) {
        putchar(ch);
    }
    putchar('\n');
    fclose(fp);
}