#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

#define COL 10      // 2.1
#define MAX_SIZE 16 // 2.2
#define MAX_SIZE2 5 // 2.3
#define SWAP(x, y, t) (t = x, x = y, y = t)

int WordCount(char *list);               //배열에 저장된 문자열의 길이를 구하는 함수
void PermChar(char *list, int i, int n); // char형 순열 출력 함수
void PermInt(int *list, int i, int n);   // int형 순열 출력 함수

int main()
{
    // =================== 2.1 ===================
    char A[][COL] = {"GO", "BOY", "GIRl", "GIRLS"}; // A[0]:"GO", A[1]:"BOY", A[2]:"GIRL", A[3]:"GIRLS"
    printf("2.1. 순열 알고리즘 호출\n");
    for (int i = 0; i < 4; i++)
    {
        printf("제시문자열 : %s\n", A[i]);
        PermChar(A[i], 0, WordCount(A[i]) - 1);
        printf("\n");
    }

    // =================== 2.2 ===================
    int B[MAX_SIZE]; //크기 16의 배열 생성
    clock_t start;
    double duration;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        B[i] = i + 1; //배열 B에 1,2,3,4,5...저장
    }
    printf("\n2.2. 1부터 n사이의 숫자들을 이용한 순열. (범위 1~16)\n");
    while (1)
    {
        int n;
        printf("입력 >> ");
        scanf("%d", &n);
        if (n == -1)
        {
            printf("종료 Bye!~~\n\n");
            break;
        }
        if (n < 1 || n > 16)
        {
            printf("범위(1~16)를 벗어남!\n");
            continue;
        }
        start = clock();
        PermInt(B, 0, n - 1);
        duration = (double)(clock() - start) / CLOCKS_PER_SEC; //걸린 시간 측정
        printf("\n실행시간 : %f\n3", duration);
    }

    // =================== 2.2 ===================
    printf("2.3. 순열 원소 개수를 1~10까지 변화시키며 실행 시간 관찰\n");
    double run_time[MAX_SIZE2]; //측정 시간을 저장할 배열
    for (int i = 0; i < MAX_SIZE2; i++)
    {
        double duration;
        clock_t start = clock();
        PermInt(B, 0, i);
        run_time[i] = (double)(clock() - start) / CLOCKS_PER_SEC; //걸린 시간
        printf("\n");
    }
    printf("  원소개수    실행시간\n");
    for (int i = 0; i < MAX_SIZE2; i++)
    {
        printf("%6d %15f\n", i + 1, run_time[i]);
    }

    return 0;
}

int WordCount(char *list)
{
    int count = 0;
    for (int i = 0; list[i] != '\0'; i++)
    {
        count++;
    }
    return count;
}

void PermChar(char *list, int i, int n)
{
    int j, temp;
    if (i == n)
    {
        printf("%-8s", list); //문자열 출력
    }
    else
    {
        for (j = i; j <= n; j++)
        {
            SWAP(list[i], list[j], temp);
            PermChar(list, i + 1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}

void PermInt(int *list, int i, int n)
{
    int j, temp;
    if (i == n)
    {
        for (j = 0; j <= n; j++)
        {
            printf("%d", list[j]);
        }
        printf("   ");
    }
    else
    {
        for (j = i; j <= n; j++)
        {
            SWAP(list[i], list[j], temp);
            PermInt(list, i + 1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}