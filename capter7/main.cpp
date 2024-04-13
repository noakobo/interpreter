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

node_t *createNode(token_t *token, token_t *left, token_t *right);
node_t *createNode(token_t *token, node_t *left, token_t *right);
int calcAdd(node_t *left, node_t *right);
int count = 0; // calcAddが呼ばれた回数

int main(void)
{
  token_t tokens[10];
  int tokenIndex = 0;
  int i;
  const char *c = "8+9+10+11+12";

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
    printf("tokens[%d] type=%d\tnumber=%d\tstr=%s\ttype=%d\n",
           i, tokens[i].type, tokens[i].number, tokens[i].str, tokens[i].type);
  }
  printf("\n");

  //////////// ノードにトークンを追加してみる ////////////
  node_t *node;

  i = 0;
  while ((i + 1) < tokenIndex)
  {
    if (tokens[i + 1].type == plus)
    {
      if (i == 0)
      {
        node = createNode(&tokens[i + 1], &tokens[i], &tokens[i + 2]);
        i += 2;
      }
      else
      {
        node = createNode(&tokens[i + 1], node, &tokens[i + 2]);
        i += 2;
      }
    }
  }

  //////////// 計算してみる ////////////
  int result;
  result = calcAdd(node->leftNode, node->rightNode);
  printf("result:%d", result);

  return 0;
}

int calcAdd(node_t *left, node_t *right)
{
  int result;
  if (left->thisToken->type == plus)
  {
    return calcAdd(left->leftNode, left->rightNode)+right->thisToken->number;
  }
  return left->thisToken->number + right->thisToken->number;
}

node_t *createNode(token_t *token, token_t *left, token_t *right)
{
  node_t *nodeLeft;
  nodeLeft = (node_t *)malloc(sizeof(node_t));
  nodeLeft->thisToken = left; // 8
  nodeLeft->leftNode = nullptr;
  nodeLeft->rightNode = nullptr;

  node_t *nodeRight;
  nodeRight = (node_t *)malloc(sizeof(node_t));
  nodeRight->thisToken = right; // 9
  nodeRight->leftNode = nullptr;
  nodeRight->rightNode = nullptr;

  node_t *newNode;
  newNode = (node_t *)malloc(sizeof(node_t));
  newNode->thisToken = token;
  newNode->leftNode = nodeLeft;   // 8
  newNode->rightNode = nodeRight; // 9

  printf("createNode %p\ttype:%d\n", newNode, newNode->thisToken->type);
  printf("\tleft:%d\tright:%d\n",
         nodeLeft->thisToken->number, nodeRight->thisToken->number);

  return newNode;
}

node_t *createNode(token_t *token, node_t *left, token_t *right)
{
  node_t *nodeRight;
  nodeRight = (node_t *)malloc(sizeof(node_t));
  nodeRight->thisToken = right;
  nodeRight->leftNode = nullptr;
  nodeRight->rightNode = nullptr;

  node_t *newNode;
  newNode = (node_t *)malloc(sizeof(node_t));
  newNode->thisToken = token;
  newNode->leftNode = left;
  newNode->rightNode = nodeRight;

  printf("createNode %p\ttype:%d\n", newNode, newNode->thisToken->type);
  printf("\tleft:%p\tright:%d\n",
         left, nodeRight->thisToken->number);

  return newNode;
}
