#pragma warning(disable:6031)
#include "menu.h"

/*----------------------------------------------------------------------------------
Class Member함수: command - handler에 저장된 함수 수행
----------------------------------------------------------------------------------*/
void PopupMenu::command()
{
	while (1)
	{
		system("cls");

		int sz = (int)v.size();
		//PopupMenu 멤버 변수 v에 등록된 하위 메뉴들의 title을 얻어서 출력
		for (int i = 0; i < sz; i++)
		{
			std::cout << i + 1 << ". " << v[i]->get_title() << std::endl;
		}
		std::cout << sz + 1 << ". 종료\n";

		int cmd;
		std::cout << "메뉴를 선택하세요 >> ";

		//사용자로부터 메뉴 숫자를 입력받음
		//입력값이 메뉴 개수보다 크거나 숫자가 아닐 경우 다시 입력받도록 함
		if (!(std::cin >> cmd)) {
			std::cin.clear();
			while (std::cin.get() == '\n') continue;
			printf("메뉴를 다시 입력해주세요(Enter..)\n");
			getch();
			continue;
		}

		//PopupMenu에서 get_exit() == 1이면 추가 handler 실행
		//여기서 get_Exit()은 최상위 메뉴에 등록되어 있음
		//해당 값이 입력되었을 때는 종료 메뉴 숫자 입력을 최상위에서 했기 때문에
		//시스템을 종료하는 명령
		//따라서, 시스템을 종료할 시에, 모든 제품의 전원을 OFF하고 현재까지 사용한
		//전력량을 계산하는 함수 호출 후 종료
		if (cmd == sz + 1 && get_Exit() == 1) {
			handler();
			_getch();
			break;
		}
		else if (cmd == sz + 1) //그 외의 종료버튼은 상위메뉴로 돌아감
			break;
		//메뉴에 맞는 command를 실행
		if (1 <= cmd && cmd < sz + 1) {
			v[cmd - 1]->command();
		}
		else {
			printf("메뉴를 다시 입력해주세요(Enter..)\n");
			getch();
			continue;
		}
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
}

/*----------------------------------------------------------------------------------
Calss Member함수: inputAtoB - A이상 B이하의 숫자만을 입력으로 받고 나머지는 재요청 진행
----------------------------------------------------------------------------------*/
void Input::inputAtoB(int& Temp, int begin, int end) {
	while (1) {
		std::cin >> Temp;
		if (getchar() != '\n' || !(begin <= Temp && Temp <= end)) {
			std::cout << "다시 입력해주세요" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
	this->Temp = Temp;
}

/*----------------------------------------------------------------------------------
Calss Member함수: inputString - 문자를 입력받음
----------------------------------------------------------------------------------*/
void Input:: inputString(std::string& Name) {
	std::cin >> Name;
	this->Name = Name;
}

/*----------------------------------------------------------------------------------
Calss Member함수: inputOnly - 숫자만 입력으로 받음
----------------------------------------------------------------------------------*/
void Input::inputOnly(int& Temp) {
	while (1) {
		std::cin >> Temp;
		if (getchar() != '\n') {
			std::cout << "다시 입력해주세요" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
}