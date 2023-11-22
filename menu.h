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
Class name	    : BaseMenu - �޴� class���� �θ� class(�߻� Ŭ����)
Class ��� ���� : programExit : root�޴����� ����ϴ� ��. �ش簪�� 1�� ���, ������ �� �߰� ��� ����
				  std::string title : �޴� �̸� ����

Class Member�Լ�: BaseMenu() - ������, ���ڿ��� ���� ���� ���ڿ� + ���� ���� �� �� ���� ����
				  get_title - �޴� �̸��� ��ȯ�ϴ� �Լ�
				  get_Exit - Exit�� ��ȯ�ϴ� �Լ�
			      ~BaseMenu() - �Ҹ���
				  command - �� �޴��� ��� ����(���� ���� Ŭ������, �Ļ� Ŭ�������� ������)
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
Class name	    : PopupMenu - BaseMenu�� ��ӹ��� class(���� �޴�â ����ϴ� �Լ�)
Class ��� ���� : handler - �޴� ���ý� ȣ��� �Լ�
				  vectr<> v - ���� �޴����� �����ϴ� vector
Class Member�Լ�: add - ���� �޴����� �Է¹޾Ƽ� ��� ���� v�� ���
				  command - handler�� ����� �Լ� ����
----------------------------------------------------------------------------------*/
class PopupMenu : public BaseMenu
{
	std::vector<std::shared_ptr<BaseMenu>> v;
	using HANDLER = std::function<void()>;

	HANDLER handler; // �޴� ���ý� ȣ��� �Լ�
public:
	PopupMenu(const std::string& s) : BaseMenu(s) {}
	PopupMenu(const std::string& s, int A, HANDLER h = nullptr) : BaseMenu(s, A), handler(h) {}
	void add(std::shared_ptr<BaseMenu> p) { v.push_back(p); }
	void command();
};

/*----------------------------------------------------------------------------------
Class name	    : MenuItem - BaseMenu�� ��ӹ��� class
Class ��� ���� : handler - �޴� ���ý� ȣ��� �Լ�

Class Member�Լ�: MenuItem - ������(���ڿ� s�� �Լ��� ���ڷ� �޾Ƽ� BaseMenu �� handler����
				  command - �޴� ���ý� handler�� ��ϵ� �Լ� ȣ��
----------------------------------------------------------------------------------*/
class MenuItem : public BaseMenu
{
	using HANDLER = std::function<void()>;

	HANDLER handler; // �޴� ���ý� ȣ��� �Լ�

public:
	MenuItem(const std::string& s, HANDLER h = nullptr)
		: BaseMenu(s), handler(h) {}

	void command()
	{
		// �޴� ���ý� ��ϵ� �Լ� ȣ��!
		if (handler != nullptr)
			handler();
	}
};

/*----------------------------------------------------------------------------------
Class name	    : Input - ����ڷκ��� data�� �Է¹޴� class(singleton ����)
Calss Member�Լ�: get_instance() - �� �Լ��� ���� ��𼭵� Input class�� ���� ����
				  inputAtoB - A�̻� B������ ���ڸ��� �Է����� �ް� �������� ���û ����
				  inputString - ���ڸ� �Է¹���
				  inputOnly - ���ڸ� �Է����� ����
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