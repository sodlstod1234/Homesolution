#ifndef APPLIANCE_H__
#define APPLAINCE_H__
#pragma warning(disable :6031)
#include "menu.h"
#include "SMSManager.h"

/*----------------------------------------------------------------------------------
Class name	    : Appliance - 제품들의 정보를 갖는 추상 class
Class 멤버 변수 : 등록되는 제품들의 세부 정보들을 저장
Class Member함수 : Appliance.cpp에서 설명
----------------------------------------------------------------------------------*/
class Appliance
{
private:
	std::string machineName;
	time_t currentTime=0;
	int _type;
	bool powerFlag;
	std::string powerFlagName[2] = { "OFF", "ON" };
	int powerConsumption;
	std::string state1;
	int state2;
	time_t startHour;
	time_t useHour;
	using HANDLER = std::function<void()>;
	HANDLER handler;

public:
	Appliance(int _type, const std::string& s, int p);
	std::string get_title() { return machineName; }
	int get_type() { return _type; }
	void set_type(int _type) {this->_type = _type;}

	bool get_powerFlag() { return powerFlag; }
	void set_powerFlag(bool powerFlag);

	int get_powerConsumption() { return powerConsumption; }
	void set_powerConsumption(int powerConsumption) {this->powerConsumption = powerConsumption;}

	std::string get_state1() { return state1; }
	void set_state1(std::string state1);
	int get_state2() { return state2; }
	void set_state2(int state2) {this->state2 = state2;}

	int get_useHour() { return useHour; }
	void set_useHour(int useHour) {this->useHour = useHour;}
	virtual ~Appliance() {}
	virtual void command() = 0;
	virtual void showadd() {std::cout << std::endl;}
	void show();

	void warningSend() {
		SMSManager& sms = SMSManager::get_instance();
		sms.send_sms(this->get_title(), "의 전원이 켜졌습니다.");
	}
};

/*----------------------------------------------------------------------------------
Class name	    : ApplianceFactory - 제품들을 미리 등록해두기 위한 공장 class
Class 멤버 변수 : 할당할 제품을 등록할 수 있는 map
Class Member함수 : register_Appliance - 공장에 접근하기 위해 외부에서 사용될 함수
				   create - main()실행 전에 호출되어 등록할 제품 생성하기 위한 함수
----------------------------------------------------------------------------------*/
class ApplianceFactory
{
	using CREATOR = std::shared_ptr<Appliance>(*)(int type, std::string Name, int powerConsumption);
	std::map<int, CREATOR> m;
public:
	void register_Appliance(int type, CREATOR f) {m[type] = f;}
	std::shared_ptr<Appliance> create(int type, std::string machineName, int powerConsumption);
	static ApplianceFactory& get_instance();
};

/*----------------------------------------------------------------------------------
Class name	    : AutoRegister

 생성자에서 공장의 참조를 얻어서 제품을 등록하기 위해 사용하는 class
----------------------------------------------------------------------------------*/
class AutoRegister
{
public:
	AutoRegister(int type, std::shared_ptr<Appliance>(*f)(int type, std::string Name, int powerConsumption));
};

/*----------------------------------------------------------------------------------
Class name	    : Airconditoner - 에어컨을 등록할 때 사용하는 class(부모class : appliance)
----------------------------------------------------------------------------------*/
class Airconditoner : public Appliance
{
public:
	Airconditoner(int _type, const std::string machinName, int powerConsumption) :
		Appliance(_type, machinName, powerConsumption) {}

	virtual void showadd() {std::cout << ", 제품 온도: " << get_state2() << std::endl;}
	void command();
	void command_state1();
	void command_state2();
	static std::shared_ptr<Appliance> create(int type, std::string machineName, int powerConsumption);
	static AutoRegister ar;

};

/*----------------------------------------------------------------------------------
Class name	    : RiceCooker - RiceCooker 등록할 때 사용하는 class(부모class : appliance)
----------------------------------------------------------------------------------*/
class RiceCooker : public Appliance
{
public:
	RiceCooker(int _type, const std::string machinName, int powerConsumption) :
		Appliance(_type, machinName, powerConsumption) {}

	static std::shared_ptr<Appliance> create(int type, std::string machineName, int powerConsumption);
	static AutoRegister ar;
	void command();
};

/*----------------------------------------------------------------------------------
Class name	    : Washer - Washer 등록할 때 사용하는 class(부모class : appliance)
----------------------------------------------------------------------------------*/
class Washer : public Appliance
{
public:
	Washer(int _type, const std::string machinName, int powerConsumption) :
		Appliance(_type, machinName, powerConsumption) {}

	static std::shared_ptr<Appliance> create(int type, std::string machineName, int powerConsumption);
	static AutoRegister ar;
	void command();
};

/*----------------------------------------------------------------------------------
Class name	    : Light - Light 등록할 때 사용하는 class(부모class : appliance)
----------------------------------------------------------------------------------*/
class Light : public Appliance
{
public:
	Light(int _type, const std::string machinName, int powerConsumption) :
		Appliance(_type, machinName, powerConsumption) {}

	static std::shared_ptr<Appliance> create(int type, std::string machineName, int powerConsumption);
	static AutoRegister ar;

	void command() {}
};


#endif