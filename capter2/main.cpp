#include <stdio.h>

typedef struct
{
    int number;   // 字句（数）
    char str[10]; // 字句（文字）
    int type;     // 意味 0=数 1=記号 2=文字
} token_t;

int main(void)
{
    token_t tokens[10];
    int tokenIndex = 0;
    int i;
    const char *c = "RUN88+99";

    char *pt;       // ポインタ変数
    pt = (char *)c; // 配列cのアドレスをptに入れる

    while (*pt != 0x00)
    {
        if ('0' <= *pt && *pt <= '9')
        {
            // 数の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = 0;
            while ('0' <= *pt && *pt <= '9')
            {
                tokens[tokenIndex].number = (tokens[tokenIndex].number * 10) + (*pt - 48);
                pt++;
            }
            tokenIndex++;
        }
        else if (('a' <= *pt && *pt <= 'z') ||
                 ('A' <= *pt && *pt <= 'Z'))
        {
            // 文字の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = 2; // 文字
            i = 0;
            while (('a' <= *pt && *pt <= 'z') ||
                   ('A' <= *pt && *pt <= 'Z'))
            {
                tokens[tokenIndex].str[i] = *pt;
                pt++;
                i++;
            }
            tokens[tokenIndex].str[i] = 0x00;
            tokenIndex++;
        }
        else
        {
            // 記号の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = 1; // 記号
            tokens[tokenIndex].str[0] = *pt;
            tokens[tokenIndex].str[1] = 0x00;
            tokenIndex++;
            pt++;
        }
    }

    // トークンの内容を表示
    for (i = 0; i < tokenIndex; i++)
    {
        printf("tokens[%d] type=%d\tnumber=%d\tstr=%s\n",
               i, tokens[i].type, tokens[i].number, tokens[i].str);
    }

    return 0;
}