#include <stdio.h>

int main(void)
{
   const char *c = "8+9"; // 配列cに8+9を代入
   // c[0]='8',c[1]='+',c[2]='9',c[3]=0x00
  
   char *pt;       // ポインタ変数
   pt = (char *)c; // 配列cのアドレスをptに入れる

   printf("%s\n", c); // 配列cの内容を表示する
   printf("\n");
   printf("c[0]=%c\n", c[0]); // 配列cの0番目の内容を表示する
   printf("c[1]=%c\n", c[1]); // 配列cの1番目の内容を表示する
   printf("c[2]=%c\n", c[2]); // 配列cの2番目の内容を表示する
   printf("\n");
   printf("%p=%c\n", pt, *pt); // ポインタptの内容を表示する
   pt++;                       // ポインタptをインクリメントする
   printf("%p=%c\n", pt, *pt); // ポインタptの内容を表示する
   pt++;                       // ポインタptをインクリメントする
   printf("%p=%c\n", pt, *pt); // ポインタptの内容を表示する
   pt++;                       // ポインタptをインクリメントする

   return 0;
}