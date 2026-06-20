#include "winner.h"

// 배열로 플레이어 점수 전달받음
void Winner(int Total[]) {
    int maxScore = 0;
    int winner[4] = { 0 }; 
    extern int playerCount;

    for (int i = 0; i < playerCount; i++) { // 플레이어 수만큼 반복
        if (Total[i] > maxScore) { //각 플레이어 별 Total점수를 비교 후 최대값 저장
            maxScore = Total[i];
        }
    }
    for (int i = 0; i < playerCount; i++) {
        if (maxScore == Total[i]) {
            winner[i] = 1; //동점인 경우를 대비하여 같은 점수를 가진 사람을 저장
        }
    }
    gotoxy(1, 37);
    printf("                                                                     ");
    gotoxy(1, 37);
    printf("우승자는 : "); //winner배열의 값이 1인 플레이어 출력
    for (int i = 0; i < playerCount; i++) {
        if (winner[i] == 1) {
            printf("%s", nickname[i]);
        }
    }
}