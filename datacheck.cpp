#include "datacheck.h"

/*----------------------------------------------------------------------------------
Class Member함수: Addcheck - 사용자가 입력한 제품이 등록가능한지 체크하는 함수
---------------------------------------------------------------------------------- */
void checkValue::Addcheck(std::map < int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, int& type, std::string& Name, int& powerConsumption) {
	//class 내 멤버 함수를 통해 Type, Name, powerConsumption에 대한 유효성을 확인하여 등록 가능 여부 판단
	if (checkType(type) == 0 || checkName(applianceArray, Name) == 0 || checkPower(powerConsumption) == 0) {
		type = 0;
		return;
	}
	std::cout << ("등록 가능 제품. 등록 진행\n") << std::endl;
}

/*----------------------------------------------------------------------------------
Class Member함수:  checkType - 사용자가 입력한 Type 유효성 확인
---------------------------------------------------------------------------------- */
int checkValue::checkType(int& type) {
	std::cout << "제품 type 입력 :";
	//singleton 패턴 사용.Input class에 접근하여 값 입력 받음(1~4까지의 숫자만 입력받는 함수)
	Input& input = Input::get_instance();
	input.inputAtoB(type, 1, 4);
	return 1;
}

/*----------------------------------------------------------------------------------
Class Member함수:  checkName - 사용자가 입력한 제품 이름의 유효성(기등록 여부) 확인
							 - 이중 for문을 통해, ApplianceArray의 등록 제품 이름과 비교
---------------------------------------------------------------------------------- */
int checkValue::checkName(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, std::string& Name) {
	std::cout << "제품 이름 입력 :";
	//singleton 패턴 사용.Input class에 접근하여 문자 입력 받음(문자만 입력받는 함수)
	Input& input = Input::get_instance();
	input.inputString(Name);
	if (!applianceArray.empty()) {
		for (auto i : applianceArray) {
			auto& v = i.second;
			for (auto j : v) {
				if (j->get_title() == Name) {
					std::cout << "이미 등록된 제품입니다.\n";
					_getch();
					return 0;
				}
			}
		}
	}
	return 1;
}
/*----------------------------------------------------------------------------------
Class Member함수:  checkPower - 사용자가 입력한 소비전력의 유효성 확인
---------------------------------------------------------------------------------- */
int checkValue::checkPower(int& powerConsumption) {
	std::cout << "제품 소비전력 입력 :";
	//singleton 패턴 사용.Input class에 접근하여 입력 받음(숫자만 입력받는 함수)
	Input& input = Input::get_instance();
	input.inputOnly(powerConsumption);
	return 1;
}

/*----------------------------------------------------------------------------------
Class Member함수:  checkDataInputArray - 유효성 통과한 값들을 시스템에 등록하는 함수
---------------------------------------------------------------------------------- */
void checkValue::checkDataInputArray(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray,
	int& type, const std::string& Name, int& powerConsumption) {

	//Appliance를 만드는 공장 참조 얻어오기. 4개 type의 제품을 등록한 공장
	ApplianceFactory& factory = ApplianceFactory::get_instance();

	//입력된 type의 제품 정보 가져오기
	std::shared_ptr<Appliance> s = factory.create(type, Name, powerConsumption);

	//해당 정보 applianceArray에 등록
	if (s) {
		applianceArray[type].push_back(s);
		applianceArray[type].back()->show();
	}
}

/*----------------------------------------------------------------------------------
Class Member함수:  checkWarningName - 알림을 보낼 수 있는 제품인지 유효성 확인
---------------------------------------------------------------------------------- */
int checkValue::checkWarningName(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, std::string& Name) {
	//singleton 패턴 사용.Input class에 접근하여 문자 입력 받음(문자만 입력받는 함수)	
	Input& input = Input::get_instance();
	input.inputString(Name);

	//등록된 제품이 1개라도 존재하는지 확인
	//제품 있을 시, map과 vector 모두 탐색해서, 입력된 이름의 제품이 등록되어 있는지 확인 후 return
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

