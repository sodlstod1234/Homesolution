#include "HomeAutomation.h"

/*----------------------------------------------------------------------------------
Class Member함수 : mySystem - 생성자
					- 해당 시스템 실행 시, 이전 데이터를 호출할지에 대한 여부를 묻는 위치
					- 또한 initMenu()를 생성 시 호출
----------------------------------------------------------------------------------*/
mySystem::mySystem() {
	int LoadOX;
	std::cout << "데이터를 불러오시겠습니까?(0 : No, 1 : Yes)";
	Input& input = Input::get_instance();
	input.inputAtoB(LoadOX, 0, 1);
	if (LoadOX == 1) {
		//DataLoad 함수를 통해 저장된 정보 Load
		DataLoad();
	}
	initMenu();
}

/*----------------------------------------------------------------------------------
Class Member함수 : mySystem - 소멸자
					- 해당 시스템 종료 시, 데이터를 저장할지에 대한 여부를 묻는 위치
----------------------------------------------------------------------------------*/
mySystem::~mySystem() {
	int SaveOX;
	std::cout << "\n\n데이터를 저장하시겠습니까?(0 : No, 1 : Yes)";
	Input& input = Input::get_instance();
	input.inputAtoB(SaveOX, 0, 1);
	if (SaveOX == 1) {
		DataSave();
	}
}

/*----------------------------------------------------------------------------------
Class Member함수 : initMenu - 초기 메뉴 세팅(전체적인 틀을 짜는 곳)
----------------------------------------------------------------------------------*/
void mySystem::initMenu()
{
	std::shared_ptr<PopupMenu> root = std::make_shared<PopupMenu>("HomeAutomationsystem", 1, std::bind(&mySystem::powerCal, this));
	std::shared_ptr<PopupMenu> menu2 = std::make_shared<PopupMenu>("가전제품 제어");
	std::shared_ptr<PopupMenu> menu4 = std::make_shared<PopupMenu>("가전제품 삭제");
	std::shared_ptr<PopupMenu> menu5 = std::make_shared<PopupMenu>("제품 알림 설정");

	root->add(std::make_shared<MenuItem>("가전제품 상태확인", std::bind(&mySystem::showAppliance, this)));
	root->add(menu2);
	root->add(std::make_shared<MenuItem>("가전제품 등록", std::bind(&mySystem::AddAppliance, this)));
	root->add(std::make_shared<MenuItem>("가전제품 삭제", std::bind(&mySystem::deleteAppliance, this)));
	root->add(std::make_shared<MenuItem>("데이터 저장하기", std::bind(&mySystem::DataSave, this)));
	root->add(std::make_shared<MenuItem>("데이터 로드하기", std::bind(&mySystem::DataLoad, this)));
	root->add(menu5);

	menu2->add(std::make_shared<MenuItem>("모든 전원 켜기", std::bind(&mySystem::allTurnOnAppliance, this)));
	menu2->add(std::make_shared<MenuItem>("모든 전원 끄기", std::bind(&mySystem::allTurnOFFAppliance, this)));
	menu2->add(std::make_shared<MenuItem>("특정제품 제어", std::bind(&mySystem::ControlAppliance, this)));

	menu5->add(std::make_shared<MenuItem>("알림 번호 등록", std::bind(&mySystem::addSmsNumber, this)));
	menu5->add(std::make_shared<MenuItem>("알림 번호 해제", std::bind(&mySystem::deleteSmsNumber, this)));
	menu5->add(std::make_shared<MenuItem>("알림 번호 현황", std::bind(&mySystem::showSmsNumber, this)));

	root->command();
}

/*----------------------------------------------------------------------------------
Class Member함수 : AddAppliance - 제품을 등록하기 위해 호출되는 함수
								(가전제품 등록 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::AddAppliance()
{
	system("cls");
	//제품 등록이 가능한 type을 출력
	std::cout << ("\n\nProduct type list==================================\n\n") << std::endl;
	std::cout << ("냉난방기(type 1), 세탁기(type 2), 밥솥(type 3), 전등(type 4)\n\n") << std::endl;
	printf("=======================================================\n");

	int type;
	std::string Name;
	int powerConsumption;
	//등록 시, 입력되는 값들의 유효성 검사
	//유효성 검사 완료되면 Data를 등록
	check.Addcheck(applianceArray, type, Name, powerConsumption);
	check.checkDataInputArray(applianceArray, type, Name, powerConsumption);
}

/*----------------------------------------------------------------------------------
Class Member함수 :  showAppliance - 등록된 제품 현황을 보기 위해 호출되는 함수
								(가전제품 상태확인 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::showAppliance()
{
	system("cls");
	std::cout << "[등록제품 현황]\n" << std::endl;
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
Class Member함수 :  allTrunONAppliance - 모든 전원을 켤 때 호출되는 함수
								(가전제품 제어=>모든 전원 켜기 메뉴 선택 시 호출)
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
		std::cout << "모든 등록제품 전원 ON!" << std::endl;
	}
	else {
		std::cout << "현재 등록된 제품이 없습니다." << std::endl;
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 : allTrunOFFAppliance - 모든 전원을 끌 때 호출되는 함수
								(가전제품 제어=>모든 전원 끄기 메뉴 선택 시 호출)
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
		std::cout << "모든 등록제품 전원 OFF!" << std::endl;
	}
	else {
		std::cout << "현재 등록된 제품이 없습니다." << std::endl;
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 :  ControlAppliance - 특정 제품을 제어할 때 호출되는 함수
								(가전제품 제어=>특정 제품 제어 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::ControlAppliance() {
	int cnt = 0;
	std::string Name;
	std::cout << "컨트롤할 제품 이름 입력 :";
	std::cin >> Name;
	for (auto i : applianceArray) {
		auto& v = i.second;
		for (auto j : v) {
			//등록된 제품들을 탐색하여 입력된 제품과 동일한 위치를 찾음
			//그 후, 해당 제품의 전원/상태를 제어하기 위한 ControlMenu를 추가 할당 및 실행
			if (j->get_title() == Name) {
				std::shared_ptr<PopupMenu> control = std::make_shared<PopupMenu>("ControlMenu");
				control->add(std::make_shared<MenuItem>("제품 전원 제어", std::bind(&mySystem::controlPower, this, j)));
				control->add(std::make_shared<MenuItem>("제품 상태 제어", std::bind(&mySystem::controlState, this, j)));
				cnt++;
				//하기 메뉴 출력 및 실행
				control->command();
			}
		}
	}

	if (cnt == 0) {
		std::cout << "제어 대상이 아닙니다." << std::endl;
		_getch();
	}
}

/*----------------------------------------------------------------------------------
Class Member함수 : controlPower - 전원을 제어하는 함수
				(가전제품 제어=>특정 제품 제어=> 제품 전원 제어 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::controlPower(std::shared_ptr<Appliance> Unit)
{
	Unit->show();
	int flag;
	printf("(전원 ON : 1,전원 OFF : 0) : ");
	Input& input = Input::get_instance();
	input.inputAtoB(flag, 0, 1);
	//해당 제품의 전원 상태 변경
	Unit->set_powerFlag(flag);
	std::cout << "전원 변경 완료" << std::endl;
}

/*----------------------------------------------------------------------------------
Class Member함수 : controlState - 상태를 제어하는 함수
				(가전제품 제어=>특정 제품 제어=> 제품 상태 제어 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::controlState(std::shared_ptr<Appliance> Unit)
{
	if (Unit->get_powerFlag() == 0) {
		std::cout << "전원 OFF 상태!! 전원을 먼저 켜주시기 바랍니다." << std::endl;
		_getch();
		return;
	}
	//파생 클래스의 command를 실행
	Unit->command();
}

/*----------------------------------------------------------------------------------
Class Member함수 :deleteAppliance - 등록된 제품을 삭제하기 위한 함수
						(가전제품 삭제 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::deleteAppliance()
{
	std::string delName;
	std::cout << "삭제할 제품의 이름을 입력해주세요. : ";
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
			//메뉴 삭제 시, 해당 제품 알림 요청한 번호 있으면 삭제하기 위해 deleteSmsKey 함수 호출
			SMSManager& sms = SMSManager::get_instance();
			sms.deleteSmsKey(delName);
			vec.erase(v);
			std::cout << "삭제 완료" << std::endl;
		}
	}

	if (cnt == 0) { std::cout << "해당 제품이 없습니다." << std::endl; }

	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수 powerCal - 종료 시, 소비전력을 계산하기 위한 함수
				(root에서 종료 메뉴 선택 시 호출)
----------------------------------------------------------------------------------*/
void mySystem::powerCal() {
	std::cout << "\n\n" << "==================[총 소비전력량 계산]==================" << "\n";
	for (auto i : applianceArray) {
		auto& v = i.second;
		for (auto j : v) {
			//전원이 켜져 있는 제품이 있으면 전원 OFF 진행
			if (j->get_powerFlag() == 1) {
				j->set_state1("0");
				j->set_state2(0);
				j->set_powerFlag(0);
			}
			j->show();
			std::cout << "소비전력량 : " << j->get_useHour() * j->get_powerConsumption() << std::endl;
		}
	}
}

/*----------------------------------------------------------------------------------
Class Member함수 addSmsNumber - 번호를 등록하기 위한 함수
				(제품 알림 설정 => 알림 번호 등록 메뉴 선택 시 실행)
----------------------------------------------------------------------------------*/
void mySystem::addSmsNumber() {
	SMSManager& sms = SMSManager::get_instance();
	std::string number;
	std::string Name;
	int type = 0;
	std::cout << "알림 받을 번호 입력 : ";
	std::cin >> number;
	std::cout << "알림 받을 제품 이름 입력: ";
	if (check.checkWarningName(applianceArray, Name)==0) {
		sms.add_sms_number(Name, number);
	}
	else {
		std::cout << "\n등록 실패[해당제품없음]" << std::endl;
		_getch();
	}
}

/*----------------------------------------------------------------------------------
Class Member함수 showSmsNumber - 저장된 번호를 보기 위한 함수
				(제품 알림 설정 => 알림 번호 현황 메뉴 선택 시 실행)
----------------------------------------------------------------------------------*/
void mySystem::showSmsNumber() {
	SMSManager& sms = SMSManager::get_instance();
	sms.show();
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수: deleteSmsNumber - 번호를 삭제하기 위한 함수
				(제품 알림 설정 => 알림 번호 해제 메뉴 선택 시 실행)
----------------------------------------------------------------------------------*/
void mySystem::deleteSmsNumber() {
	SMSManager& sms = SMSManager::get_instance();
	std::string number;
	std::string Name;
	sms.show();
	std::cout << "삭제할 번호 입력 : ";
	std::cin >> number;
	sms.deleteSms(number);
}

/*----------------------------------------------------------------------------------
Class Member함수: DataSave - 현재 등록된 제품의 데이터를 파일에 저장하는 함수
				(데이터 저장하기 메뉴 선택 시 실행)
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
	std::cout << "데이터 저장 완료" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수:  DataLoad - 현재 등록된 제품의 데이터를 불러오는 함수
				(데이터 로드하기 메뉴 선택 시 실행)
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
	std::cout << "[데이터 등록 완료]";
	_getch();
}