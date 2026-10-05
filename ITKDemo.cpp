#include <stdio.h>
#include <tcinit/tcinit.h>

int ITK_user_main(int argc, char* argv[])
{

    int retcode = ITK_ok;

    char* userid = ITK_ask_cli_argument("-u=");
    char* password = ITK_ask_cli_argument("-p=");

    char* groupid = ITK_ask_cli_argument("-g=");
    retcode = ITK_init_module(userid, password, groupid);

    if (retcode != ITK_ok) {
        printf("\n Login Faild ");
        return -1;
    }
    printf("\n Login Done ");




    /*printf("\n UserID: %s", userid);
    printf("\n Password: %s", password);
    printf("\n GroupId: %s", groupid);*/

    return 0;


}