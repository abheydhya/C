#include <stdio.h>
#include <conio.h>
#include <string.h>

char a[6];
char b[6];

void setupConsole()
{
    window(1, 1, 25, 80);
    textbackground(LIGHTBLUE);
    textcolor(YELLOW);
    clrscr();
}

void drawFrame()
{
    int i;
    gotoxy(2, 2);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    for (i = 3; i <= 23; i++) {
        gotoxy(2, i);
        printf("┃");
        gotoxy(76, i);
        printf("┃");
    }
    gotoxy(2, 24);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void displayHelp()
{
    setupConsole();
    drawFrame();
    gotoxy(25, 4);
    printf("^_^欢迎使用商人过河游戏！^_^");
    gotoxy(4, 6);
    printf("游戏说明：");
    gotoxy(5, 7);
    printf("三个商人带着三个随从和货物过河，船每次最多只能载两个人，");
    gotoxy(5, 8);
    printf("要求在过河期间，任一岸上商人的人数要大于或等于随从的人数，");
    gotoxy(5, 9);
    printf("否则随从会杀掉商人抢走货物。");
    gotoxy(5, 11);
    printf("游戏操作：（1）依次输入过河的商人和随从人数；");
    gotoxy(5, 12);
    printf("          （2）非法输入按键将重新开始。");
    gotoxy(2, 13);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
}

void printCase(char sideA[], char sideB[])
{
    int i, xa = 0, xb = 0, ya = 0, yb = 0;
    gotoxy(11, 14);
    printf("此岸                彼岸\n");

    for (i = 0; i < 6; i++) {
        if (sideA[i] == 'A') xa++;
        else if (sideA[i] == 'B') xb++;
    }
    gotoxy(11, 15);
    for (i = 1; i <= xa; i++) printf("商人  ");
    gotoxy(11, 16);
    for (i = 1; i <= xb; i++) printf("随从  ");

    for (i = 0; i < 6; i++) {
        if (sideB[i] == 'A') ya++;
        else if (sideB[i] == 'B') yb++;
    }
    gotoxy(31, 15);
    for (i = 1; i <= ya; i++) printf("商人 ");
    gotoxy(31, 16);
    for (i = 1; i <= yb; i++) printf("随从 ");
}

int validateInput(int countA, int countB, int x, int y)
{
    return !(x < 0 || x > countA || y < 0 || y > countB || x + y < 1 || x + y > 2);
}

void updateCharacters(char source[], char destination[], int x, char type)
{
    int i, j;
    for (i = 1; i <= x; i++) {
        for (j = 0; j < 6; j++) {
            if (source[j] == type) {
                source[j] = '0';
                break;
            }
        }
        for (j = 0; j < 6; j++) {
            if (destination[j] == '0') {
                destination[j] = type;
                break;
            }
        }
    }
}

int isValidGameState(char sideA[], char sideB[])
{
    int aA = 0, aB = 0, bA = 0, bB = 0, i;
    for (i = 0; i < 6; i++) {
        if (sideA[i] == 'A') aA++;
        else if (sideA[i] == 'B') aB++;
        if (sideB[i] == 'A') bA++;
        else if (sideB[i] == 'B') bB++;
    }
    return (aA == 3 || bA == 3 || aA == aB || bA == bB);
}

void startGame()
{
    int x, y, i;
    char ch;
Start:
    displayHelp();
    gotoxy(15, 16);
    printf("请按任意键开始游戏（按Q键退出）...");
    ch = getch();
    if (ch == 'Q' || ch == 'q') {
        setupConsole();
        textbackground(BLACK);
        textcolor(LIGHTGRAY);
        clrscr();
        exit(0);
    }

    for (i = 0; i < 3; i++) a[i] = 'A';
    for (i = 3; i < 6; i++) a[i] = 'B';
    memset(b, '0', sizeof(b));
    printCase(a, b);

    while (1) {
        int countA = 0, countB = 0;
        for (i = 0; i < 6; i++) {
            if (a[i] == 'A') countA++;
            else if (a[i] == 'B') countB++;
        }

        gotoxy(20, 18);
        printf("输入去彼岸商人的人数： ");
        scanf("%d", &x);
        gotoxy(20, 18);
        printf("输入去彼岸随从的人数： ");
        scanf("%d", &y);

        if (!validateInput(countA, countB, x, y)) {
            gotoxy(15, 21);
            printf("输入有误！！按任意键重新开始...");
            getch();
            goto Start;
        }

        updateCharacters(a, b, x, 'A');
        updateCharacters(a, b, y, 'B');
        if (isValidGameState(a, b)) {
            displayHelp();
            printCase(a, b);
        } else {
            gotoxy(15, 21);
            printf("商人被杀，按任意键重新开始...");
            getch();
            goto Start;
        }

        countA = countB = 0;
        for (i = 0; i < 6; i++) {
            if (b[i] == 'A') countA++;
            else if (b[i] == 'B') countB++;
        }

        gotoxy(20, 18);
        printf("输入回此岸商人的人数： ");
        scanf("%d", &x);
        gotoxy(20, 18);
        printf("输入回此岸随从的人数： ");
        scanf("%d", &y);

        if (!validateInput(countA, countB, x, y)) {
            gotoxy(15, 21);
            printf("输入有误！！按任意键重新开始...");
            getch();
            goto Start;
        }

        updateCharacters(b, a, x, 'A');
        updateCharacters(b, a, y, 'B');
        if (isValidGameState(a, b)) {
            displayHelp();
            printCase(a, b);
        } else {
            gotoxy(15, 21);
            printf("商人被杀，按任意键重新开始...");
            getch();
            goto Start;
        }

        if (countA == 0 && countB == 0) {
            gotoxy(15, 21);
            printf("恭喜你！你已成功帮助商人安全过河！按任意键退出...");
            getch();
            exit(0);
        }
    }
}

void main()
{
    startGame();
}
