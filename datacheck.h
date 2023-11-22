#pragma once
#include "Appliance.h"


/*----------------------------------------------------------------------------------
Class name	    : checkValue - �Էµ� Data�� ���� ��ȿ���� Ȯ���ϴ� �Լ�
Class Member�Լ�: Addcheck - ����ڰ� �Է��� ��ǰ�� ��ϰ������� üũ�ϴ� �Լ�
                  checkType - ����ڰ� �Է��� Type ��ȿ�� Ȯ��
				  checkName - ����ڰ� �Է��� ��ǰ �̸��� ��ȿ��(���� ����) Ȯ��
				  checkPower - ����ڰ� �Է��� �Һ������� ��ȿ�� Ȯ��
				  checkDataInputArray - ��ȿ�� ����� ������ �ý��ۿ� ����ϴ� �Լ�
				  checkWarningName - �˸��� ���� �� �ִ� ��ǰ���� ��ȿ�� Ȯ��
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
