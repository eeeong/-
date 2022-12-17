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
                return tmp; // 부모 반환
            tmp = tmp->lchild;
        }
        else
        {
            if (tmp->rchild == NULL)
                return tmp; // 부모 반환
            tmp = tmp->rchild;
        }
    }
    return NULL; // root가 NULL인 경우
}

void insert_node(Node **root, int key, int value)
{
    Node *ptr, *parent = modified_search(*root, key);
    if (parent || !(*root))
    { // key가 존재하지 않거나, 트리가 empty일 때 추가
        ptr = (Node *)malloc(sizeof(Node));
        ptr->key = key;
        ptr->value = value;
        ptr->lchild = NULL;
        ptr->rchild = NULL;

        if (*root)
        {                          // parent 존재
            if (key < parent->key) // 왼쪽에 추가
                parent->lchild = ptr;
            else // 오른쪽 추가
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

Node *min_key_node(Node *node)
{
    Node *curr = node;
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (curr->lchild != NULL)
        curr = curr->lchild;
    return curr;
}

// key 노드 삭제 후 루트 반환
Node *delete_node(Node *root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->key) // 키가 루트보다 작으면 왼쪽 서브 트리
        root->lchild = delete_node(root->lchild, key);
    else if (key > root->key) // 키가 루트보다 크면 오른쪽 서브 트리에 있음
        root->rchild = delete_node(root->rchild, key);
    else
    { // 키가 루트와 같으면 이 노드를 삭제함
        if (root->lchild == NULL)
        {
            Node *temp = root->rchild;
            free(root);
            return temp;
        }
        else if (root->rchild == NULL)
        {
            Node *temp = root->lchild;
            free(root);
            return temp;
        }

        Node *temp = min_key_node(root->rchild);
        root->key = temp->key;                               // 직후 키 복사
        root->rchild = delete_node(root->rchild, temp->key); // 직후 노드 삭제
    }
    return root;
}

int main(void)
{
    Node *A = NULL, *tmp;
    int key_level, input_key, input_data;

    // 입력
    printf("이진 탐색 트리를 생성합니다 \n");
    while (1)
    {
        printf(" (key value) 종료는 -1 -1 >> ");
        scanf("%d %d", &input_key, &input_data);
        if (input_key == -1 || input_data == -1)
            break;
        insert_node(&A, input_key, input_data);
    }
    printf("\t 생성완료 \n완성된 tree의 inorder traversal : ");
    inorder(A);
    printf("\n\n");

    // 삭제
    printf("이진검색트리 노드 삭제 \n");
    while (1)
    {
        printf(" key 입력 >> ");
        scanf("%d", &input_key);
        if (input_key == -1)
            break;
        tmp = search(A, input_key);
        if (A == NULL || tmp == NULL)
        {
            printf("key(%d)인 노드가 없습니다. 삭제 실패 !\n", input_key);
            continue;
        }
        printf("(%d %d) 삭제 합니다 !\n", tmp->key, tmp->value);
        A = delete_node(A, input_key);
        printf("삭제 후 root : %d, inorder traversal : ", A->key);
        inorder(A);
        printf("\n");
    }
    printf("\n");

    // 검색
    printf("이진검색트리 key 검색 \n");
    while (1)
    {
        printf(" key 입력 >> ");
        scanf("%d", &input_key);
        if (input_key == -1)
            break;
        tmp = search(A, input_key);
        if (tmp)
        {
            key_level = searchKeyLevel(A, input_key);
            printf("count : %d, key(%d) value : %f \n", key_level, input_key, tmp->value);
        }
        else
            printf("key(%d)인 노드가 없습니다 \n", input_key);
    }
    free(A);
}