//
//  main.cpp
//  A4
//
//  Created by zzr on 2024/11/11.
//

#include <iostream>
#include <string.h>
int main()
{
    char M[100];//储存明文
    char C[100];//储存密文
    int K;//储存密钥
    int len;//字长
    int i;
    printf("请输入一段明文：");
    gets(M);
    len=strlen(M);
    printf("请输入密钥(整数)：");
    scanf("%d",&K);
    for(i=0;i<len;i++)
    {
        C[i]=M[i]+K;//加密
    }
    printf("加密好的密文为：");
    for(i=0;i<len;i++)
    {
        printf("%c",C[i]);
    }
    printf("\n");
    return 0;
}


