#pragma once
#pragma warning(disable :6031)
#include "menu.h"

/*----------------------------------------------------------------------------------
Class name	    : SMSManager - 알림을 받을 휴대폰 번호를 등록 및 문자 전송하는 함수
Class 멤버 변수 : map<> m - 전원 ON을 감지하고 싶은 제품 이름과 전송 받을 번호를 저장하는 map

Class Member함수: add_sms_number - 멤버 변수 map에 번호를 추가하는 함수
			      send_sms - 문자를 보낼 때 호출되는 함수
				  deleteSms - 번호를 삭제하고 싶을 때 호출하는 함수
				  deleteSmsKey - 제품이 삭제될 시 호출되어 연동된 번호도 함께 삭제하는 함수
				  show - 저장된 번호의 현황을 표시
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
