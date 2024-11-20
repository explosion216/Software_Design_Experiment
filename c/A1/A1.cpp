//
//  P22000820-A1.cpp
//  A1
//
//  Created by 张哲瑞 on 2024/11/11.
//

#include <iostream>
#define N 100
int main()
{
    int i, j, k;
    int T, R;
    int n;
    int con = 0;
    char name[N][10];//人名采用二维数组，一列为一个人名，该列的每个元素为名字的字母
    int score[N];
    int num[N];//分数，序号采用一维数组即可
    printf("请输入学生人数：");
    scanf_s("%d", &n);
    printf("请输入学生信息：\n");
    printf("格式为：姓名+空格+成绩\n");
    for (i = 0;i < n;i++)
    {
        scanf_s("%s", name[i], (unsigned)_countof(name[i]));//字符串依次送入二维数组的每列
        scanf_s("%d", &score[i]);//双精度数依次送入一维数组的每个元素
        num[i] = i;//每个成员有了序号
    }
    for (j = 0;j < (n - 1);j++)//排序
        for (k = 0;k < (n - 1 - j);k++)
            if (score[k] < score[k + 1])
            {
                R = score[k];
                score[k] = score[k + 1];
                score[k + 1] = R;//若后者成绩高，则换位，也就是把成绩高的换到前面，这一步只改了成绩的顺序
                T = num[k];
                num[k] = num[k + 1];
                num[k + 1] = T;//换序号，使得成员和成绩仍然有正确的对应关系
            }
    printf("按分数降序排列：\n");
    for (i = 0;i < n;i++)
    {
        con = num[i];
        printf("%s  ", name[con]);
        printf("%d", score[i]);
        printf("\n");
    }
    return 0;
}