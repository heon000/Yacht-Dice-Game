#include "rolldice.h"

void roll_dice(int dice[]) { //주사위를 5번 굴리기
    for (int i = 0; i < 5; i++) {
        dice[i] = rand() % 6 + 1; //1~6사이의 난수 생성
    }
}

char ask_reroll() { // 주사위를 다시 굴릴지 여부 묻는 함수
    char answer;
    while (1) {
        ask;
        printf("주사위를 더 굴리시겠습니까? (y/n): "); // 유효한 입력을 할 때까지 반복
        if (scanf(" %c", &answer) == 1 && (answer == 'y' || answer == 'n')) {
            break;
        }
        ask;
        printf("잘못된 입력입니다. 'y' 또는 'n'을 입력하세요.\n");
        while (getchar() != '\n'); // 잘못된 입력 버퍼 비우기
    }
    return answer;
}

int get_reroll_count() { // 몇 개의 주사위를 굴릴 건지 묻는 함수
    int reroll;
    while (1) { // 유효한 입력을 할 때까지 반복
        ask;
        printf("몇 개의 주사위를 다시 굴리시겠습니까? (1-5): ");
        if (scanf("%d", &reroll) == 1 && reroll >= 1 && reroll <= 5) {
            break;
        }
        ask;
        printf("잘못된 입력입니다. 1에서 5 사이의 숫자를 입력하세요.\n");
        while (getchar() != '\n'); // 잘못된 입력 버퍼 비우기
    }
    return reroll;
}

void get_reroll_indices(int reroll_indice[], int reroll) { //굴릴 주사위의 번호를 입려받는 함수
    while (1) {
        ask;
        printf("다시 굴릴 주사위의 번호를 선택하세요 (1-5, 공백으로 구분): ");
        int dices_entered = 0;
        int invalid_input = 0;
        for (int i = 0; i < reroll; i++) { //위에서 입력받은 다시 굴릴 주사위 개수만큼 반복
            int index;
            if (scanf_s("%d", &index) != 1 || index < 1 || index > 5 || reroll_indice[index - 1]) { //유효성 검사
                if (index < 1 || index > 5) { //1에서 5사이인지 확인
                    ask;
                    printf("잘못된 번호입니다. 1에서 5 사이의 숫자를 입력하세요.\n");
                }
                else if (reroll_indice[index - 1]) { //중복된 번호인지 확인
                    ask;
                    printf("이미 선택된 번호입니다. 다른 번호를 선택하세요.\n");
                }
                invalid_input = 1; //유효하지 않은 입력으로 플래그 설정
                while (getchar() != '\n'); // 잘못된 입력 버퍼 비우기
                break;
            }
            reroll_indice[index - 1] = 1; //유효한 입력일 경우 인덱스 설정
            dices_entered++; //바꾼 주사위 수 증가
        }
        if (!invalid_input && dices_entered == reroll) { //유효한 입력이 모두 완료되었는지 확인
            break;
        }
        else {
            ask;
            printf("잘못된 입력입니다. %d개의 유효한 번호를 입력하세요.\n", reroll);
            while (getchar() != '\n');
            for (int i = 0; i < 5; i++) {
                reroll_indice[i] = 0; // 재입력을 위해 배열 초기화
            }
        }
    }
}

void initdice() { //중복계산을 피하기 위한 주사위 배열을 초기화 하는 함수
    for (int i = 0; i < 5; i++) {
        dice[i] = 0;
    }
}

void selection_sort(int dice[]) { //선택정렬함수
    int n = 5; //주사위 개수
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i; //현재 인덱스를 최소값 인덱스로 설정
        for (j = i + 1; j < n; j++)
        {
            if (dice[j] < dice[min]) //현재값 보다 작은 값을 찾으면 최소값 인덱스 교환
                min = j;
        }
        temp = dice[min];
        dice[min] = dice[i];
        dice[i] = temp;
    }
}