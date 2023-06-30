#include "../include/view/MenuView.h"

#define SEPERATOR "-----------------------------------------------------------------------\n"

void show_welcome_message()
{
    //在线字符banner生成：https://www.bootschool.net/chinese-to-ascii
    FILE* file = fopen("banner.txt", "r");
    if (file == NULL) {
        puts("banner.txt文件打开失败，请检查后重试");
        return;
    }
    char line[255];
    printf(SEPERATOR);
	while (fgets(line, 255, file) != NULL) {

		printf(" %s", line);
	}
    printf(SEPERATOR);
    fclose(file);
    printf("%s%42s%28s\n", "|", "欢迎使用本银行服务", "|");
}

void show_main_menu()
{
    printf(SEPERATOR);
    printf("%s%69s%s\n", "|",  " ", "|");
    printf("%-24s%s%41s\n", "|", "1.取号", "|");
    printf("%-24s%s%37s\n", "|", "2.办理业务", "|");
    printf("%-24s%s%33s\n", "|", "3.查看交易信息", "|");
    printf("%-24s%s%38s\n", "|", "4.升级VIP", "|");
    printf("%-24s%s%37s\n", "|", "0.结束交易", "|");
    printf(SEPERATOR);
    printf("请选择需要的功能：");
}

void show_basicbusiness_menu()
{
    printf(" ------------------------------------------------\n");
    printf("|                                                |\n");
    printf("|            1.查询余额                          |\n");
    printf("|            2.存款                              |\n");
    printf("|            3.取款                              |\n");
    printf("|            4.转账                              |\n");
    printf("|            5.查看交易记录                      |\n");
    printf("|            0.结束业务办理                      |\n");
    printf("|                                                |\n");
    printf(" ------------------------------------------------\n");
    printf("请选择进行办理的业务：");
}

void show_exit_message()
{
    printf("              ******           ******            \n");
    printf("           ***********       ***********         \n");
    printf("          **************   **************        \n");
    printf("         *********************************       \n");
    printf("         ***********------------**********       \n");
    printf("          **********|  Goodbye | *********       \n");
    printf("           *********------------********         \n");
    printf("             *************************           \n");
    printf("               *********************             \n");
    printf("                 ******************              \n");
    printf("                   **************                \n");
    printf("                     **********                  \n");
    printf("                       ******                    \n");
}