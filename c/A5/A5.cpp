//
//  P22000820-A5.cpp
//  A5
//
//  Created by 张哲瑞 on 2024/11/11.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>

// 十进制转二进制函数
void to_binary(int n)
{
    if (n >= 2)
        to_binary(n / 2); // 递归调用
    putchar((n % 2) == 0 ? '0' : '1');
}

int main()
{
    char input[50]; // 用于储存输入的数字
    int radix;      // 输入的进制
    int num = 0;    // 转换为十进制的数
    int i = 0, len;

    printf("欢迎使用进制转换器！\n");
    printf("请输入数字和进制（支持 2、8、10、16 进制）：\n");

    // 输入数字和进制
    if (scanf_s("%s %d", input, (unsigned)_countof(input), &radix) != 2)
    {
        printf("输入格式错误，请重新运行程序。\n");
        return -1;
    }

    // 检查输入的进制是否有效
    if (radix != 2 && radix != 8 && radix != 10 && radix != 16)
    {
        printf("仅支持 2、8、10、16 进制，请重新运行程序。\n");
        return -1;
    }

    // 将输入的数字转换为十进制
    len = strlen(input);
    for (i = 0; i < len; i++)
    {
        if ('0' <= input[i] && input[i] <= '9') // 数字部分
        {
            num = num * radix + (input[i] - '0');
        }
        else if ('a' <= input[i] && input[i] <= 'f') // 小写字母部分（十六进制）
        {
            num = num * radix + (input[i] - 'a' + 10);
        }
        else if ('A' <= input[i] && input[i] <= 'F') // 大写字母部分（十六进制）
        {
            num = num * radix + (input[i] - 'A' + 10);
        }
        else
        {
            printf("输入的数字包含非法字符，请重新运行程序。\n");
            return -1;
        }
    }

    // 输出转换后的各进制数
    printf("二进制：");
    to_binary(num);
    printf("\n");

    printf("八进制：%o\n", num);
    printf("十进制：%d\n", num);
    printf("十六进制：%X\n", num);

    return 0;
}