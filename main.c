#include "main.h"
#include "start.h"
#include "scoreboard.h"
#include "rolldice.h"
#include "score.h"
#include "winner.h"

int p1score[12]; //플레이어별 점수배열
int p2score[12];
int p3score[12];
int p4score[12];
char nickname[MAX_PLAYERS][NICKNAME_LENGTH]; //플레이어 이름 배열
int dice[5]; //주사위 배열
int score[12] = { 0 }; //점수 배열
int midTotal[4] = { 0 };
int Total[4] = { 0 };
int x; //현재 차례인 플레이어 확인하는 변수
int scount[4][12]; //이미 입력된 카테고리인지 확인하기 위한 배열

int main(void) { //올바른 메뉴번호 입력 시까지 반복
	while (1) {
		menu(); // 메뉴화면 출력
		int menunum = 0;
		gotoxy(0, 14);
		printf("메뉴 번호를 선택하세요: ");
		scanf("%d", &menunum);
		getchar();

		switch (menunum) {
		case 1:
			PLAYER(); //플레이어 정보 입력받는 함수
			initSB(); //점수판 초기화
			printSB(); //점수판 출력
			break; // 게임 준비
		case 2:
			file_PrintRule();
			break; // 규칙 보여준 뒤 다시 메뉴화면
		case 3:
			exit(0); // 프로그램 종료
		default:
			printf("잘못된 입력입니다 (엔터누르고 다시 입력)");
			getchar();
			break;
		}
		if (menunum == 1) // 게임 시작
			break;
	}
	
	int turn = 1;
	int tcount = 1;
	srand(time(NULL));
	extern int playerCount;

	while (tcount <= playerCount * 12) { //플레이어 별로 12번씩 할 때까지 게임진행
		if (x == 1) { //x가 1인 경우 첫 번째 플레이어 차례로 돌아온 것이므로 턴을 증가
			turn += 1;
		}
		if (tcount % playerCount == 0) { //tcount는 주사위 굴리기를 할 때마다 증가하는데 이를 플레이어 수로 나눈 나머지 값이 0이라면 마지막 플레이어 이므로 x에 마지막 플레이어 저장
			x = playerCount - 1; // 배열에 써야하므로 -1
		}
		else {
			x = tcount % playerCount - 1; // 그 외에는 나머지로 바로 사용
		}
		gotoxy(1, 37);
		printf("%d턴, %s의 차례입니다                  ", turn, nickname[x]); //턴과 누구 차례인지 출력
		int b = 1;

		ask;
		printf("엔터를 누르시면 주사위를 굴립니다.\n");
		getchar();
		roll_dice(dice); // 주사위 굴리기
		selection_sort(dice); // 주사위 정렬
		printDice(dice); // 주사위 모양 출력
		score_cal(dice); // 점수 계산
		expectedscore(score); // 예상점수 출력
		printSB(); //점수판 출력

		while (1) {
			
			char answer = ask_reroll(); // 다시 굴릴 건지 여부 묻는 함수
			if (answer == 'n') {
				break;
			}
			if (answer == 'y' && b < 3) {
				b++;
				initscore(score); // 점수를 다시 계산해야 하므로 점수 초기화
				int reroll = get_reroll_count(); // 다시 굴릴 주사위 개수 입력받기
				int reroll_indice[5] = { 0 };
				get_reroll_indices(reroll_indice, reroll); // 몇 번째 주사위를 굴릴건지 여부 묻기
				for (int i = 0; i < 5; i++) {
					if (reroll_indice[i]) {
						dice[i] = rand() % 6 + 1;
					}
				}
				printDice(dice); // 주사위 모양 출력
				selection_sort(dice); // 주사위 정렬
				Sleep(1000); // 주사위가 정렬되는 것을 육안으로 확인하기 위해 약간의 딜레이
				printDice(dice); // 정렬된 주사위 출력
				score_cal(dice); // 점수 계산
				expectedscore(score); // 예상점수 출력
			}
			if (b >= 3) { // 주사위를 총 3번 굴렸다면 굴리기는 끝
				break;
			}
		}
		selectscore(tcount); //점수 선택
		printSB();
		tcount += 1;
		initdice(); // 주사위 초기화
		printDice(dice); // 주사위 칸에 빈칸 출력
		ask;
		printf("턴을 종료합니다.\n");
	}
	Winner(Total); //승자 확인 함수
	getchar();
	return 0;
}