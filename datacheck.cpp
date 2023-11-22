#include "datacheck.h"

/*----------------------------------------------------------------------------------
Class Member�Լ�: Addcheck - ����ڰ� �Է��� ��ǰ�� ��ϰ������� üũ�ϴ� �Լ�
---------------------------------------------------------------------------------- */
void checkValue::Addcheck(std::map < int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, int& type, std::string& Name, int& powerConsumption) {
	//class �� ��� �Լ��� ���� Type, Name, powerConsumption�� ���� ��ȿ���� Ȯ���Ͽ� ��� ���� ���� �Ǵ�
	if (checkType(type) == 0 || checkName(applianceArray, Name) == 0 || checkPower(powerConsumption) == 0) {
		type = 0;
		return;
	}
	std::cout << ("��� ���� ��ǰ. ��� ����\n") << std::endl;
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:  checkType - ����ڰ� �Է��� Type ��ȿ�� Ȯ��
---------------------------------------------------------------------------------- */
int checkValue::checkType(int& type) {
	std::cout << "��ǰ type �Է� :";
	//singleton ���� ���.Input class�� �����Ͽ� �� �Է� ����(1~4������ ���ڸ� �Է¹޴� �Լ�)
	Input& input = Input::get_instance();
	input.inputAtoB(type, 1, 4);
	return 1;
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:  checkName - ����ڰ� �Է��� ��ǰ �̸��� ��ȿ��(���� ����) Ȯ��
							 - ���� for���� ����, ApplianceArray�� ��� ��ǰ �̸��� ��
---------------------------------------------------------------------------------- */
int checkValue::checkName(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, std::string& Name) {
	std::cout << "��ǰ �̸� �Է� :";
	//singleton ���� ���.Input class�� �����Ͽ� ���� �Է� ����(���ڸ� �Է¹޴� �Լ�)
	Input& input = Input::get_instance();
	input.inputString(Name);
	if (!applianceArray.empty()) {
		for (auto i : applianceArray) {
			auto& v = i.second;
			for (auto j : v) {
				if (j->get_title() == Name) {
					std::cout << "�̹� ��ϵ� ��ǰ�Դϴ�.\n";
					_getch();
					return 0;
				}
			}
		}
	}
	return 1;
}
/*----------------------------------------------------------------------------------
Class Member�Լ�:  checkPower - ����ڰ� �Է��� �Һ������� ��ȿ�� Ȯ��
---------------------------------------------------------------------------------- */
int checkValue::checkPower(int& powerConsumption) {
	std::cout << "��ǰ �Һ����� �Է� :";
	//singleton ���� ���.Input class�� �����Ͽ� �Է� ����(���ڸ� �Է¹޴� �Լ�)
	Input& input = Input::get_instance();
	input.inputOnly(powerConsumption);
	return 1;
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:  checkDataInputArray - ��ȿ�� ����� ������ �ý��ۿ� ����ϴ� �Լ�
---------------------------------------------------------------------------------- */
void checkValue::checkDataInputArray(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray,
	int& type, const std::string& Name, int& powerConsumption) {

	//Appliance�� ����� ���� ���� ������. 4�� type�� ��ǰ�� ����� ����
	ApplianceFactory& factory = ApplianceFactory::get_instance();

	//�Էµ� type�� ��ǰ ���� ��������
	std::shared_ptr<Appliance> s = factory.create(type, Name, powerConsumption);

	//�ش� ���� applianceArray�� ���
	if (s) {
		applianceArray[type].push_back(s);
		applianceArray[type].back()->show();
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:  checkWarningName - �˸��� ���� �� �ִ� ��ǰ���� ��ȿ�� Ȯ��
---------------------------------------------------------------------------------- */
int checkValue::checkWarningName(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, std::string& Name) {
	//singleton ���� ���.Input class�� �����Ͽ� ���� �Է� ����(���ڸ� �Է¹޴� �Լ�)	
	Input& input = Input::get_instance();
	input.inputString(Name);

	//��ϵ� ��ǰ�� 1���� �����ϴ��� Ȯ��
	//��ǰ ���� ��, map�� vector ��� Ž���ؼ�, �Էµ� �̸��� ��ǰ�� ��ϵǾ� �ִ��� Ȯ�� �� return
	if (!applianceArray.empty()) {
		for (auto i : applianceArray) {
			auto& v = i.second;
			for (auto j : v) {
				if (j->get_title() == Name) {
					return 0;
				}
			}
		}
	}
	return 1;
}

