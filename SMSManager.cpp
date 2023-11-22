#include "SMSManager.h"

/*----------------------------------------------------------------------------------
Class Member�Լ�: get_instance() - singleton ����/ class �����ϱ� ���� ����ؾ��ϴ� �Լ�
----------------------------------------------------------------------------------*/
SMSManager& SMSManager::get_instance()
{
	static SMSManager sms;
	return sms;
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:add_sms_number - �ش� ��ȣ ��ϵǾ����� ����ϴ� �Լ�
----------------------------------------------------------------------------------*/
void SMSManager::add_sms_number(const std::string& number)
{
	std::cout << number << "���" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:add_sms_number - ��� ���� map�� ��ȣ�� �߰��ϴ� �Լ�
----------------------------------------------------------------------------------*/
void SMSManager::add_sms_number(const std::string& Name, const PHONENUMBER& number)
{
	//map Ž���� ���� �ش� ��ǰ �˶��� ��û�� number�� �ִ��� Ȯ��
	auto it = std::find(m[Name].begin(), m[Name].end(), number);
	if (it == m[Name].end()) {
		//��ϵǾ� ���� ���� ��ȣ�� ���
		m[Name].push_back(number);
		std::cout << "���" << std::endl;
	}
	else {
		std::cout << "����" << std::endl;
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ�: deleteSms - ��ȣ�� �����ϰ� ���� �� ȣ���ϴ� �Լ�
----------------------------------------------------------------------------------*/
void SMSManager::deleteSms(const std::string& Number)
{
	int cnt = 0;
	//m�� key Ž��
	std::for_each(m.begin(), m.end(), [&Number,&cnt](auto& pair) {
		std::vector<std::string>& v = pair.second;
		//�ش� key�� �Էµ� ���� ���� ��ȣ�� ��ϵǾ����� Ž�� 
		auto it = std::find(v.begin(), v.end(), Number);
		if (it != v.end()) {
			v.erase(it);
			cnt++;
			std::cout << "��ȣ ����" << std::endl;
		}
	});
	if (cnt == 0) { std::cout << "��ȣ ��� �ʿ�" << std::endl; }
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ�: deleteSmsKey - ��ǰ�� ������ �� ȣ��Ǿ� ������ ��ȣ�� �Բ� �����ϴ� �Լ�
----------------------------------------------------------------------------------*/
void SMSManager::deleteSmsKey(const std::string& Name) {
	auto it = m.find(Name);
	if (it != m.end()) {
		m.erase(it);
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ�: send_sms - ���ڸ� ���� �� ȣ��Ǵ� �Լ�
----------------------------------------------------------------------------------*/
void SMSManager::send_sms(const std::string& Name, const std::string& msg)
{
	auto v = m.find(Name);

	if (v != m.end()) {
		for (const PHONENUMBER& number : v->second)
		{
			std::cout << number << " : " << Name << msg << std::endl;
		}
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ�: show - ����� ��ȣ�� ��Ȳ�� ǥ��
----------------------------------------------------------------------------------*/
void SMSManager::show() {
	std::for_each(m.begin(), m.end(), [](auto& pair) {
		std::string key = pair.first;
		auto& v = pair.second;

		std::cout << "[" << key << "]" << std::endl;

		std::for_each(v.begin(), v.end(), [](PHONENUMBER& value) {
			std::cout << "PHONE NUMBER : " << value << std::endl;
		});
	});
}


