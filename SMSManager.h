#pragma once
#pragma warning(disable :6031)
#include "menu.h"

/*----------------------------------------------------------------------------------
Class name	    : SMSManager - �˸��� ���� �޴��� ��ȣ�� ��� �� ���� �����ϴ� �Լ�
Class ��� ���� : map<> m - ���� ON�� �����ϰ� ���� ��ǰ �̸��� ���� ���� ��ȣ�� �����ϴ� map

Class Member�Լ�: add_sms_number - ��� ���� map�� ��ȣ�� �߰��ϴ� �Լ�
			      send_sms - ���ڸ� ���� �� ȣ��Ǵ� �Լ�
				  deleteSms - ��ȣ�� �����ϰ� ���� �� ȣ���ϴ� �Լ�
				  deleteSmsKey - ��ǰ�� ������ �� ȣ��Ǿ� ������ ��ȣ�� �Բ� �����ϴ� �Լ�
				  show - ����� ��ȣ�� ��Ȳ�� ǥ��
----------------------------------------------------------------------------------*/
class SMSManager
{
	using PHONENUMBER = std::string;
	std::map<std::string, std::vector<PHONENUMBER>> m;
public:
	static SMSManager& get_instance();
	void add_sms_number(const std::string& number);
	void add_sms_number(const std::string& Name, const PHONENUMBER& number);
	void send_sms(const std::string& Name, const std::string& msg);
	void deleteSms(const std::string& Number);
	void deleteSmsKey(const std::string& Name);
	void show();
};
