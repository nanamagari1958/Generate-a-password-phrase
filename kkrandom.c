/**********************************************************************
* FUNCTION : kkrandom main function
* PURPOSE  : generate password string
* USAGE    : % kkrandom password-length
*              MAX. password length is 20
* EXIT CODE: 0: no error, 1: error
* REMARKS  :
* MODIFY HISTORY :
*   mark    modify                               date      name
*   new                                         17/10/07   k.kimura
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PWD_LEN 20

void Usage();
const char *pwdstr = "ABCDEFGHIJKLMNOPQRXYZ0123456789abcdefghijklmnopqrxyz";

int main(int argc, char **argv)
{
    time_t epoctime, e_time;
    int ireqpwdlen, i, inum, ich, ipos, ipwdstrlen;
    char pwdbuff[MAX_PWD_LEN + 1], *pstr;

    // 引数チェック
    if (argc != 2) Usage();
    if (strlen(argv[1]) > 2) Usage();
    ireqpwdlen = atoi(argv[1]);
    if (ireqpwdlen < 1 || ireqpwdlen > MAX_PWD_LEN) Usage();

    // 初期化
    memset(pwdbuff, 0x00, sizeof(pwdbuff));     // パスワード格納バッファ
    ipwdstrlen = strlen(pwdstr);                // パスワード用文字列町

    // 乱数発生のためのseeds作製
    epoctime = time(&e_time);
    if (epoctime < 0) {
        perror("main");
        exit(1);
    }
    // 乱数初期化
    srand((unsigned int)epoctime);
    // 指定文字数分の乱数発生
    for (i=0; i<ireqpwdlen; ){
        inum = rand();
        ipos = inum % (ipwdstrlen - 1);
        // パスワード用の1文字を取得
        ich = *(pwdstr + ipos);
        // 同一文字コードがパスワードに含まれないようにチェックする。
        pstr = strchr(pwdbuff, ich);
        if (pstr == NULL) {
            pwdbuff[strlen(pwdbuff)] = ich;
            i++;
        }
    }
    // パスワード表示
    printf("password = %s \n", pwdbuff);
    exit(0);
}

void Usage() {
    printf("Usage : kkrandom password_lengnth\n");
    printf("        MAX. password length is 20\n");
    exit(1);
}
