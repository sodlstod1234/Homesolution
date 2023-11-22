#ifndef DATACHECK_H__
#define DATACHECK_H__
#include "datacheck.h"

/*----------------------------------------------------------------------------------
Class name	    : mySystem - 시스템을 관리하는 class
Class 멤버 변수 : check - checkvalue class를 멤버 변수로 가지고 있음
				  apllianceArray - 제품들을 보관하는 map. 제품의 type을 key로 갖고,
								   해당 key의 value로 appliance* class 형을 갖는 vector 보관
Class Member함수 : AddAppliance - 제품을 등록하기 위해 호출되는 함수
				   initMenu - 초기 메뉴 등록
                   add - 제품 등록하는 함수
				   showAppliance - 등록된 제품 현황을 보기 위해 호출되는 함수
				   allTrunONAppliance - 모든 전원을 켤 때 호출되는 함수
				    allTrunOFFAppliance - 모든 전원을 끌 때 호출되는 함수
				   ControlAppliance - 특정 제품을 제어할 때 호출되는 함수
				   controlPower - 전원을 제어하는 함수
				   controlState - 상태를 제어하는 함수
				   deleteAppliance - 등록된 제품을 삭제하기 위한 함수
				   powerCal - 종료 시, 소비전력을 계산하기 위한 함수
				   addSmsNumber - 번호를 등록하기 위한 함수
				   deleteSmsNumber - 번호를 삭제하기 위한 함수
				   showSmsNumber - 저장된 번호를 보기 위한 함수
				   DataSave - 현재 등록된 제품의 데이터를 파일에 저장하는 함수
				   DataLoad - 현재 등록된 제품의 데이터를 불러오는 함수
----------------------------------------------------------------------------------*/
class mySystem 
{
	checkValue check;
	std::map <int, std::vector<std::shared_ptr<Appliance>>> applianceArray;
public:
	mySystem();

	~mySystem();
	
	void initMenu();
	//void add(int type, std::shared_ptr<Appliance> p) {applianceArray[type].push_back(p);}
	void AddAppliance();
	void showAppliance();

	void allTurnOnAppliance();
	void allTurnOFFAppliance();
	void ControlAppliance();
	void controlPower(std::shared_ptr<Appliance> Unit);
	void controlState(std::shared_ptr<Appliance> Unit);
	void deleteAppliance();
	void powerCal();
	void addSmsNumber();
	void showSmsNumber();
	void deleteSmsNumber();
	void DataSave();
	void DataLoad();
};
#endif