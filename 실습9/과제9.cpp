#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int key;
    double value;
    struct node *lchild;
    struct node *rchild;
} Node;

void inorder(Node *ptr)
{
    if (ptr)
    {
        inorder(ptr->lchild);
        printf("%d ", ptr->key);
        inorder(ptr->rchild);
    }
}

Node *modified_search(Node *root, int key)
{
    Node *tmp;
    for (tmp = root; tmp != NULL;)
    {
        if (key == tmp->key)
            return NULL; // key값이 이미 존재할 때
        else if (key < tmp->key)
        {
            if (tmp->lchild == NULL)
                return tmp; //부모 반환
            tmp = tmp->lchild;
        }
        else
        {
            if (tmp->rchild == NULL)
                return tmp; //부모 반환
            tmp = tmp->rchild;
        }
    }
    return NULL; // root가 NULL인 경우
}

void insert_node(Node **root, int key)
{
    Node *ptr, *parent = modified_search(*root, key);
    if (parent || !(*root))
    { // key가 존재하지 않거나, 트리가 empty일 때 추가
        ptr = (Node *)malloc(sizeof(Node));
        ptr->key = key;
        ptr->value = 1.0 / key;
        ptr->lchild = NULL;
        ptr->rchild = NULL;

        if (*root)
        {                          // parent 존재
            if (key < parent->key) //왼쪽에 추가
                parent->lchild = ptr;
            else //오른쪽 추가
                parent->rchild = ptr;
        }
        else // root empty
            *root = ptr;
    }
}

Node *search(Node *ptr, int key)
{
    if (!ptr)
        return NULL; // key가 존재하지 않음
    if (key == ptr->key)
        return ptr;
    else if (key < ptr->key)
        return search(ptr->lchild, key);
    else
        return search(ptr->rchild, key);
}

int searchKeyLevel(Node *ptr, int key)
{
    int count = 0;
    if (!ptr)
        return 0; // key가 존재하지 않음 (잘못된 값 리턴)
    if (key == ptr->key)
        return 1;
    else if (key < ptr->key)
        return 1 + searchKeyLevel(ptr->lchild, key);
    else
        return 1 + searchKeyLevel(ptr->rchild, key);
}

void printBstInorder(Node *tree, int n, int *i)
{
    if (tree)
    {
        printBstInorder(tree->lchild, n, i);
        if (*i < 2 || *i > n - 4)
            printf("(%8d, %.6f) \n", tree->key, tree->value);
        if (*i == 2)
            printf("..... \n");
        (*i)++;
        printBstInorder(tree->rchild, n, i);
    }
}

Node *makeBst(int n)
{
    Node *tree = NULL;
    int key, i = 0;
    for (int i = 0; i < n; i++)
    {
        key = (rand() / (0x7fff * 1.0)) * 100000000;
        insert_node(&tree, key);
    }
    printBstInorder(tree, n, &i);
    return tree;
}

int countNode(Node *tree)
{
    if (!tree)
        return 0;
    return 1 + countNode(tree->lchild) + countNode(tree->rchild);
}

int countDepth(Node *tree)
{
    int n1, n2;
    if (!tree)
        return 0;
    n1 = countDepth(tree->lchild);
    n2 = countDepth(tree->rchild);
    return (n1 > n2) ? n1 + 1 : n2 + 1;
}

int countLeaf(Node *tree)
{
    if (!tree)
        return 0;
    if (tree->lchild == NULL && tree->rchild == NULL)
        return 1;
    return countLeaf(tree->lchild) + countLeaf(tree->rchild);
}

int main(void)
{
    Node *A = NULL, *tmp;
    int n;
    srand(time(NULL));

    printf("9.1. 12개의 (key, value)쌍을 생성하여 이진 탐색 트리 생성 \n");
    // 10, 6, 15, 8, 18, 12, 3, 14, 9, 20, 5, 2 순으로 이진탐색트리 추가
    insert_node(&A, 10);
    insert_node(&A, 6);
    insert_node(&A, 15);
    insert_node(&A, 8);
    insert_node(&A, 18);
    insert_node(&A, 12);
    insert_node(&A, 3);
    insert_node(&A, 14);
    insert_node(&A, 9);
    insert_node(&A, 20);
    insert_node(&A, 5);
    insert_node(&A, 2);
    printf("\t 생성완료 \n완성된 tree의 inorder traversal : ");
    inorder(A);
    printf("\n\n");

    printf("9.2. 생성된 이진 검색 트리에서 key값을 활용한 검색\n");
    while (true)
    {
        Node *tmp;
        int key_level;
        printf("찾고자 하는 key값 입력 >> ");
        scanf("%d", &n);
        if (n == -1)
            break;

        tmp = search(A, n);
        if (tmp)
        {
            key_level = searchKeyLevel(A, n);
            printf("count : %d, key(%d) value : %f \n", key_level, n, tmp->value);
        }
        else
            printf("key(%d)인 노드가 없습니다 \n", n);
    }

    printf("\n9.3. n개의 노드를 가진 이진검색트리 생성시간 및 노드 수, 높이(깊이), 단말노드 수 관찰 \n");
    while (true)
    {
        Node *B;
        clock_t time;
        double duration;
        printf("n개의 노드를 가진 이진검색트리 생성 >> ");
        scanf("%d", &n);
        if (n == -1)
            break;

        printf("(%8s, %8s) \n", "key", "value");
        time = clock();
        B = makeBst(n);
        duration = (double)(clock() - time) / CLOCKS_PER_SEC;

        printf("이진검색트리 B : \n");
        printf("이진검색트리 B의 생성시간 : %.3f \n", duration);
        printf("이진검색트리 B의 노드 수 : %d \n", countNode(B));
        printf("이진검색트리 B의 높이(깊이) : %d \n", countDepth(B));
        printf("이진검색트리 B의 단말노드 수 : %d \n\n", countLeaf(B));
    }
}