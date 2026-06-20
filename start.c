#include "start.h"
int playerCount;

//규칙 내용
char content1[] = "요트다이스\n인원 : 2~4인\n플레이 시간 : 10~30분\n\n규칙\n1. 주사위 5개를 굴린다.\n\
2. 주사위는 원하는 주사위를 선택하여 다시 굴릴 수 있으며, 최대 3번까지 굴릴 수 있다.\n3. 주사위를 굴린 후 나온 조합을 아직 기록되지 않은 카테고리를 선택하여 점수판에 기록한다.\n\
(만족하는 카테고리가 없거나 점수가 맘에 들지 않는다면 0점으로 기록 가능)\n4. 모든 플레이어가 모든 카테고리를 선택하여 점수판을 다 채우면 게임이 종료된다.\n\
(이 때 가장 높은 점수를 만든 플레이어가 승리한다.)\n5. 카테고리는 12개로 한 턴에 하나만 채울 수 있으며 총 12턴으로 진행된다.\n\
6. 카테고리에서 위 6개를 상단이라고 하며, 상단의 점수가 63 이상이면 보너스 35점을 받는다.\n";
//점수 족보 내용
char content2[] = \
"Ones: 1이 나온 주사위의 합\nTwos: 2가 나온 주사위의 합\nThrees: 3이 나온 주사위의 합\nFours : 4가 나온 주사위의 합\nFives: 5가 나온 주사위의 합\nSixes: 6이 나온 주사위의 합\n\
Choice: 주사위의 총합\nFour of a Kind: 동일한 주사위가 4개 이상일 때, 주사위의 합\nFull House: 주사위 묶음을 2,3개 또는 3,2개로 하였을 때 각 묶음에서 주사위 눈이 같을 때 주사위의 합\n\
Small Straight: 이어지는 주사위가 4개 이상일 때 15점\nLarge Straight: 이어지는 주사위가 5개일 때 30점\nYacht: 주사위 눈이 전부 동일할 때 50점\n";

int nicknamelen(const char* nickname) { //닉네임 길이의 제한을 두기 위한 사용자 정의 함수
    int len = strlen(nickname);
    int english = 0; // 영어길이
    int korean = 0; // 한글길이

    for (int i = 0; i < len; i++) {
        if ((nickname[i] >= 0x00 && nickname[i] <= 0x7F)) { //아스키코드를 사용하여 영문과 한글 구분
            english++; //영어 길이 카운트 증가
        }
        else {
            korean++; //한글 길이 카운트 증가
        }
    }
    return (english <= 8 && korean <= 8);
}

void PLAYER() {
    int i;

    while (1) { //2~4 입력받을 때까지 반복
        printf("플레이어 수를 입력하세요 (2 ~ 4명): ");
        scanf("%d", &playerCount);
        getchar();
        if (!(2 <= playerCount && playerCount <= 4)) {
            printf("최소 2명, 최대 4명까지 가능합니다. 다시 입력해주세요.\n");
        }
        else {
            break;
        }
    }

    for (i = 0; i < playerCount; i++) { //영문 8자, 한글 4자가 이내가 아니면 반복
        while (1) {
            printf("플레이어 %d의 닉네임을 입력하세요(최대 영문 8자, 한글 4자): ", i + 1);
            scanf("%s", nickname[i]);
            getchar();
            if (nicknamelen(nickname[i])) { //닉네임 길이 사용자 정의함수를 불러옴
                break;
            }
            else {
                printf("영문 8자 또는 한글 4자 이내로 입력해주세요.\n");
            }
        }
    }

    for (i = playerCount; i < MAX_PLAYERS; i++) { //4인 미만일 경우 빈 닉네임은 '-'로 채움
        strcpy(nickname[i], "-");
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        printf("플레이어 %d의 닉네임: %s\n", i + 1, nickname[i]);
    }
}

void file_PrintRule()
{
    RuleFile("rule1.txt", content1); //파일 읽기
    RuleFile("rule2.txt", content2);

    int choice;

    while (1) //유효한 값과 3을 입력받을 때까지 무한반복
    {
        printf("──────────────────────────────────────────────────────────\n");
        printf("1. 규칙 출력\n");
        printf("2. 점수 족보 출력\n");
        printf("3. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) //switch case를 사용하여 입력받은 숫자를 토대로 각 기능 실행
        {
        case 1:
            FileContent("rule1.txt"); //파일 내용 출력함수
            break;
        case 2:
            FileContent("rule2.txt");
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 선택입니다. 다시 선택하세요.\n");
            break;
        }
    }
}

int RuleFile(char* filename, char* content[]) // 파일 읽기 또는 (없다면) 생성 함수
{
    FILE* file = fopen(filename, "r"); // 파일 읽기
    if (file == NULL) // 파일이 없으면 생성
    {
        file = fopen(filename, "w"); //파일 생성
        if (file == NULL)
        {
            printf("파일 생성 실패\n");
            return 1;
        }
        fprintf(file, "%s\n", content); //파일 내용 쓰기
        printf("%s 파일을 생성했습니다.\n", filename);
        fclose(file);
    }
    else // 파일이 이미 있으면 종료
    {
        fclose(file);
    }
    return 0;
}

int FileContent(char* filename) // 파일 내용 출력 함수
{
    FILE* file = fopen(filename, "r"); //파일 읽기
    if (file == NULL)
    {
        printf("파일을 열기 실패\n");
        return 1;
    }
    system("cls"); //화면 지우기
    char buffer[100]; //버퍼설정
    while (fgets(buffer, sizeof(buffer), file) != NULL) //파일에 내용 복사
    {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(file);
    return 0;
}