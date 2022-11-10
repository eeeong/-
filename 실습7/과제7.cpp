#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) ((x > y) ? 1 : ((x == y) ? 0 : -1))
#define IS_FULL(ptr) (!(ptr)) //메모리 할당 실패

//실습7 시작
typedef struct polyNode *polyPointer; //걍 안 쓸 거임
typedef struct polyNode
{
    float coef; //계수
    int expon;  //지수
    polyNode *link;
} polyNode;

polyNode *avail = NULL; //전역변수 avail

polyNode *getNode(void)
{
    polyNode *node;
    if (avail != NULL)
    { // avail에 노드가 있을 때
        node = avail;
        avail = avail->link;
    }
    else
    { // avail이 비어있을 때
        node = (polyNode *)malloc(sizeof(polyNode));
        if (IS_FULL(node))
        {
            fprintf(stderr, "The memory is full\n");
            exit(1);
        }
    }
    return node;
}

void retNode(polyNode *node)
{
    node->link = avail;
    avail = node;
}

void cerase(polyNode **node)
{
    polyNode *tmp;
    if (*node)
    {
        tmp = (*node)->link;
        (*node)->link = avail;
        avail = tmp;
        *node = NULL;
    }
}

void attach(float coef, int expon, polyNode **rear)
{
    polyNode *tmp;
    tmp = getNode(); //메모리 full은 getNode()에서 검사함
    tmp->coef = coef;
    tmp->expon = expon;
    tmp->link = (*rear)->link; //원형연결리스트라서 추가
    (*rear)->link = tmp;
    *rear = tmp;
}

void print_polynomial(polyNode *poly)
{
    polyNode *front, *tmp;
    front = poly->link;

    printf("%7s %7s\n", "coef", "expon");
    for (tmp = front->link; tmp != front; tmp = tmp->link)
    {
        printf("%7.2f %5d\n", tmp->coef, tmp->expon);
    }
}

polyNode *create_polynomial(void)
{
    polyNode *poly;
    float c;
    int e;
    poly = getNode();
    poly->expon = -1;
    poly->link = poly;

    while (1)
    {
        printf("다항식의 항을 입력하세요(coef expon) >> ");
        scanf("%f %d", &c, &e);
        if (e == -1)
            break;
        attach(c, e, &poly);
    }
    return poly;
}

polyNode *cpadd(polyNode *A, polyNode *B)
{ // A, B는 rear노드 (내가 변경)
    polyNode *startA, *D, *lastD;
    int sum, done = false;
    startA = A->link;
    A = startA->link;
    B = B->link->link;
    D = getNode();
    D->expon = -1;
    D->link = D; //추가
    lastD = D;
    do
    {
        switch (COMPARE(A->expon, B->expon))
        {
        case -1: // A->expon < B->expon
            attach(B->coef, B->expon, &lastD);
            B = B->link;
            break;
        case 0: // A->expon == B->expon
            if (A == startA)
                done = true;
            else
            {
                sum = A->coef + B->coef;
                if (sum)
                    attach(sum, A->expon, &lastD);
                A = A->link;
                B = B->link;
            }
            break;
        case 1:
            attach(A->coef, A->expon, &lastD);
            A = A->link;
        }
    } while (!done);
    // lastD->link = D; //attach에서 자동으로 됨
    return lastD; //변경. 맨 뒤 노드 가리킴
}

polyNode *single_cpmul(polyNode Ai, polyNode *B)
{
    polyNode *Ci, *tmpB;
    float mul;
    Ci = getNode();
    Ci->expon = -1;
    Ci->link = Ci;

    for (tmpB = B->link->link; tmpB != B->link; tmpB = tmpB->link)
    {
        mul = Ai.coef * tmpB->coef;
        if (mul)
            attach(mul, Ai.expon + tmpB->expon, &Ci);
    }
    return Ci;
}

polyNode *cpmul(polyNode *A, polyNode *B)
{
    polyNode *D, *X, *tmpA;
    int count = 1;
    D = getNode();
    D->expon = -1;
    D->link = D;

    for (tmpA = A->link->link; tmpA != A->link; tmpA = tmpA->link, count++)
    {
        X = single_cpmul(*tmpA, B);
        printf("single_mul - C%d(x) : \n", count);
        print_polynomial(X);
        D = cpadd(D, X);
    }
    return D;
}

int main(void)
{
    while (1)
    {
        polyNode *A, *B, *D1, *D2; // A, B, D1, D2는 원형연결리스트의 rear을 가리킨다

        printf("7.1 다항식 생성\n");
        A = create_polynomial();
        printf("다항식 A(x) : \n");
        print_polynomial(A);
        B = create_polynomial();
        printf("다항식 B(x) : \n");
        print_polynomial(B);
        if (A->link == A && B->link == B)
            break; //다항식 둘 다 비어있으면 종료

        printf("7.2 다항식 덧셈\n");
        D1 = cpadd(A, B);
        printf("다항식 덧셈 결과 D(x) : \n");
        print_polynomial(D1);

        printf("7.3 다항식 곱셈\n");
        D2 = cpmul(B, A);
        printf("다항식 곱셈 결과 D(x) : \n");
        print_polynomial(D2);
        printf("\n");

        cerase(&A);
        cerase(&B);
        cerase(&D1);
        cerase(&D2);
    }
    return 0;
}