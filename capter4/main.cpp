#include <stdio.h>

typedef enum
{
    number,
    symbol,
    text,
    plus,
    minus,
    mul,
    div,
} tokentype;

typedef struct
{
    int number;     // 字句（数）
    char str[10];   // 字句（文字）
    tokentype type; // 意味
} token_t;

int main(void)
{
    token_t tokens[10];
    int tokenIndex = 0;
    int i;
    const char *c = "8+9";

    char *pt;       // ポインタ変数
    pt = (char *)c; // 配列cのアドレスをptに入れる

    while (*pt != 0x00)
    {
        if ('0' <= *pt && *pt <= '9')
        {
            // 数の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = number;
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
            tokens[tokenIndex].type = text; // 文字
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
        else if (*pt == '+')
        {
            // 記号の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = plus; // 足す
            tokens[tokenIndex].str[0] = *pt;
            tokens[tokenIndex].str[1] = 0x00;
            tokenIndex++;
            pt++;
        }
        else if (*pt == '-')
        {
            // 記号の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = minus; // 引く
            tokens[tokenIndex].str[0] = *pt;
            tokens[tokenIndex].str[1] = 0x00;
            tokenIndex++;
            pt++;
        }
        else if (*pt == '*')
        {
            // 記号の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = mul; // 掛ける
            tokens[tokenIndex].str[0] = *pt;
            tokens[tokenIndex].str[1] = 0x00;
            tokenIndex++;
            pt++;
        }
        else if (*pt == '/')
        {
            // 記号の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = div; // 割る
            tokens[tokenIndex].str[0] = *pt;
            tokens[tokenIndex].str[1] = 0x00;
            tokenIndex++;
            pt++;
        }
        else
        {
            // 記号の字句
            tokens[tokenIndex].number = 0;
            tokens[tokenIndex].type = symbol; // 記号
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

    int ans;

    switch (tokens[1].type)
    {
    case plus:
        ans = tokens[0].number + tokens[2].number;
        break;
    case minus:
        ans = tokens[0].number - tokens[2].number;
        break;
    case mul:
        ans = tokens[0].number * tokens[2].number;
        break;
    case div:
        ans = tokens[0].number / tokens[2].number;
        break;
    default:
        ans = 999;
    }
    printf("ans=%d", ans);
    return 0;
}