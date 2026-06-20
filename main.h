#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define MAX_PLAYERS 4
#define NICKNAME_LENGTH 8

extern int p1score[12];
extern int p2score[12];
extern int p3score[12];
extern int p4score[12];
extern char nickname[MAX_PLAYERS][NICKNAME_LENGTH];
extern int dice[5];
extern int score[12];
extern int midTotal[4];
extern int Total[4];

//사용자에게 질문하는 칸에 출력하기 위해 printf쓸 때마다 써야하는 함수 편하게 정의
#define ask gotoxy(1,38); printf("                                                                     "); gotoxy(1,38);

void gotoxy(int x, int y); //gotoxy 함수 선언

void menu();