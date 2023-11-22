#ifndef MENU_H__
#define MENU_H__

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:4244)
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <map>
#include <algorithm>
#include <functional>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <memory>

/*----------------------------------------------------------------------------------
Class name	    : BaseMenu - 메뉴 class들의 부모 class(추상 클래스)
Class 멤버 변수 : programExit : root메뉴에서 등록하는 값. 해당값이 1일 경우, 종료할 때 추가 기능 수행
				  std::string title : 메뉴 이름 저장

Class Member함수: BaseMenu() - 생성자, 문자열만 받을 때와 문자열 + 문자 받을 때 두 가지 존재
				  get_title - 메뉴 이름을 반환하는 함수
				  get_Exit - Exit값 반환하는 함수
			      ~BaseMenu() - 소멸자
				  command - 각 메뉴의 기능 수행(순수 가상 클래스로, 파생 클래스에서 구현됨)
----------------------------------------------------------------------------------*/
class BaseMenu
{
	int programExit = 0;
	std::string title;


public:
	BaseMenu(const std::string& s) : title(s) {}
	BaseMenu(const std::string& s, int A) : title(s), programExit(A) {}
	std::string get_title() { return title; }
	int get_Exit() { return programExit; }
	virtual ~BaseMenu() {}
	virtual void command() = 0;
};

/*----------------------------------------------------------------------------------
Class name	    : PopupMenu - BaseMenu를 상속받은 class(하위 메뉴창 출력하는 함수)
Class 멤버 변수 : handler - 메뉴 선택시 호출될 함수
				  vectr<> v - 하위 메뉴들을 보관하는 vector
Class Member함수: add - 하위 메뉴들을 입력받아서 멘버 변수 v에 등록
				  command - handler에 저장된 함수 수행
----------------------------------------------------------------------------------*/
class PopupMenu : public BaseMenu
{
	std::vector<std::shared_ptr<BaseMenu>> v;
	using HANDLER = std::function<void()>;

	HANDLER handler; // 메뉴 선택시 호출될 함수
public:
	PopupMenu(const std::string& s) : BaseMenu(s) {}
	PopupMenu(const std::string& s, int A, HANDLER h = nullptr) : BaseMenu(s, A), handler(h) {}
	void add(std::shared_ptr<BaseMenu> p) { v.push_back(p); }
	void command();
};

/*----------------------------------------------------------------------------------
Class name	    : MenuItem - BaseMenu를 상속받은 class
Class 멤버 변수 : handler - 메뉴 선택시 호출될 함수

Class Member함수: MenuItem - 생성자(문자열 s와 함수를 인자로 받아서 BaseMenu 및 handler저장
				  command - 메뉴 선택시 handler에 등록된 함수 호출
----------------------------------------------------------------------------------*/
class MenuItem : public BaseMenu
{
	using HANDLER = std::function<void()>;

	HANDLER handler; // 메뉴 선택시 호출될 함수

public:
	MenuItem(const std::string& s, HANDLER h = nullptr)
		: BaseMenu(s), handler(h) {}

	void command()
	{
		// 메뉴 선택시 등록된 함수 호출!
		if (handler != nullptr)
			handler();
	}
};

/*----------------------------------------------------------------------------------
Class name	    : Input - 사용자로부터 data를 입력받는 class(singleton 패턴)
Calss Member함수: get_instance() - 이 함수를 통해 어디서든 Input class에 접근 가능
				  inputAtoB - A이상 B이하의 숫자만을 입력으로 받고 나머지는 재요청 진행
				  inputString - 문자를 입력받음
				  inputOnly - 숫자만 입력으로 받음
----------------------------------------------------------------------------------*/
class Input {
	int Temp;
	std::string Name;
	int begin;
	int end;
public:
	static Input& get_instance() {
		static Input input;
		return input;
	}

	void inputAtoB(int& Temp, int begin, int end);
	void inputString(std::string& Name);
	void inputOnly(int& Temp);
};

#endif