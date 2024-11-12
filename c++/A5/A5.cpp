//
//  main.cpp
//  A5
//
//  Created by zzr on 2024/11/11.
//

#include <iostream>
#include<string.h>
#include<stdlib.h>
void to_binary(int n)//十进制转二进制函数
{
    int r;
    r=n%2;
    if(n>=2)
        to_binary(n/2);//递归调用
    
    putchar(r==0?'0':'1');
}
int main()
{
    char input[50],str[100];
    int radix,i,num=0,j,len;
    printf("请输入数字和进制\n");
    scanf("%s %d",input,&radix);
    len=strlen(input);
    for(i=0;i<len;i++)//先转换成十进制数
      {
          if('0' <= input[i] && input[i] <= '9')//该位对应的值在0-9之间(2,8或10进制)
           num=num*radix+input[i]-'0';
         else
           num=num*radix+input[i]-'a'+10;//该位对应的值大于9（16进制）
      }

    printf("二进制：");
    to_binary(num);
    printf("\n");
    printf("八进制：%o\n",num);
    printf("十进制：%d\n",num);
    printf("十六进制：%x\n",num);
    return 0;
}

