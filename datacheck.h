#pragma once
#include "Appliance.h"


/*----------------------------------------------------------------------------------
Class name	    : checkValue - 입력된 Data에 대한 유효성을 확인하는 함수
Class Member함수: Addcheck - 사용자가 입력한 제품이 등록가능한지 체크하는 함수
                  checkType - 사용자가 입력한 Type 유효성 확인
				  checkName - 사용자가 입력한 제품 이름의 유효성(기등록 여부) 확인
				  checkPower - 사용자가 입력한 소비전력의 유효성 확인
				  checkDataInputArray - 유효성 통과한 값들을 시스템에 등록하는 함수
				  checkWarningName - 알림을 보낼 수 있는 제품인지 유효성 확인
----------------------------------------------------------------------------------*/
class checkValue
{
public:
	void Addcheck(std::map < int, std::vector<std::shared_ptr<Appliance>>>& applianceArray,
	int& type, std::string& Name, int& powerConsumption);
	int checkType(int& type);
	int checkName(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, std::string& Name);
	int checkPower(int& powerConsumption);
	void checkDataInputArray(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray,int& type, const std::string& Name, int& powerConsumption);
	int checkWarningName(std::map <int, std::vector<std::shared_ptr<Appliance>>>& applianceArray, std::string& Name);

};
