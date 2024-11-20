//
//  P22000820-A4.cpp
//  A4
//
//  Created by 张哲瑞 on 2024/11/11.
//

#include <iostream>
#include <string.h>

int main()
{
    char M[100] = { 0 }; // 储存明文，初始化为 0
    char C[100] = { 0 }; // 储存密文，初始化为 0
    int K = 0; // 储存密钥
    int len = 0; // 储存字长
    int i = 0; // 循环计数器

    // 输入界面
    printf("欢迎使用加密程序！\n");
    printf("请输入一段明文：\n");

    // 使用 fgets 替代 gets，限制读取的最大字符数
    if (fgets(M, sizeof(M), stdin) == nullptr)
    {
        printf("输入错误，请重新运行程序。\n");
        return -1;
    }

    // 移除 fgets 自动添加的换行符（如果存在）
    size_t inputLen = strlen(M);
    if (M[inputLen - 1] == '\n')
    {
        M[inputLen - 1] = '\0';
    }

    len = static_cast<int>(strlen(M)); // 将 size_t 转换为 int 类型

    if (len == 0) // 检查是否为空字符串
    {
        printf("输入的明文为空，请重新运行程序。\n");
        return -1;
    }

    printf("请输入密钥(整数)：\n");
    if (scanf_s("%d", &K) != 1) // 检查密钥输入是否合法
    {
        printf("密钥输入错误，请重新运行程序。\n");
        return -1;
    }

    // 加密过程
    for (i = 0; i < len; i++)
    {
        C[i] = M[i] + K; // 根据公式 Ci = Mi + K 进行加密
    }

    // 输出界面
    printf("加密好的密文为：\n");
    for (i = 0; i < len; i++)
    {
        printf("%c", C[i]); // 输出密文
    }
    printf("\n");

    return 0;
}