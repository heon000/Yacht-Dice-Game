//점수 추천 및 선택, 점수계산
#include "score.h"
int t1 = 0, t2 = 0, t3 = 0, t4 = 0;

void expectedscore(int score[]) {//예상점수 출력
    int i = 0;
    while (i < 6) { //1~6 카테고리에 해당하는 좌표
        gotoxy(61, 8 + 2 * i);
        printf("%-8d", score[i]);
        i++;
    }
    while (i < 12) { //7~12 카테고리에 해당하는 좌표
        gotoxy(61, 10 + 2 * i);
        printf("%-8d", score[i]);
        i++;
    }
}

void initscore(int score[]) { //점수 초기화 함수
    for (int i = 0; i < 12; i++) {
        score[i] = 0;
    }
}

void selectscore(int tcount) { //점수를 선택하는 함수
    int category = 0;
    int scoreType = 1;
    extern int x; //x는 메인함수에 있는 함수로 현재 몇 번째 플레이어인지 판단하는 변수
    extern int scount[4][12]; //플레이어 별로 해당 카테고리가 채워졌는지 여부 판단을 위한 배열
    while (1) { //유효한 카테고리 값을 입력할 때까지 반복
        ask;
        printf("원하는 카테고리를 입력하시오(1 ~ 12) : ");
        scanf_s("%d", &category);
        getchar();
        if (scount[x][category - 1] == 1) { //해당 인덱스가 1이라면 해당 카테고리는 채워져있음
            ask;
            printf("이미 입력한 점수입니다 다시 선택해주세요");
            getchar();
        }
        else if (category < 1 || category>12) {
            ask;
            printf("1~12사이의 숫자를 입력해주세요");
            getchar();
        }
        else
            break;
    }
    switch (x + 1) { // 턴 별로 점수가 입력되는 플레이어 결정
        case 1:
            p1score[category - 1] = score[category - 1]; //선택한 카테고리에 해당하는 첫 번째 플레이어의 점수배열에 계산된 점수 저장
            if (category <= 6) { // 선택한 카테고리가 6이하면 midTotal에도 합산
                midTotal[0] += p1score[category - 1];
            }
            Total[0] += p1score[category - 1]; //7이상이면 Total에만 합산
            if (midTotal[0] >= 63 && t1 == 0) { //midTotal이 63점 이상이면 보너스 35점 추가
                Total[0] += 35;
                t1 = 1; //보너스 점수는 한 번만 추가하기 위한 함수
            }
            scount[0][category - 1] = 1; //해당 카테고리는 사용하였다는 의미로 1추가
            break;
        case 2: // 나머지 케이스도 동일 내용
            p2score[category - 1] = score[category - 1];
            if (category <= 6) {
                midTotal[1] += p2score[category - 1];
            }
            Total[1] += p2score[category - 1];
            if (midTotal[1] >= 63 && t2 == 0) {
                Total[1] += 35;
                t2 = 1;
            }
            scount[1][category - 1] = 1;
            break;
        case 3:
            p3score[category - 1] = score[category - 1];
            if (category <= 6) {
                midTotal[2] += p3score[category - 1];
            }
            Total[2] += p3score[category - 1];
            if (midTotal[2] >= 63 && t3 == 0) {
                Total[2] += 35;
                t3 = 1;
            }
            scount[2][category - 1] = 1;
            break;
        case 4:
            p4score[category - 1] = score[category - 1];
            if (category <= 6) {
                midTotal[3] += p4score[category - 1];
            }
            Total[3] += p4score[category - 1];
            if (midTotal[3] >= 63 && t4 == 0) {
                Total[3] += 35;
                t4 = 1;
            }
            scount[3][category - 1] = 1;
            break;
    }
    initscore(score);
}

int* score_cal(int dice[]) {
    int count[6] = { 0 };         // 주사위 눈의 개수를 세기 위한 배열
    int temp[3] = { 0 };
    for (int i = 0; i < 6; i++) { //1~6페어와 초이스 점수 초기화
        score[i] = 0;
    }

    for (int i = 0; i < 5; i++) { // 1~6 페어 (점수 족보 배열의 0번부터 5번까지)
        score[dice[i] - 1] += dice[i];
        score[6] += dice[i];  // 초이스 (점수 족보 배열의 6번)
        count[dice[i] - 1]++;
    }

    for (int i = 0; i < 6; i++) {
        if (count[i] == 2)
            temp[0] = 1; // 풀하우스(주사위 같은 수 2개 확인)
        else if (count[i] == 3)
            temp[1] = 2; // 풀하우스(주사위 같은 수 3개 확인)
        if (count[i] != 0)  //temp2 =>연속된 숫자인지를 확인하는 임시
            temp[2] += 1;
        else if (count[i] == 0) //연속되는 수가 없으면 0으로 초기화
            temp[2] = 0;

        if (count[i] >= 4) { // 포카드 (점수 족보 배열의 7번)
            score[7] = score[6];
        }
        if (temp[2] == 4) { // 스몰 스트레이트 (점수 족보 배열의 9번)
            score[9] = 15;
        }
        if (temp[2] == 5) { // 라지 스트레이트 (점수 족보 배열의 10번)
            score[10] = 30;
        }
        if (temp[0] == 1 && temp[1] == 2) { // 풀하우스 (점수 족보 배열의 8번)
            score[8] = score[6];
        }
        if (count[i] == 5) { // 요트 (점수 족보 배열의 11번)
            score[11] = 50;
        }
    }
    getchar();
    return score;
}