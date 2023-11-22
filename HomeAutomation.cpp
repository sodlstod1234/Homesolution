#include "HomeAutomation.h"

/*----------------------------------------------------------------------------------
Class Member�Լ� : mySystem - ������
					- �ش� �ý��� ���� ��, ���� �����͸� ȣ�������� ���� ���θ� ���� ��ġ
					- ���� initMenu()�� ���� �� ȣ��
----------------------------------------------------------------------------------*/
mySystem::mySystem() {
	int LoadOX;
	std::cout << "�����͸� �ҷ����ðڽ��ϱ�?(0 : No, 1 : Yes)";
	Input& input = Input::get_instance();
	input.inputAtoB(LoadOX, 0, 1);
	if (LoadOX == 1) {
		//DataLoad �Լ��� ���� ����� ���� Load
		DataLoad();
	}
	initMenu();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� : mySystem - �Ҹ���
					- �ش� �ý��� ���� ��, �����͸� ���������� ���� ���θ� ���� ��ġ
----------------------------------------------------------------------------------*/
mySystem::~mySystem() {
	int SaveOX;
	std::cout << "\n\n�����͸� �����Ͻðڽ��ϱ�?(0 : No, 1 : Yes)";
	Input& input = Input::get_instance();
	input.inputAtoB(SaveOX, 0, 1);
	if (SaveOX == 1) {
		DataSave();
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ� : initMenu - �ʱ� �޴� ����(��ü���� Ʋ�� ¥�� ��)
----------------------------------------------------------------------------------*/
void mySystem::initMenu()
{
	std::shared_ptr<PopupMenu> root = std::make_shared<PopupMenu>("HomeAutomationsystem", 1, std::bind(&mySystem::powerCal, this));
	std::shared_ptr<PopupMenu> menu2 = std::make_shared<PopupMenu>("������ǰ ����");
	std::shared_ptr<PopupMenu> menu4 = std::make_shared<PopupMenu>("������ǰ ����");
	std::shared_ptr<PopupMenu> menu5 = std::make_shared<PopupMenu>("��ǰ �˸� ����");

	root->add(std::make_shared<MenuItem>("������ǰ ����Ȯ��", std::bind(&mySystem::showAppliance, this)));
	root->add(menu2);
	root->add(std::make_shared<MenuItem>("������ǰ ���", std::bind(&mySystem::AddAppliance, this)));
	root->add(std::make_shared<MenuItem>("������ǰ ����", std::bind(&mySystem::deleteAppliance, this)));
	root->add(std::make_shared<MenuItem>("������ �����ϱ�", std::bind(&mySystem::DataSave, this)));
	root->add(std::make_shared<MenuItem>("������ �ε��ϱ�", std::bind(&mySystem::DataLoad, this)));
	root->add(menu5);

	menu2->add(std::make_shared<MenuItem>("��� ���� �ѱ�", std::bind(&mySystem::allTurnOnAppliance, this)));
	menu2->add(std::make_shared<MenuItem>("��� ���� ����", std::bind(&mySystem::allTurnOFFAppliance, this)));
	menu2->add(std::make_shared<MenuItem>("Ư����ǰ ����", std::bind(&mySystem::ControlAppliance, this)));

	menu5->add(std::make_shared<MenuItem>("�˸� ��ȣ ���", std::bind(&mySystem::addSmsNumber, this)));
	menu5->add(std::make_shared<MenuItem>("�˸� ��ȣ ����", std::bind(&mySystem::deleteSmsNumber, this)));
	menu5->add(std::make_shared<MenuItem>("�˸� ��ȣ ��Ȳ", std::bind(&mySystem::showSmsNumber, this)));

	root->command();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� : AddAppliance - ��ǰ�� ����ϱ� ���� ȣ��Ǵ� �Լ�
								(������ǰ ��� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::AddAppliance()
{
	system("cls");
	//��ǰ ����� ������ type�� ���
	std::cout << ("\n\nProduct type list==================================\n\n") << std::endl;
	std::cout << ("�ó����(type 1), ��Ź��(type 2), ���(type 3), ����(type 4)\n\n") << std::endl;
	printf("=======================================================\n");

	int type;
	std::string Name;
	int powerConsumption;
	//��� ��, �ԷµǴ� ������ ��ȿ�� �˻�
	//��ȿ�� �˻� �Ϸ�Ǹ� Data�� ���
	check.Addcheck(applianceArray, type, Name, powerConsumption);
	check.checkDataInputArray(applianceArray, type, Name, powerConsumption);
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  showAppliance - ��ϵ� ��ǰ ��Ȳ�� ���� ���� ȣ��Ǵ� �Լ�
								(������ǰ ����Ȯ�� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::showAppliance()
{
	system("cls");
	std::cout << "[�����ǰ ��Ȳ]\n" << std::endl;
	for (auto i : applianceArray)
	{
		auto& v = i.second;
		for (int j = 0; j < v.size(); j++) {
			v[j]->show();
		}
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  allTrunONAppliance - ��� ������ �� �� ȣ��Ǵ� �Լ�
								(������ǰ ����=>��� ���� �ѱ� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void  mySystem::allTurnOnAppliance()
{
	if (!applianceArray.empty()) {
		for (auto i : applianceArray) {
			auto& v = i.second;
			for (auto j : v) {
				j->set_powerFlag(1);
			}
		}
		std::cout << "��� �����ǰ ���� ON!" << std::endl;
	}
	else {
		std::cout << "���� ��ϵ� ��ǰ�� �����ϴ�." << std::endl;
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� : allTrunOFFAppliance - ��� ������ �� �� ȣ��Ǵ� �Լ�
								(������ǰ ����=>��� ���� ���� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::allTurnOFFAppliance()
{
	if (!applianceArray.empty()) {
		for (auto i : applianceArray) {
			auto& v = i.second;
			for (auto j : v) {
				j->set_powerFlag(0);
			}
		}
		std::cout << "��� �����ǰ ���� OFF!" << std::endl;
	}
	else {
		std::cout << "���� ��ϵ� ��ǰ�� �����ϴ�." << std::endl;
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  ControlAppliance - Ư�� ��ǰ�� ������ �� ȣ��Ǵ� �Լ�
								(������ǰ ����=>Ư�� ��ǰ ���� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::ControlAppliance() {
	int cnt = 0;
	std::string Name;
	std::cout << "��Ʈ���� ��ǰ �̸� �Է� :";
	std::cin >> Name;
	for (auto i : applianceArray) {
		auto& v = i.second;
		for (auto j : v) {
			//��ϵ� ��ǰ���� Ž���Ͽ� �Էµ� ��ǰ�� ������ ��ġ�� ã��
			//�� ��, �ش� ��ǰ�� ����/���¸� �����ϱ� ���� ControlMenu�� �߰� �Ҵ� �� ����
			if (j->get_title() == Name) {
				std::shared_ptr<PopupMenu> control = std::make_shared<PopupMenu>("ControlMenu");
				control->add(std::make_shared<MenuItem>("��ǰ ���� ����", std::bind(&mySystem::controlPower, this, j)));
				control->add(std::make_shared<MenuItem>("��ǰ ���� ����", std::bind(&mySystem::controlState, this, j)));
				cnt++;
				//�ϱ� �޴� ��� �� ����
				control->command();
			}
		}
	}

	if (cnt == 0) {
		std::cout << "���� ����� �ƴմϴ�." << std::endl;
		_getch();
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ� : controlPower - ������ �����ϴ� �Լ�
				(������ǰ ����=>Ư�� ��ǰ ����=> ��ǰ ���� ���� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::controlPower(std::shared_ptr<Appliance> Unit)
{
	Unit->show();
	int flag;
	printf("(���� ON : 1,���� OFF : 0) : ");
	Input& input = Input::get_instance();
	input.inputAtoB(flag, 0, 1);
	//�ش� ��ǰ�� ���� ���� ����
	Unit->set_powerFlag(flag);
	std::cout << "���� ���� �Ϸ�" << std::endl;
}

/*----------------------------------------------------------------------------------
Class Member�Լ� : controlState - ���¸� �����ϴ� �Լ�
				(������ǰ ����=>Ư�� ��ǰ ����=> ��ǰ ���� ���� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::controlState(std::shared_ptr<Appliance> Unit)
{
	if (Unit->get_powerFlag() == 0) {
		std::cout << "���� OFF ����!! ������ ���� ���ֽñ� �ٶ��ϴ�." << std::endl;
		_getch();
		return;
	}
	//�Ļ� Ŭ������ command�� ����
	Unit->command();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :deleteAppliance - ��ϵ� ��ǰ�� �����ϱ� ���� �Լ�
						(������ǰ ���� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::deleteAppliance()
{
	std::string delName;
	std::cout << "������ ��ǰ�� �̸��� �Է����ּ���. : ";
	Input& input = Input::get_instance();
	int cnt = 0;
	input.inputString(delName);
	for (auto& i : applianceArray)
	{
		auto& vec = i.second;
		auto v = std::find_if(vec.begin(), vec.end(), [&](std::shared_ptr<Appliance> p) {return p->get_title() == delName; });

		if (v == i.second.end()) {}
		else {
			cnt++;
			//�޴� ���� ��, �ش� ��ǰ �˸� ��û�� ��ȣ ������ �����ϱ� ���� deleteSmsKey �Լ� ȣ��
			SMSManager& sms = SMSManager::get_instance();
			sms.deleteSmsKey(delName);
			vec.erase(v);
			std::cout << "���� �Ϸ�" << std::endl;
		}
	}

	if (cnt == 0) { std::cout << "�ش� ��ǰ�� �����ϴ�." << std::endl; }

	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� powerCal - ���� ��, �Һ������� ����ϱ� ���� �Լ�
				(root���� ���� �޴� ���� �� ȣ��)
----------------------------------------------------------------------------------*/
void mySystem::powerCal() {
	std::cout << "\n\n" << "==================[�� �Һ����·� ���]==================" << "\n";
	for (auto i : applianceArray) {
		auto& v = i.second;
		for (auto j : v) {
			//������ ���� �ִ� ��ǰ�� ������ ���� OFF ����
			if (j->get_powerFlag() == 1) {
				j->set_state1("0");
				j->set_state2(0);
				j->set_powerFlag(0);
			}
			j->show();
			std::cout << "�Һ����·� : " << j->get_useHour() * j->get_powerConsumption() << std::endl;
		}
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ� addSmsNumber - ��ȣ�� ����ϱ� ���� �Լ�
				(��ǰ �˸� ���� => �˸� ��ȣ ��� �޴� ���� �� ����)
----------------------------------------------------------------------------------*/
void mySystem::addSmsNumber() {
	SMSManager& sms = SMSManager::get_instance();
	std::string number;
	std::string Name;
	int type = 0;
	std::cout << "�˸� ���� ��ȣ �Է� : ";
	std::cin >> number;
	std::cout << "�˸� ���� ��ǰ �̸� �Է�: ";
	if (check.checkWarningName(applianceArray, Name)==0) {
		sms.add_sms_number(Name, number);
	}
	else {
		std::cout << "\n��� ����[�ش���ǰ����]" << std::endl;
		_getch();
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ� showSmsNumber - ����� ��ȣ�� ���� ���� �Լ�
				(��ǰ �˸� ���� => �˸� ��ȣ ��Ȳ �޴� ���� �� ����)
----------------------------------------------------------------------------------*/
void mySystem::showSmsNumber() {
	SMSManager& sms = SMSManager::get_instance();
	sms.show();
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ�: deleteSmsNumber - ��ȣ�� �����ϱ� ���� �Լ�
				(��ǰ �˸� ���� => �˸� ��ȣ ���� �޴� ���� �� ����)
----------------------------------------------------------------------------------*/
void mySystem::deleteSmsNumber() {
	SMSManager& sms = SMSManager::get_instance();
	std::string number;
	std::string Name;
	sms.show();
	std::cout << "������ ��ȣ �Է� : ";
	std::cin >> number;
	sms.deleteSms(number);
}

/*----------------------------------------------------------------------------------
Class Member�Լ�: DataSave - ���� ��ϵ� ��ǰ�� �����͸� ���Ͽ� �����ϴ� �Լ�
				(������ �����ϱ� �޴� ���� �� ����)
----------------------------------------------------------------------------------*/
void mySystem::DataSave() {
	if (!applianceArray.empty()) {
		std::ofstream fout;
		fout.open("test.txt");
		for (auto i : applianceArray) {
			auto& v = i.second;
			for (auto j : v) {
				fout << j->get_type() << '\n' << j->get_title() << '\n' << j->get_powerConsumption() << '\n';
			}
		}
		fout.close();
	}
	std::cout << "������ ���� �Ϸ�" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ�:  DataLoad - ���� ��ϵ� ��ǰ�� �����͸� �ҷ����� �Լ�
				(������ �ε��ϱ� �޴� ���� �� ����)
----------------------------------------------------------------------------------*/
void mySystem::DataLoad() {
	int type;
	std::string Name;
	int powerConsumption;
	std::ifstream fin;
	fin.open("test.txt");
	applianceArray.clear();
	if (fin.is_open()) {
		while (fin >> type) {
			fin >> Name >> powerConsumption;
			check.checkDataInputArray(applianceArray, type, Name, powerConsumption);
		}
	}
	std::cout << "[������ ��� �Ϸ�]";
	_getch();
}