#pragma warning(disable:6031)
#include "menu.h"

/*----------------------------------------------------------------------------------
Class Member�Լ�: command - handler�� ����� �Լ� ����
----------------------------------------------------------------------------------*/
void PopupMenu::command()
{
	while (1)
	{
		system("cls");

		int sz = (int)v.size();
		//PopupMenu ��� ���� v�� ��ϵ� ���� �޴����� title�� �� ���
		for (int i = 0; i < sz; i++)
		{
			std::cout << i + 1 << ". " << v[i]->get_title() << std::endl;
		}
		std::cout << sz + 1 << ". ����\n";

		int cmd;
		std::cout << "�޴��� �����ϼ��� >> ";

		//����ڷκ��� �޴� ���ڸ� �Է¹���
		//�Է°��� �޴� �������� ũ�ų� ���ڰ� �ƴ� ��� �ٽ� �Է¹޵��� ��
		if (!(std::cin >> cmd)) {
			std::cin.clear();
			while (std::cin.get() == '\n') continue;
			printf("�޴��� �ٽ� �Է����ּ���(Enter..)\n");
			getch();
			continue;
		}

		//PopupMenu���� get_exit() == 1�̸� �߰� handler ����
		//���⼭ get_Exit()�� �ֻ��� �޴��� ��ϵǾ� ����
		//�ش� ���� �ԷµǾ��� ���� ���� �޴� ���� �Է��� �ֻ������� �߱� ������
		//�ý����� �����ϴ� ���
		//����, �ý����� ������ �ÿ�, ��� ��ǰ�� ������ OFF�ϰ� ������� �����
		//���·��� ����ϴ� �Լ� ȣ�� �� ����
		if (cmd == sz + 1 && get_Exit() == 1) {
			handler();
			_getch();
			break;
		}
		else if (cmd == sz + 1) //�� ���� �����ư�� �����޴��� ���ư�
			break;
		//�޴��� �´� command�� ����
		if (1 <= cmd && cmd < sz + 1) {
			v[cmd - 1]->command();
		}
		else {
			printf("�޴��� �ٽ� �Է����ּ���(Enter..)\n");
			getch();
			continue;
		}
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
}

/*----------------------------------------------------------------------------------
Calss Member�Լ�: inputAtoB - A�̻� B������ ���ڸ��� �Է����� �ް� �������� ���û ����
----------------------------------------------------------------------------------*/
void Input::inputAtoB(int& Temp, int begin, int end) {
	while (1) {
		std::cin >> Temp;
		if (getchar() != '\n' || !(begin <= Temp && Temp <= end)) {
			std::cout << "�ٽ� �Է����ּ���" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
	this->Temp = Temp;
}

/*----------------------------------------------------------------------------------
Calss Member�Լ�: inputString - ���ڸ� �Է¹���
----------------------------------------------------------------------------------*/
void Input:: inputString(std::string& Name) {
	std::cin >> Name;
	this->Name = Name;
}

/*----------------------------------------------------------------------------------
Calss Member�Լ�: inputOnly - ���ڸ� �Է����� ����
----------------------------------------------------------------------------------*/
void Input::inputOnly(int& Temp) {
	while (1) {
		std::cin >> Temp;
		if (getchar() != '\n') {
			std::cout << "�ٽ� �Է����ּ���" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
}