# 词频统计（数组或链表实现）

**【问题描述】**

编写程序统计一个英文文本文件中每个单词的出现次数（词频统计），并将统计结果按单词字典序输出到屏幕上。

注：在此单词为仅由字母组成的字符序列。包含大写字母的单词将大写字母转换为小写字母后统计。

**【输入形式】**

打开当前目录下文件“article.txt”，从中读取英文单词进行词频统计。

**【输出形式】**

程序将单词统计结果按单词字典序输出到屏幕上，每行输出一个单词及其出现次数，单词和其出现次数间由一个空格分隔，出现次数后无空格，直接为回车。

**【样例输入】**

当前目录下文件article.txt内容如下：

“Do not take to heart every thing you hear.”

“Do not spend all that you have.”

“Do not sleep as long as you want;”

**【样例输出】**

```text
all 1
as 2
do 3
every 1
have 1
hear 1
heart 1
long 1
not 3
sleep 1
spend 1
take 1
that 1
thing 1
to 1
want 1
you 3

```

**【样例说明】**

按单词字典序依次输出单词及其出现次数。

**【评分标准】**

通过所有测试点将得满分。提交程序文件名为word_frequency_statistics.c。