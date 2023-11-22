#ifndef DATACHECK_H__
#define DATACHECK_H__
#include "datacheck.h"

/*----------------------------------------------------------------------------------
Class name	    : mySystem - �ý����� �����ϴ� class
Class ��� ���� : check - checkvalue class�� ��� ������ ������ ����
				  apllianceArray - ��ǰ���� �����ϴ� map. ��ǰ�� type�� key�� ����,
								   �ش� key�� value�� appliance* class ���� ���� vector ����
Class Member�Լ� : AddAppliance - ��ǰ�� ����ϱ� ���� ȣ��Ǵ� �Լ�
				   initMenu - �ʱ� �޴� ���
                   add - ��ǰ ����ϴ� �Լ�
				   showAppliance - ��ϵ� ��ǰ ��Ȳ�� ���� ���� ȣ��Ǵ� �Լ�
				   allTrunONAppliance - ��� ������ �� �� ȣ��Ǵ� �Լ�
				    allTrunOFFAppliance - ��� ������ �� �� ȣ��Ǵ� �Լ�
				   ControlAppliance - Ư�� ��ǰ�� ������ �� ȣ��Ǵ� �Լ�
				   controlPower - ������ �����ϴ� �Լ�
				   controlState - ���¸� �����ϴ� �Լ�
				   deleteAppliance - ��ϵ� ��ǰ�� �����ϱ� ���� �Լ�
				   powerCal - ���� ��, �Һ������� ����ϱ� ���� �Լ�
				   addSmsNumber - ��ȣ�� ����ϱ� ���� �Լ�
				   deleteSmsNumber - ��ȣ�� �����ϱ� ���� �Լ�
				   showSmsNumber - ����� ��ȣ�� ���� ���� �Լ�
				   DataSave - ���� ��ϵ� ��ǰ�� �����͸� ���Ͽ� �����ϴ� �Լ�
				   DataLoad - ���� ��ϵ� ��ǰ�� �����͸� �ҷ����� �Լ�
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