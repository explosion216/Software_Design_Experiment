//
//  main.cpp
//  A2
//
//  Created by zzr on 2024/11/11.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char *randstr(char *str)
{
    int i,len;
    srand(time(NULL));//随机性借由时钟产生
    len = rand()%10+2;//随机生成字长
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 3))//可以产生大写字母，小写字母和数字
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
        case 2:
            str[i] = 'a' + rand() % 26;
            break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    str[i] = '\0';//终止位
    return str;
}

int main(){
    char name[20],inputstr[20];
    int i=0,error = 0,j=5;//可以打5次
    float gailv;
    printf("随机产生字符串为：");
    while(j!=0){
        printf("%s\n",randstr(name));//输出上面生成的字符串
        scanf("%s",&inputstr);
        while(name[i]!='\0'){//不等于终止位就一直判断
            if(name[i]!= inputstr[i]){
                error++;//字符不同，即输入错误，错误+1
            }
            i++;
        }
        if(error == 0){
            printf("输入正确，正确率：100%% \n");
        }else{
            gailv = (1-error/(float)strlen(name))*100;//计算正确率（1-错误率）
            printf("输入错误，正确率：");
            printf("%.2f",gailv);
            printf("%%\n");
        }
        j--;//完成一次打字
        error=0;
        i=0;
    }

    return 0;
}



