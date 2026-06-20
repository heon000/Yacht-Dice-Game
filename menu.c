#include "main.h"

void menu() { //메뉴화면 출력
	system("cls");
	gotoxy(0, 0);
	printf("● ●   ●    ●●  ● ●  ●●●     ●●   ●●●   ●●  ●●●\n");
	printf("● ●  ● ●  ●    ● ●   ●      ● ●   ●   ●    ●  \n");
	printf(" ●   ●●●  ●    ●●●   ●      ● ●   ●   ●    ●●●\n");
	printf(" ●   ● ●  ●    ● ●   ●      ● ●   ●   ●    ●  \n");
	printf(" ●   ● ●   ●●  ● ●   ●      ●●   ●●●   ●●  ●●●\n");
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                                                  ┃\n");
	printf("┃                                                                  ┃\n");
	printf("┃                                                                  ┃\n");
	printf("┃                                                                  ┃\n");
	printf("┃                                                                  ┃\n");
	printf("┃                                                                  ┃\n");
	printf("┃                                                                  ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	gotoxy(10, 9); printf("1.게임시작");
	gotoxy(29, 9); printf("2.게임규칙");
	gotoxy(48, 9); printf("3.게임종료");
}

void gotoxy(int x, int y) { //gotoxy함수
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}