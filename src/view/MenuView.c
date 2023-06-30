#include "../include/view/MenuView.h"

#define SEPERATOR "-----------------------------------------------------------------------\n"

void show_welcome_message()
{
    //�����ַ�banner���ɣ�https://www.bootschool.net/chinese-to-ascii
    FILE* file = fopen("banner.txt", "r");
    if (file == NULL) {
        puts("banner.txt�ļ���ʧ�ܣ����������");
        return;
    }
    char line[255];
    printf(SEPERATOR);
	while (fgets(line, 255, file) != NULL) {

		printf(" %s", line);
	}
    printf(SEPERATOR);
    fclose(file);
    printf("%s%42s%28s\n", "|", "��ӭʹ�ñ����з���", "|");
}

void show_main_menu()
{
    printf(SEPERATOR);
    printf("%s%69s%s\n", "|",  " ", "|");
    printf("%-24s%s%41s\n", "|", "1.ȡ��", "|");
    printf("%-24s%s%37s\n", "|", "2.����ҵ��", "|");
    printf("%-24s%s%33s\n", "|", "3.�鿴������Ϣ", "|");
    printf("%-24s%s%38s\n", "|", "4.����VIP", "|");
    printf("%-24s%s%37s\n", "|", "0.��������", "|");
    printf(SEPERATOR);
    printf("��ѡ����Ҫ�Ĺ��ܣ�");
}

void show_basicbusiness_menu()
{
    printf(" ------------------------------------------------\n");
    printf("|                                                |\n");
    printf("|            1.��ѯ���                          |\n");
    printf("|            2.���                              |\n");
    printf("|            3.ȡ��                              |\n");
    printf("|            4.ת��                              |\n");
    printf("|            5.�鿴���׼�¼                      |\n");
    printf("|            0.����ҵ�����                      |\n");
    printf("|                                                |\n");
    printf(" ------------------------------------------------\n");
    printf("��ѡ����а����ҵ��");
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