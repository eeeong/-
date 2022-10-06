#define _CRT_SUCURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc, realloc

#define COMPARE(x, y) ((x < y) ? -1 : ((x == y) ? 0 : 1))
#define SWAP(x, y, t) (t = x, x = y, y = t)
#define MAX_TERMS 10 //다항식 최대 항

typedef struct //다항식 구조체
{
    float coef; //계수
    int expon;  //지수
} polynomial;

void sortPolyminal(polynomial *poly, int size) //다항식 구조체 배열 정렬
{
    int max;
    polynomial tmp;
    for (int i = 0; i < size - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < size; j++)
        {
            if (poly[max].expon < poly[j].expon)
                max = j;
        }
        SWAP(poly[i], poly[max], tmp);
    }
}

void printPolynomial(polynomial *poly)
{
    printf("%10s %10s\n", "coef", "expon");
    for (int i = 0; poly[i].expon != -1; i++)
    {
        printf("%10.2f %10d\n", poly[i].coef, poly[i].expon);
    }
}

polynomial *padd(polynomial *A, polynomial *B) //다항식의 합을 리턴하는 함수
{                                              // attach 안 씀
    int ia = 0, ib = 0, size_D = 0;
    float coef;
    polynomial *D = (polynomial *)malloc(MAX_TERMS * 3 * sizeof(polynomial));

    while (A[ia].expon != -1 || B[ib].expon != -1) // or으로!! A,B의 모두 끝까지
    {
        if (size_D >= MAX_TERMS) //배열의 크기가 MAX_TERMS를 넘으면 현재 배열 크기의 +1
            D = (polynomial *)realloc(D, (size_D + 1) * sizeof(polynomial));
        switch (COMPARE(A[ia].expon, B[ib].expon))
        {
        case 1: // A지수 > B지수
            D[size_D].coef = A[ia].coef;
            D[size_D].expon = A[ia].expon;
            ia++;
            size_D++;
            break;
        case 0: // A지수 == B지수
            coef = A[ia].coef + B[ib].coef;
            if (coef)
            {
                D[size_D].coef = coef;
                D[size_D].expon = A[ia].expon;
                size_D++;
            }
            ia++;
            ib++;
            break;
        case -1: // A지수 < B지수
            D[size_D].coef = B[ib].coef;
            D[size_D].expon = B[ib].expon;
            ib++;
            size_D++;
        }
    }
    D[size_D].expon = -1; //마지막을 지정
    return D;             // malloc 으로 동적할당하면 함수가 끝나도 사라지지 않음
}

polynomial *single_mul(polynomial Ai, polynomial *B)
{
    polynomial *Ci;
    Ci = (polynomial *)malloc(MAX_TERMS * sizeof(polynomial));

    int size_Ci = 0;
    for (int i = 0; B[i].expon != -1; i++)
    {
        if (i >= MAX_TERMS) //배열의 크기가 MAX_TERMS를 넘으면 현재 배열 크기의 +1
            Ci = (polynomial *)realloc(Ci, (i + 1) * sizeof(polynomial));

        Ci[size_Ci].coef = Ai.coef * B[i].coef;
        Ci[size_Ci].expon = Ai.expon + B[i].expon;
        size_Ci++;
    }

    Ci[size_Ci].expon = -1;
    return Ci;
}

polynomial *pmul(polynomial *A, polynomial *B)
{
    polynomial *D, *Ci;
    D = (polynomial *)malloc(MAX_TERMS * sizeof(polynomial));
    D[0].expon = -1;

    for (int i = 0; A[i].expon != -1; i++)
    {
        Ci = single_mul(A[i], B);
        printf("single_mul - C%d(x)\n", i + 1);
        printPolynomial(Ci);

        D = padd(D, Ci);
    }
    // free(Ci);

    return D;
}

int main(void)
{
    while (1)
    {
        polynomial *A, *B, *C, *D, tmp; // A, B, C 다항식 구조체 배열
        A = (polynomial *)malloc(MAX_TERMS * sizeof(polynomial));
        B = (polynomial *)malloc(MAX_TERMS * sizeof(polynomial));
        int size_A = 0, size_B = 0;

        // =============== 3.1 ===============
        printf("3.1. 다항식 생성\n");
        while (1) // A 다항식 생성
        {
            if (size_A >= MAX_TERMS) //배열의 크기가 MAX_TERMS를 넘으면 현재 배열 크기의 +1
                A = (polynomial *)realloc(A, (size_A + 1) * sizeof(polynomial));
            printf("A(x)의 항을 입력 (coef expon) >> ");
            scanf("%f %d", &(A[size_A].coef), &(A[size_A].expon));
            if (A[size_A].expon == -1)
                break;
            size_A++; // size는 지수 -1 이전까지의 개수가 저장된다
        }
        sortPolyminal(A, size_A); //다항식 A 정렬
        printf("다항식 A(x)\n");
        printPolynomial(A);

        while (1) // B 다항식 생성
        {
            if (size_B >= MAX_TERMS) //배열의 크기가 MAX_TERMS를 넘으면 현재 배열 크기의 +1
                B = (polynomial *)realloc(B, (size_B + 1) * sizeof(polynomial));
            printf("B(x)의 항을 입력 (coef expon) >> ");
            scanf("%f %d", &(B[size_B].coef), &(B[size_B].expon));
            if (B[size_B].expon == -1)
                break;
            size_B++;
        }
        sortPolyminal(B, size_B); //다항식 B 정렬
        printf("다항식 B(x)\n");
        printPolynomial(B);

        // =============== 3.2 ===============
        printf("3.2. 다항식 덧셈\n");

        C = padd(A, B); //함수에서 동적할당 받은 포인터를 반환받기 때문에 따로 동적할당 안 해도 된다!!!!
        printf("다항식 C(x)\n");
        printPolynomial(C);

        // =============== 3.3 ===============
        printf("3.2. 다항식 곱셈\n");

        D = pmul(A, B);
        printf("다항식 D(x)\n");
        printPolynomial(D);
        printf("\n");

        if (A[0].expon == -1 && B[0].expon == -1) // A,B 다항식이 모두 0일 경우 프로그램 종료
        {
            printf("프로그램 종료 -----bye\n");
            free(A);
            free(B);
            free(C);
            free(D);
            break;
        }

        free(A);
        free(B);
        free(C);
        free(D);
    }

    return 0;
}