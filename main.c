#include "BankQueueSystem.h"
#include "include/util/md5.h"
int main()
{
	//start_system();
	char* password = "123456";
	printf("���ܺ�%s\n", GetMD5(password));
	return 0;
}