# 字符串替换（新）

**【问题描述】**
编写程序将一个指定文件中某一字符串替换为另一个字符串。要求：（1）被替换字符串若有多个，均要被替换；（2）指定的被替换字符串，大小写无关。

**【输入形式】**
给定文件名为 `filein.txt`。从控制台输入两行字符串（不含空格，行末尾都有回车换行符），分别表示被替换的字符串和替换字符串。

**【输出形式】**
将替换后的结果输出到文件 `fileout.txt` 中。

**【样例输入】**
从控制台输入两行字符串：

```text
in
out

```

文件 `filein.txt` 的内容为：

```c
#include <stdio.h>
void main()
{
    FILE * IN;
    if((IN=fopen("in.txt","r"))==NULL)
    {
        printf("Can&rsquot;t open in.txt!");
        return;
    }
    fclose(IN);
}

```

**【样例输出】**
文件 `fileout.txt` 的内容应为：

```c
#outclude <stdio.h>
void maout()
{
    FILE * out;
    if((out=fopen("out.txt","r"))==NULL)
    {
        prouttf("Can&rsquot;t open out.txt!");
        return;
    }
    fclose(out);
}

```

**【样例说明】**
输入的被替换字符串为 `in`，替换字符串为 `out`，即将文件 `filein.txt` 中的所有 `in` 字符串（包括 `iN`、`In`、`IN` 字符串）全部替换为 `out` 字符串，并输出保存到文件 `fileout.txt` 中。

**【评分标准】**
该题要求得到替换后的文件内容，共有5个测试点。上传C语言文件名为 `replace.c`。