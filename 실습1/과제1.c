#define _CRT_SECURE_NO_WARNINGS // CRT에서 보안에 관련된 warning들을 하지 않겠다. (가장 상단에!)
#include <stdio.h>
#include <stdlib.h> //rand() 사용
#include <time.h>

#define MAX_SIZE 100000
#define MAX_SIZE2 1000000
#define MAX_SIZE3 100000
#define MAX_SIZE4 50000

void swap(int *a, int *b);                                     // a,b 스왑 함수
void sort(int A[], int n);                                     // A 배열 정렬 함수
int is_sorted(int A[], int n);                                 // A 배열 정렬 확인 함수
void printComplete();                                          //"완료" 출력 함수
int binsearch(int list[], int searchnum, int left, int right); //이진검색 함수
void runBinSearch(int list[], int list_size);                  //이진검색 반복 함수

int main(void)
{
    srand(time(NULL));

    // =================== 1.1 ===================
    printf("1.1. 무작위 %d개 정수 생성 및 정렬, 정렬 검사 수행\n", MAX_SIZE);
    printf("1.1.1 배열 A에 %d개의 정수를 무작위로 생성 후 저장\n", MAX_SIZE);
    int A[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        A[i] = rand() % MAX_SIZE + 1;
        if (i < 100)
        {
            printf("%8d ", A[i]);
            if ((i + 1) % 15 == 0) // 15개씩 정렬
                printf("\n");
        }
        else if (i == MAX_SIZE - 1)
            printf(" ......100개 초과 출력 안 함\n");
    }
    printComplete();

    printf("1.1.2 배열 A에 무작위로 저장된 정수 정렬\n");
    sort(A, MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (i < 100)
        {
            printf("%8d ", A[i]);
            if ((i + 1) % 15 == 0)
                printf("\n");
        }
        else if (i == MAX_SIZE - 1)
            printf(" ......100개 초과 출력 안 함\n");
    }
    printComplete();

    printf("1.1.3 배열 A에 정렬된 정수의 정렬 상태 확인\n");
    if (is_sorted(A, MAX_SIZE))
        printf("\t 정렬 완료 !!\n");

    // =================== 1.2 ===================
    printf("\n1.2. 배열의 크기를 100 ~ 1,000,000까지 바꾸며 sort 함수의 실행 시간 측정\n");
    printf("%10s %10s %15s\n", "n", "시간", "정렬상태");
    for (int i = 100; i <= MAX_SIZE2; i *= 10)
    {
        for (int j = 1; j < 10; j++)
        {
            int size = i * j;
            int B[MAX_SIZE2];
            clock_t start;   //시작 시간
            double duration; //걸린 시간

            for (int i2 = 0; i2 < size; i2++)
                B[i2] = size - i2;

            start = clock(); //현재시간
            sort(B, size);
            duration = (double)(clock() - start) / CLOCKS_PER_SEC; //걸린 시간 측정

            if (is_sorted(B, size))
                printf("%10d %10.5lf %10s\n", size, duration, "정렬됨");

            if (size == MAX_SIZE2)
                break;
        }
    }

    // =================== 1.3 ===================
    printf("1.3. %d개의 정수를 무작위로 생성하여 정렬 후 이진검색 수행\n", MAX_SIZE3);
    printf("1.3.1. 배열에 %d개의 정수를 무작위로 생성하여 저장\n", MAX_SIZE3);
    int C[MAX_SIZE3];
    for (int i = 0; i < MAX_SIZE3; i++)
    {
        C[i] = rand() % MAX_SIZE3 + 1;
    }
    printComplete();

    printf("1.3.2. 배열에 무작위로 저장된 정수 정렬\n");
    sort(C, MAX_SIZE3);
    printComplete();

    printf("1.3.3. 배열에 정렬된 정수의 정렬 상태 확인\n");
    if (is_sorted(C, MAX_SIZE3))
        printf("\t 정렬 완료 !!\n");
    runBinSearch(C, MAX_SIZE3);

    // =================== 1.4 ===================
    // 100,000개의 정수
    printf("1.4. 배열의 크기를 변화하며 counter의 값을 관찰\n");
    printf("1.4.1. 배열의 %d의 정수를 역순으로 생성하여 저장\n", MAX_SIZE3);
    int D1[MAX_SIZE3];
    for (int i = 0; i < MAX_SIZE3; i++)
    {
        D1[i] = MAX_SIZE3 - i;
    }
    printComplete();

    printf("1.4.2. 배열에 저장된 %d개의 정수 정렬\n", MAX_SIZE3);
    sort(D1, MAX_SIZE3);
    printComplete();

    printf("1.4.3. 배열에 정렬된 정수의 정렬 상태 확인\n");
    if (is_sorted(D1, MAX_SIZE3))
        printf("\t 정렬 완료 !!\n");

    runBinSearch(D1, MAX_SIZE3);

    // 50,000개의 정수
    printf("1.4. 배열의 크기를 변화하며 counter의 값을 관찰\n");
    printf("1.4.1. 배열의 %d의 정수를 역순으로 생성하여 저장\n", MAX_SIZE4);
    int D2[MAX_SIZE4];
    for (int i = 0; i < MAX_SIZE4; i++)
    {
        D2[i] = MAX_SIZE4 - i;
    }
    printComplete();

    printf("1.4.2. 배열에 저장된 %d개의 정수 정렬\n", MAX_SIZE4);
    sort(D2, MAX_SIZE4);
    printComplete();

    printf("1.4.3. 배열에 정렬된 정수의 정렬 상태 확인\n");
    if (is_sorted(D2, MAX_SIZE4))
        printf("\t 정렬 완료 !!\n");

    runBinSearch(D2, MAX_SIZE4);

    return 0;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int A[], int n)
{
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j] < A[min])
                min = j;
        }
        swap(&A[i], &A[min]);
    }
}

int is_sorted(int A[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i] > A[i + 1])
        { //정렬 실패
            return 0;
        }
    }
    return 1; //정렬 성공
}

void printComplete()
{
    printf("\t완료\n");
}

int binsearch(int list[], int searchnum, int left, int right)
{
    int middle, counter = 0;
    while (left <= right)
    {
        middle = (left + right) / 2;
        counter++;

        if (searchnum == list[middle])
        { //찾음
            return counter;
        }
        else if (searchnum < list[middle])
            right = middle - 1; //찾는 숫자가 더 작음
        else
            left = middle + 1; //찾는 숫자가 더 큼
    }
    return -1; //찾기 실패
}

void runBinSearch(int list[], int list_size)
{
    while (1)
    {
        int search, counter;
        printf("검색 데이터( 1 ~ %d ) >> ", list_size);
        scanf("%d", &search);
        if (search == -1)
        {
            printf("검색 종료 ~ ~ ~ ~ ~\n\n");
            break;
        }
        else if (search < 1 || search > list_size)
            continue;
        counter = binsearch(list, search, 0, list_size - 1);
        printf("검색 데이터 : %10d,\tCounter : %4d\n", search, counter);
    }
}