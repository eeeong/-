#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) \
    {                 \
        t = x;        \
        x = y;        \
        y = t;        \
    }

int is_sorted(int list[], int n)
{
    for (int i = 0; i < n - 1; i++)
        if (list[i] > list[i + 1])
            return 0;
    return 1;
}

void selection_sort(int list[], int n)
{
    int min, temp;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}

void insertion_sort(int list[], int n)
{
    int j, next;
    for (int i = 1; i < n; i++)
    {
        next = list[i];
        for (j = i - 1; j >= 0 && next < list[j]; j--)
            list[j + 1] = list[j];
        list[j + 1] = next;
    }
}

// stack over flow 문제가 생겨서
//스택 예약 크기 1,000,000,000으로 늘림
void quick_sort(int list[], int left, int right)
{
    int pivot, i, j, temp;
    if (left < right)
    {
        pivot = list[left];
        i = left;
        j = right + 1;

        do
        {
            // i와 j가 배열의 크기를 넘어가는 것을 방지하는 경계 추가
            do
            {
                i++;
                //} while (list[i] < pivot);
            } while (i <= right && list[i] < pivot);
            do
            {
                j--;
                //} while (list[j] > pivot);
            } while (j >= left && list[j] > pivot);
            if (i < j)
                SWAP(list[i], list[j], temp);
        } while (i < j);

        SWAP(list[left], list[j], temp);
        quick_sort(list, left, j - 1);
        quick_sort(list, j + 1, right);
    }
}

// void 배열 정렬 되었는지, 정렬 안 돼있으면 정렬 안 됨 출력, 정렬 됐으면 걸린 시간 출력
void solts_stop_watch(int A[], int n)
{
    clock_t time;
    double duration;
    int *B = (int *)malloc(n * sizeof(int));

    // selection sort
    for (int i = 0; i < n; i++)
        B[i] = A[i];
    time = clock();
    selection_sort(B, n);
    duration = (double)(clock() - time) / CLOCKS_PER_SEC;
    if (is_sorted(B, n))
        printf("  selection sort time : %f \n", duration);
    else
        printf("!!! 정렬 실패 !!!");

    // insertion sort
    for (int i = 0; i < n; i++)
        B[i] = A[i];
    time = clock();
    insertion_sort(B, n);
    duration = (double)(clock() - time) / CLOCKS_PER_SEC;
    if (is_sorted(B, n))
        printf("  insertion sort time : %f \n", duration);
    else
        printf("!!! 정렬 실패 !!!");

    // quick sort
    for (int i = 0; i < n; i++)
        B[i] = A[i];
    time = clock();
    quick_sort(B, 0, n - 1);
    duration = (double)(clock() - time) / CLOCKS_PER_SEC;
    if (is_sorted(B, n))
        printf("      quick sort time : %f \n", duration);
    else
        printf("!!! 정렬 실패 !!! \n");

    printf("\n");
    free(B);
}

int main(void)
{
    int *A, n;

    printf("=== 12.1 랜덤 생성 데이터의 정렬 ===\n");
    while (1)
    {
        printf("  원소 수 : ");
        scanf("%d", &n);
        if (n == -1)
            break;

        A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            A[i] = (int)(rand() / (0x7fff * 1.0)) * 100000000;

        solts_stop_watch(A, n);
        free(A);
    }

    printf("\n=== 12.2. 정렬된 데이터의 정렬 ===\n");
    printf("12.2.1. 오름차순 정렬된 데이터의 정렬 \n");
    while (1)
    {
        printf("  원소 수 : ");
        scanf("%d", &n);
        if (n == -1)
            break;

        A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            A[i] = i + 1;

        solts_stop_watch(A, n);
        free(A);
    }

    printf("\n12.2.2. 내림차순 정렬된 데이터의 정렬 \n");
    while (1)
    {
        printf("  원소 수 : ");
        scanf("%d", &n);
        if (n == -1)
            break;

        A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            A[i] = n - i;

        solts_stop_watch(A, n);
        free(A);
    }

    return 0;
}