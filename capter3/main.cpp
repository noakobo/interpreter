#include <stdio.h>

int main(void)
{
    const char *c = "88+99"; // 配列cに8+9を代入
    // c[0]='8',c[1]='+',c[2]='9',c[3]=0x00

    char *pt;       // ポインタ変数
    pt = (char *)c; // 配列cのアドレスをptに入れる

    while (*pt != 0x00)
    {
        if ('0' <= *pt && *pt <= '9') // 数？
        {
            printf("%c", *pt); // ポインタptの内容を表示する
        }
        else if (('a' <= *pt && *pt <= 'z') ||
                 ('A' <= *pt && *pt <= 'Z')) // 文字？
        {
            printf("%c", *pt); // ポインタptの内容を表示する
        }
        else
        {
            // その他は記号とする
            printf("\n%c\n", *pt); // ポインタptの内容を表示する
        }
        pt++; // ポインタptをインクリメントする
    }

    return 0;
}