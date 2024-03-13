#include <stdio.h>
#include <malloc.h>

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

typedef struct node_t
{
    token_t *thisToken;
    node_t *leftNode;
    node_t *rightNode;
} node_t;

int main(void)
{
    token_t tokens[10];
    int tokenIndex = 0;
    int i;
    const char *c = "8+9+10";

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
    printf("\n");

    //////////// ノードにトークンを追加してみる ////////////

    node_t node1;
    node_t *node1Left;
    node_t *node1Right;

    node1Left = (node_t *)malloc(sizeof(node_t));
    node1Left->thisToken = &tokens[0]; // 8
    node1Left->leftNode = nullptr;
    node1Left->rightNode = nullptr;

    node1Right = (node_t *)malloc(sizeof(node_t));
    node1Right->thisToken = &tokens[2]; // 9
    node1Right->leftNode = nullptr;
    node1Right->rightNode = nullptr;

    node1.leftNode = node1Left;   // 8
    node1.thisToken = &tokens[1]; //+
    node1.rightNode = node1Right; // 9

    node_t node2;
    node_t *node2Right;

    node2Right = (node_t *)malloc(sizeof(node_t));
    node2Right->thisToken = &tokens[4]; // 10
    node2Right->leftNode = nullptr;
    node2Right->rightNode = nullptr;

    node2.leftNode = &node1;      // 8+9
    node2.thisToken = &tokens[3]; //+
    node2.rightNode = node2Right; // 10

    printf("node1.pt=%p\n", &node1);
    printf("\tstr=%c\n", node1.thisToken->str[0]);
    printf("\tleft.num=%d\n", node1Left->thisToken->number);
    printf("\tright.num=%d\n", node1Right->thisToken->number);

    printf("node2.pt=%p\n", &node2);
    printf("\tstr=%c\n", node2.thisToken->str[0]);
    printf("\tleft.pt=%p\n", node2.leftNode);
    printf("\tright.num=%d\n", node2Right->thisToken->number);

    return 0;
}