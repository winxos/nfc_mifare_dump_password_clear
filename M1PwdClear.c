/**
 * @file M1PwdClear.c
 * @author wvv (winxos@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CARD_SZ 1024
typedef unsigned char Card[CARD_SZ];

void card_load(char *p, Card *c)
{
    FILE *fin = fopen(p, "rb");
    if (!fin)
    {
        puts("file not exist.");
        return;
    }
    fread(c, CARD_SZ, 1, fin);
}
void card_print(Card cd)
{
    puts("M1 CARD");
    for (int c = 0; c < CARD_SZ; c++)
    {
        printf("%02X", cd[c]);
        if (c % 64 == 63)
        {
            printf("\n");
        }
    }
}
void card_clear_pwd(Card c)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            c[i * 64 + 48 + j] = 0xff;
            c[i * 64 + 58 + j] = 0xff;
        }
    }
}
void card_save(char *p, Card c)
{
    FILE *fout = fopen(p, "wb");
    if (!fout)
    {
        puts("file already exist.");
        return;
    }
    fwrite(c, CARD_SZ, 1, fout);
}
void test()
{
    puts("DEMO TEST");
    Card c = {0};
    // card_load("1.dump", &c);
    card_print(c);
    card_clear_pwd(c);
    card_print(c);
}
int main(int n, char **args)
{
    if (n < 2)
    {
        puts("USAGE: M1PwdClear.exe xx.dump");
        test();
        return 0;
    }
    puts(args[0]);
    puts(args[1]);
    Card c = {0};
    card_load(args[1], &c);
    card_print(c);
    card_clear_pwd(c);
    card_print(c);
    char cn[200];
    memcpy(cn,args[1],strlen(args[1]));
    strcat(cn, ".dump");
    puts("PASSWORD CLEARED.");
    printf("SAVE TO THE FILE %s.",cn);
    card_save(cn,c);
    return 0;
}
