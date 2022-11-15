#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} Node;

// 5개의 노드를 가진 Tree를 직접 생성
Node *makeTreeByCode()
{
    Node *root, *tmp, *node;
    node = (Node *)malloc(sizeof(Node));
    node->data = 5;
    tmp = node;
    root = tmp;

    node = (Node *)malloc(sizeof(Node));
    node->data = 3;
    tmp->lchild = node;

    tmp = tmp->lchild;
    node = (Node *)malloc(sizeof(Node));
    node->data = 1;
    node->lchild = NULL, node->rchild = NULL;
    tmp->lchild = node;

    node = (Node *)malloc(sizeof(Node));
    node->data = 4;
    node->lchild = NULL, node->rchild = NULL;
    tmp->rchild = node;

    tmp = root;
    node = (Node *)malloc(sizeof(Node));
    node->data = 8;
    node->lchild = NULL, node->rchild = NULL;
    tmp->rchild = node;

    return root;
}

// L->V->R 출력
void inorder(Node *ptr)
{
    if (ptr)
    {
        inorder(ptr->lchild);
        printf("%d ", ptr->data);
        inorder(ptr->rchild);
    }
}

// V->L->R
void preorder(Node *ptr)
{
    if (ptr)
    {
        printf("%d ", ptr->data);
        preorder(ptr->lchild);
        preorder(ptr->rchild);
    }
}

// L->R->V
void postorder(Node *ptr)
{
    if (ptr)
    {
        postorder(ptr->lchild);
        postorder(ptr->rchild);
        printf("%d ", ptr->data);
    }
}

//이진트리 동일성 검사 (동일하면 : 1, 다르면 : 0)
int equal(Node *A, Node *B)
{
    return ((!A && !B) || (A && B && A->data == B->data && equal(A->lchild, B->lchild) && equal(A->rchild, B->rchild)));
}

//트리 전체 복사 (복사된 트리의 root노드 리턴) postorder 참고
Node *copy(Node *original)
{
    Node *tmp = NULL;
    if (original)
    {
        tmp = (Node *)malloc(sizeof(Node));
        tmp->lchild = copy(original->lchild);
        tmp->rchild = copy(original->rchild);
        tmp->data = original->data;
    }
    return tmp;
}

//트리 swap 후 복사 (swap된 트리의 root노드 리턴)
Node *swap(Node *original)
{
    Node *tmp = NULL;
    if (original)
    {
        tmp = (Node *)malloc(sizeof(Node));
        tmp->lchild = swap(original->rchild); //왼쪽자식은 오른쪽 자식으로
        tmp->rchild = swap(original->lchild); //오른쪽자식은 왼쪽 자식으로
        tmp->data = original->data;
    }
    return tmp;
}

void addRandomNode(Node **ptr, int n)
{
    int random = rand() % 2;
    if (*ptr)
        printf("%d의 random choice %d \n", n, random);

    if (*ptr == NULL)
    {
        *ptr = (Node *)malloc(sizeof(Node));
        (*ptr)->data = n;
        (*ptr)->lchild = NULL;
        (*ptr)->rchild = NULL;
    }
    else if (random == 0)
        addRandomNode(&((*ptr)->lchild), n); //왼쪽 노드로
    else if (random == 1)
        addRandomNode(&((*ptr)->rchild), n); //오른쪽 노드로
}

Node *makeNTree()
{
    Node *root, *ptr;
    int input_n;
    printf("input n >> ");
    scanf("%d", &input_n);

    // root 노드 초기화
    ptr = (Node *)malloc(sizeof(Node));
    ptr->data = 1;
    ptr->lchild = NULL;
    ptr->rchild = NULL;
    root = ptr;

    for (int i = 2; i <= input_n; i++)
        addRandomNode(&root, i);
    return root;
}

void printAllOrder(Node *ptr, const char tree_name[])
{
    printf("inorder(%s) : ", tree_name);
    inorder(ptr);
    printf("\npreorder(%s) : ", tree_name);
    preorder(ptr);
    printf("\npostorder(%s) : ", tree_name);
    postorder(ptr);
    printf("\n");
}

int main(void)
{
    Node *A, *B, *C, *D;
    srand(time(NULL));

    printf("8.1.1 트리 구성 (A = makeTreeByCode()) \n");
    printf("8.1.2 트리 순회 (A) \n");
    A = makeTreeByCode();
    printAllOrder(A, "A");

    printf("\n8.2.1 트리 복사 (B = copy(A)) \n");
    printf("8.2.2 트리 순회 (B) \n");
    B = copy(A);
    printAllOrder(B, "B");

    printf("\n8.2.3 트리 동질성 검사 (equal(A,B)) \n");
    printf("equal(A, B) : ");
    if (equal(A, B))
        printf("TRUE \n");
    else
        printf("FALSE \n");

    printf("\n8.2.4 트리 swap (C = swap(A)) \n");
    printf("8.2.5 트리 순회 (C) \n");
    C = swap(A);
    printAllOrder(C, "C");

    printf("\n8.3.1 랜덤 트리 자동 생성 (D) \n");
    D = makeNTree();
    printAllOrder(D, "D");

    return 0;
}