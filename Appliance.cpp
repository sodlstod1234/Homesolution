#include "Appliance.h"

/*----------------------------------------------------------------------------------
Class Member함수 :  Appliance - 생성자
					 인자들을 Appliance 멤버 변수에 저장 및 멤버 변수 초기화
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
Class Member함수 :  set_powerFlag - 멤버 변수 pwoerFlag를 변경할 때사용
----------------------------------------------------------------------------------*/
void Appliance::set_powerFlag(bool powerFlag) {
	//해당 제품의 전원상태를 체크해서 전원이 이전과 바뀌는 입력이 요청되었을 때만
	//상태 및 시간 등을 값을 수정
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
	else { std::cout << "[제품명 : " << this->get_title() << "]이 이미 전원 " << powerFlagName[powerFlag] << " 상태입니다." << std::endl; }
	this->powerFlag = powerFlag;
}

/*----------------------------------------------------------------------------------
Class Member함수 :  set_state1 - 멤버 변수 stete1를 변경할 때사용
					-- 각 제품의 type을 확인해서 "0" <= 초기화 값이 들어왔을 때 다른 값을 저장
----------------------------------------------------------------------------------*/
void Appliance::set_state1(std::string state1) {
	if (state1 == "0") {
		switch (get_type()) {
		case 1:state1 = "SENDAIR"; break;
		default:
			state1 = "무동작"; break;
		}
	}
	this->state1 = state1;
}

/*----------------------------------------------------------------------------------
Class Member함수 :  show - 해당 제품의 정보를 출력
----------------------------------------------------------------------------------*/
void Appliance::show() {
	if (powerFlag) {
		std::cout << "제품 이름 : " << get_title();
		printf(", 제품 타입 : %d, 제품 소비전력 : %d", get_type(), get_powerConsumption());
		std::cout << ", 제품 상태 : " << get_state1();
		showadd();
	}
	else {
		std::cout << "제품 이름 : " << get_title();
		printf(", 제품 타입 : %d, 제품 소비전력 : %d \n", get_type(), get_powerConsumption());
	}
}

/*----------------------------------------------------------------------------------
Class Member함수 :  create - main()실행 전에 호출되어 등록할 제품 생성하기 위한 함수
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
Class Member함수 :  command - Airconditoner의 명령을 저장한 함수
					Airconditoner은 추가 제어 메뉴가 있으므로 메뉴 추가 할당
----------------------------------------------------------------------------------*/
void Airconditoner::command() {
	std::shared_ptr<PopupMenu> control = std::make_shared<PopupMenu>("ControlMenu");
	control->add(std::make_shared<MenuItem>("냉난방기 상태 제어", std::bind(&Airconditoner::command_state1, this)));
	control->add(std::make_shared<MenuItem>("냉난방기 온도 제어", std::bind(&Airconditoner::command_state2, this)));

	control->command();
}

/*----------------------------------------------------------------------------------
Class Member함수 :  command_state1 - Airconditoner의 상태를 변경하는 함수
----------------------------------------------------------------------------------*/
void Airconditoner::command_state1() {
	show();
	std::cout << std::endl;
	
	int state1;
	std::vector<std::string> stateName = { "SENDAIR", "COOLER", "HEATER", };
	std::cout << "제품 상태(";
	for (int i = 0; i < stateName.size(); i++) {
		std::cout << i+1 << ":" << stateName[i] << "  ";
	}
	std::cout << ") :";

	Input& input = Input::get_instance();
	input.inputAtoB(state1, 1, 3);
	set_state1(stateName[state1-1]);

	std::cout << "상태 변경 완료" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 :  command_state1 - Airconditoner의 온도를 변경하는 함수
----------------------------------------------------------------------------------*/
void Airconditoner::command_state2() {
	show();
	int state2;
	printf("냉난방기 설정 온도(18도~30도) : ");
	Input& input = Input::get_instance();
	input.inputAtoB(state2, 18, 30);
	set_state2(state2);
	std::cout << "상태 변경 완료" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 :  create - Airconditoner 스스로를 만드는 정적 멤버 함수 create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> Airconditoner::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Airconditoner> p = std::make_shared<Airconditoner>(type, machineName, powerConsumption);
	return p;
}
//스스로 만들고 공장에 등록
AutoRegister Airconditoner::ar(1, &Airconditoner::create);

/*----------------------------------------------------------------------------------
Class Member함수 :  command - RiceCooker의 명령을 저장한 함수
----------------------------------------------------------------------------------*/
void RiceCooker::command() {
	show();
	std::cout << std::endl;
	int state1;
	int cnt = 1;
	std::string stateName[4] = { "무동작", "보온", "밥짓기", "데우기" };
	std::for_each(stateName, stateName + 4, [&cnt](std::string Name) {std::cout << cnt << ":" << Name << ", "; cnt++; });
	Input& input = Input::get_instance();
	input.inputAtoB(state1, 1, 4);
	set_state1(stateName[state1-1]);
	std::cout << "상태 변경 완료" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 :  create - RiceCooker 스스로를 만드는 정적 멤버 함수 create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> RiceCooker::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<RiceCooker> p = std::make_shared<RiceCooker>(type, machineName, powerConsumption);
	return p;
}
AutoRegister RiceCooker::ar(2, &RiceCooker::create);

/*----------------------------------------------------------------------------------
Class Member함수 :  command - Washer의 명령을 저장한 함수
----------------------------------------------------------------------------------*/
void Washer::command() {
	show(); 
	std::cout << std::endl;
	int state1;
	int cnt = 1;
	std::string stateName[4] = { "무동작", "일반빨래", "삶은 빨래", "건조" };
	std::for_each(stateName, stateName + 4, [&cnt](std::string Name) {std::cout << cnt << ":" << Name << ", "; cnt++; });
	Input& input = Input::get_instance();
	input.inputAtoB(state1, 1, 4);
	set_state1(stateName[state1-1]);
	std::cout << "상태 변경 완료" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 :  create - Washer 스스로를 만드는 정적 멤버 함수 create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> Washer::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Washer> p = std::make_shared<Washer>(type, machineName, powerConsumption);
	return p;
}
AutoRegister Washer::ar(3, &Washer::create);

/*----------------------------------------------------------------------------------
Class Member함수 :  create - Light 스스로를 만드는 정적 멤버 함수 create
----------------------------------------------------------------------------------*/
std::shared_ptr<Appliance> Light::create(int type, std::string machineName, int powerConsumption) {
	std::shared_ptr<Light> p = std::make_shared<Light>(type, machineName, powerConsumption);
	return p;
}
AutoRegister Light::ar(4, &Light::create);