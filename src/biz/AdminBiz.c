#include "../include/biz/AdminBiz.h"

int admin_login(char* login_name, char* password) {
	Admin admin;
	query_admin(&admin, login_name);		//���ݵ�¼����ѯ��Ӧ�Ĺ���Ա��Ϣ
	if (admin.id < 0) {
		return 0;		//���޴���
	}
	//�Ƚ�����
	char* md5_password = GetMD5(password);	//��������������md5����
	//�Ƚ� ���ܺ�Ĵ������� �� ���ݿ���ȡ��������
	if (strcmp(md5_password, admin.password) == 0) {
		return 1;
	}
	safe_free(md5_password);
	return 0;			//�������
}