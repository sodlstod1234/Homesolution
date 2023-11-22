#include "SMSManager.h"

/*----------------------------------------------------------------------------------
Class Member함수: get_instance() - singleton 패턴/ class 접근하기 위해 사용해야하는 함수
----------------------------------------------------------------------------------*/
SMSManager& SMSManager::get_instance()
{
	static SMSManager sms;
	return sms;
}

/*----------------------------------------------------------------------------------
Class Member함수:add_sms_number - 해당 번호 등록되었음을 출력하는 함수
----------------------------------------------------------------------------------*/
void SMSManager::add_sms_number(const std::string& number)
{
	std::cout << number << "등록" << std::endl;
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수:add_sms_number - 멤버 변수 map에 번호를 추가하는 함수
----------------------------------------------------------------------------------*/
void SMSManager::add_sms_number(const std::string& Name, const PHONENUMBER& number)
{
	//map 탐색을 통해 해당 제품 알람을 요청한 number가 있는지 확인
	auto it = std::find(m[Name].begin(), m[Name].end(), number);
	if (it == m[Name].end()) {
		//등록되어 있지 않은 번호면 등록
		m[Name].push_back(number);
		std::cout << "등록" << std::endl;
	}
	else {
		std::cout << "기등록" << std::endl;
	}
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수: deleteSms - 번호를 삭제하고 싶을 때 호출하는 함수
----------------------------------------------------------------------------------*/
void SMSManager::deleteSms(const std::string& Number)
{
	int cnt = 0;
	//m의 key 탐색
	std::for_each(m.begin(), m.end(), [&Number,&cnt](auto& pair) {
		std::vector<std::string>& v = pair.second;
		//해당 key에 입력된 값과 같은 번호가 등록되었는지 탐색 
		auto it = std::find(v.begin(), v.end(), Number);
		if (it != v.end()) {
			v.erase(it);
			cnt++;
			std::cout << "번호 삭제" << std::endl;
		}
	});
	if (cnt == 0) { std::cout << "번호 등록 필요" << std::endl; }
	_getch();
}

/*----------------------------------------------------------------------------------
Class Member함수: deleteSmsKey - 제품이 삭제될 시 호출되어 연동된 번호도 함께 삭제하는 함수
----------------------------------------------------------------------------------*/
void SMSManager::deleteSmsKey(const std::string& Name) {
	auto it = m.find(Name);
	if (it != m.end()) {
		m.erase(it);
	}
}

/*----------------------------------------------------------------------------------
Class Member함수: send_sms - 문자를 보낼 때 호출되는 함수
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
Class Member함수: show - 저장된 번호의 현황을 표시
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


