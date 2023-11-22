#include "Appliance.h"

/*----------------------------------------------------------------------------------
Class Member�Լ� :  Appliance - ������
					 ���ڵ��� Appliance ��� ������ ���� �� ��� ���� �ʱ�ȭ
----------------------------------------------------------------------------------*/
Appliance::Appliance(int _type, const std::string& s, int p) : _type(_type), machineName(s), powerConsumption(p) {
	this->powerFlag = 0;
	startHour = 0;
	useHour = 0;
	if (currentTime == 0) {
		currentTime = time(nullptr);
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  set_powerFlag - ��� ���� pwoerFlag�� ������ �����
----------------------------------------------------------------------------------*/
void Appliance::set_powerFlag(bool powerFlag) {
	//�ش� ��ǰ�� �������¸� üũ�ؼ� ������ ������ �ٲ�� �Է��� ��û�Ǿ��� ����
	//���� �� �ð� ���� ���� ����
	if (this->powerFlag != powerFlag) {
		this->set_state1("0");
		this->set_state2(0);
		if (powerFlag == 0) {
			this->useHour += time(&currentTime) - this->startHour;
		}
		else if (powerFlag == 1) {
			this->startHour = time(&currentTime);
			this->warningSend();
		}
	}
	else { std::cout << "[��ǰ�� : " << this->get_title() << "]�� �̹� ���� " << powerFlagName[powerFlag] << " �����Դϴ�." << std::endl; }
	this->powerFlag = powerFlag;
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  set_state1 - ��� ���� stete1�� ������ �����
					-- �� ��ǰ�� type�� Ȯ���ؼ� "0" <= �ʱ�ȭ ���� ������ �� �ٸ� ���� ����
----------------------------------------------------------------------------------*/
void Appliance::set_state1(std::string state1) {
	if (state1 == "0") {
		switch (get_type()) {
		case 1:state1 = "SENDAIR"; break;
		default:
			state1 = "������"; break;
		}
	}
	this->state1 = state1;
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  show - �ش� ��ǰ�� ������ ���
----------------------------------------------------------------------------------*/
void Appliance::show() {
	if (powerFlag) {
		std::cout << "��ǰ �̸� : " << get_title();
		printf(", ��ǰ Ÿ�� : %d, ��ǰ �Һ����� : %d", get_type(), get_powerConsumption());
		std::cout << ", ��ǰ ���� : " << get_state1();
		showadd();
	}
	else {
		std::cout << "��ǰ �̸� : " << get_title();
		printf(", ��ǰ Ÿ�� : %d, ��ǰ �Һ����� : %d \n", get_type(), get_powerConsumption());
	}
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  create - main()���� ���� ȣ��Ǿ� ����� ��ǰ �����ϱ� ���� �Լ�
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> ApplianceFactory::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Appliance> s = nullptr;
	auto f = m.find(type);
	if (f != m.end()) {
		s = f->second(type, machineName, powerConsumption);
		return s;
	}
}

ApplianceFactory& ApplianceFactory::get_instance() {
	static ApplianceFactory factory;
	return factory;
}

AutoRegister::AutoRegister(int type, std::shared_ptr<Appliance>(*f)(int type, std::string Name, int powerConsumption)) {
	ApplianceFactory& factory = ApplianceFactory::get_instance();
	factory.register_Appliance(type, f);
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  command - Airconditoner�� ����� ������ �Լ�
					Airconditoner�� �߰� ���� �޴��� �����Ƿ� �޴� �߰� �Ҵ�
----------------------------------------------------------------------------------*/
void Airconditoner::command() {
	std::shared_ptr<PopupMenu> control = std::make_shared<PopupMenu>("ControlMenu");
	control->add(std::make_shared<MenuItem>("�ó���� ���� ����", std::bind(&Airconditoner::command_state1, this)));
	control->add(std::make_shared<MenuItem>("�ó���� �µ� ����", std::bind(&Airconditoner::command_state2, this)));

	control->command();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  command_state1 - Airconditoner�� ���¸� �����ϴ� �Լ�
----------------------------------------------------------------------------------*/
void Airconditoner::command_state1() {
	show();
	std::cout << std::endl;
	
	int state1;
	std::vector<std::string> stateName = { "SENDAIR", "COOLER", "HEATER", };
	std::cout << "��ǰ ����(";
	for (int i = 0; i < stateName.size(); i++) {
		std::cout << i+1 << ":" << stateName[i] << "  ";
	}
	std::cout << ") :";

	Input& input = Input::get_instance();
	input.inputAtoB(state1, 1, 3);
	set_state1(stateName[state1-1]);

	std::cout << "���� ���� �Ϸ�" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  command_state1 - Airconditoner�� �µ��� �����ϴ� �Լ�
----------------------------------------------------------------------------------*/
void Airconditoner::command_state2() {
	show();
	int state2;
	printf("�ó���� ���� �µ�(18��~30��) : ");
	Input& input = Input::get_instance();
	input.inputAtoB(state2, 18, 30);
	set_state2(state2);
	std::cout << "���� ���� �Ϸ�" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  create - Airconditoner �����θ� ����� ���� ��� �Լ� create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> Airconditoner::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Airconditoner> p = std::make_shared<Airconditoner>(type, machineName, powerConsumption);
	return p;
}
//������ ����� ���忡 ���
AutoRegister Airconditoner::ar(1, &Airconditoner::create);

/*----------------------------------------------------------------------------------
Class Member�Լ� :  command - RiceCooker�� ����� ������ �Լ�
----------------------------------------------------------------------------------*/
void RiceCooker::command() {
	show();
	std::cout << std::endl;
	int state1;
	int cnt = 1;
	std::string stateName[4] = { "������", "����", "������", "�����" };
	std::for_each(stateName, stateName + 4, [&cnt](std::string Name) {std::cout << cnt << ":" << Name << ", "; cnt++; });
	Input& input = Input::get_instance();
	input.inputAtoB(state1, 1, 4);
	set_state1(stateName[state1-1]);
	std::cout << "���� ���� �Ϸ�" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  create - RiceCooker �����θ� ����� ���� ��� �Լ� create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> RiceCooker::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<RiceCooker> p = std::make_shared<RiceCooker>(type, machineName, powerConsumption);
	return p;
}
AutoRegister RiceCooker::ar(2, &RiceCooker::create);

/*----------------------------------------------------------------------------------
Class Member�Լ� :  command - Washer�� ����� ������ �Լ�
----------------------------------------------------------------------------------*/
void Washer::command() {
	show(); 
	std::cout << std::endl;
	int state1;
	int cnt = 1;
	std::string stateName[4] = { "������", "�Ϲݻ���", "���� ����", "����" };
	std::for_each(stateName, stateName + 4, [&cnt](std::string Name) {std::cout << cnt << ":" << Name << ", "; cnt++; });
	Input& input = Input::get_instance();
	input.inputAtoB(state1, 1, 4);
	set_state1(stateName[state1-1]);
	std::cout << "���� ���� �Ϸ�" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member�Լ� :  create - Washer �����θ� ����� ���� ��� �Լ� create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> Washer::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Washer> p = std::make_shared<Washer>(type, machineName, powerConsumption);
	return p;
}
AutoRegister Washer::ar(3, &Washer::create);

/*----------------------------------------------------------------------------------
Class Member�Լ� :  create - Light �����θ� ����� ���� ��� �Լ� create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> Light::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Light> p = std::make_shared<Light>(type, machineName, powerConsumption);
	return p;
}
AutoRegister Light::ar(4, &Light::create);