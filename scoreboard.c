#include "scoreboard.h"

void initSB() { // 점수와 점수판 초기화
    system("cls");
    for (int i = 0; i < 12; i++) {
        p1score[i] = 0;
        p2score[i] = 0;
        p3score[i] = 0;
        p4score[i] = 0;
    }
	for (int i = 0; i < 5; i++) {
		score[i] = 0;
	}
}


void printSB() { //점수판
    const char* category[] = { "Ones","Twos","Threes","Fours","Fives","Sixes","Choice", "Four of a Kind","Full House","Small Straight","Large Straight","Yacht", }; //각 카테고리 이름 저장
    gotoxy(0, 5); // 위치에 맞춰 점수판 출력
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓┏━━━━━━━━━┓\n");
    printf("┃%-17s ┃%-8s ┃%-8s ┃%-8s ┃%-8s ┃┃%-8s ┃\n", "category", nickname[0], nickname[1], nickname[2], nickname[3], "예상점수");
    for (int a = 0; a < 6; a++) {
        printf("┠──────────────────╂─────────╂─────────╂─────────╂─────────┨┠─────────┨\n");
        printf("┃%2d.%-14s ┃%-8d ┃%-8d ┃%-8d ┃%-8d ┃┃%-8d ┃\n", a + 1, category[a], p1score[a], p2score[a], p3score[a], p4score[a], score[a]);
    }
    printf("┠──────────────────╂─────────╂─────────╂─────────╂─────────┨┠─────────┨\n");
    printf("┃%-17s ┃%-8d ┃%-8d ┃%-8d ┃%-8d ┃┃%-8s ┃\n", "midTotal(+35)", midTotal[0], midTotal[1], midTotal[2], midTotal[3], "-");
    for (int a = 6; a < 12; a++) {
        printf("┠──────────────────╂─────────╂─────────╂─────────╂─────────┨┠─────────┨\n");
        printf("┃%2d.%-14s ┃%-8d ┃%-8d ┃%-8d ┃%-8d ┃┃%-8d ┃\n", a + 1, category[a], p1score[a], p2score[a], p3score[a], p4score[a], score[a]);
    }
    printf("┠──────────────────╂─────────╂─────────╂─────────╂─────────┨┠─────────┨\n");
    printf("┃%-17s ┃%-8d ┃%-8d ┃%-8d ┃%-8d ┃┃%-8s ┃\n", "Total", Total[0], Total[1], Total[2], Total[3], "-");
    printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛┗━━━━━━━━━┛\n");
	// 플레이어 입력을 입력받는 공간 출력
    gotoxy(0, 36);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            gotoxy(70 * j, 37 + i);
            printf("┃");
        }
    }
    printf("\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

// 주사위들의 모양 정하기
char dicepattern1[5][30] = {
	{"┏━━━━━━━┓"},
	{"┃       ┃"},
	{"┃   ●   ┃"},
	{"┃       ┃"},
	{"┗━━━━━━━┛"}
};
char dicepattern2[5][30] = {
	{"┏━━━━━━━┓"},
	{"┃●      ┃"},
	{"┃       ┃"},
	{"┃      ●┃"},
	{"┗━━━━━━━┛"}
};
char dicepattern3[5][30] = {
	{"┏━━━━━━━┓"},
	{"┃●      ┃"},
	{"┃   ●   ┃"},
	{"┃      ●┃"},
	{"┗━━━━━━━┛"}
};
char dicepattern4[5][30] = {
	{"┏━━━━━━━┓"},
	{"┃●     ●┃"},
	{"┃       ┃"},
	{"┃●     ●┃"},
	{"┗━━━━━━━┛"}
};
char dicepattern5[5][30] = {
	{"┏━━━━━━━┓"},
	{"┃●     ●┃"},
	{"┃   ●   ┃"},
	{"┃●     ●┃"},
	{"┗━━━━━━━┛"}
};
char dicepattern6[5][30] = {
	{"┏━━━━━━━┓"},
	{"┃●     ●┃"},
	{"┃●     ●┃"},
	{"┃●     ●┃"},
	{"┗━━━━━━━┛"}
};





void printDice(int dice[5]) { // 주사위 출력 함수
	for (int i = 0; i < 5; i++) {
		int j;
		switch (dice[i]) { //주사위 값에 따라 위에서 설정한 해당 주사위 출력을 위한 switch case 함수
		case 1:
			for (j = 0; j < 5; j++) {
				gotoxy(i * 11 + 2, j); //해당 x좌표 위치에 줄바꿈 해가면서 출력
				printf("%s", dicepattern1[j]);
			}
			break;
		case 2:
			for (j = 0; j < 5; j++) {
				gotoxy(i * 11 + 2, j);
				printf("%s", dicepattern2[j]);
			}
			break;
		case 3:
			for (j = 0; j < 5; j++) {
				gotoxy(i * 11 + 2, j);
				printf("%s", dicepattern3[j]);
			}
			break;
		case 4:
			for (j = 0; j < 5; j++) {
				gotoxy(i * 11 + 2, j);
				printf("%s", dicepattern4[j]);
			}
			break;
		case 5:
			for (j = 0; j < 5; j++) {
				gotoxy(i * 11 + 2, j);
				printf("%s", dicepattern5[j]);
			}
			break;
		case 6:
			for (j = 0; j < 5; j++) {
				gotoxy(i * 11 + 2, j);
				printf("%s", dicepattern6[j]);
			}
			break;
		default : // 주사위 굴리기가 끝나거나 했을 경우 빈 공간 출력
			gotoxy(0, 0);
			for (int a = 0; a < 5; a++) {
				printf("                                                                       \n");
			}
		}
	}
}