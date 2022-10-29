#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
} NODE;

void print_list(struct node *A)
{
    struct node *tmp;

    printf("리스트 : Head->");
    for (tmp = A; tmp != NULL; tmp = tmp->link)
        printf("%d->", tmp->data);
    printf("Null\n");
}

void insert_front(struct node **A, int data)
{
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->link = *A;
    (*A) = ptr;
}

void insert_last(struct node **A, int data)
{
    struct node *ptr, *tmp;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->link = NULL;
    tmp = *A;

    if (tmp == NULL)
    {
        *A = ptr;
        return;
    }

    for (; tmp->link != NULL; tmp = tmp->link)
        ;
    tmp->link = ptr;
}

int delete_front(struct node **A)
{
    struct node *tmp = *A;
    int d_value;

    if (tmp == NULL) //리스트가 비어있다
        return -999;

    d_value = tmp->data;
    *A = tmp->link;
    free(tmp);

    return d_value;
}

// delete는 변수명으로 사용 불가
int delete_(struct node **A, int data)
{
    struct node *tmp, *p = NULL, *target = NULL; // p:tmp 이전노드, target:삭제할노드
    int d_value;

    tmp = *A;
    while (tmp != NULL)
    {
        if (tmp->data == data)
        { //삭제할 노드 찾음
            target = tmp;
            break;
        }
        p = tmp;
        tmp = tmp->link;
    } // target:삭제할 노드, p:target 이전 노드 / 존재하지 않는 경우엔 target:NULL

    if (target == NULL)
        d_value = -999; //삭제할 노드 존재 X
    else
    {                     //삭제할 노드 존재 O
        if (target == *A) //첫노드인 경우
            *A = (*A)->link;
        else
            p->link = target->link;
        d_value = target->data;
        free(target);
    }

    return d_value;
}

int search(struct node *A, int data)
{
    struct node *tmp;
    int idx = -1; //찾을 노드의 인덱스

    tmp = A;
    for (; tmp != NULL; tmp = tmp->link)
    {
        idx += 1;
        if (tmp->data == data)
            break; //노드 찾음
    }
    if (tmp == NULL)
        idx = -999; //찾는 노드가 존재하지 않음

    return idx;
}

int main(void)
{
    struct node *list = NULL, *stack = NULL, *queue = NULL;
    int menu, data;

    printf("============== 6.1 ==============\n");
    while (1)
    {
        printf("리스트 기본연산\n");
        printf("0.print_list \n1.insert_front \n2.insert_last \n3.delete_front \n4.delete_ \n5.search \n-1.exit \n");
        printf("어떤 기능을 수행할까요? >> ");
        scanf("%d", &menu);

        if (menu == -1)
        {
            printf("~~~~~종료~~~~~\n\n");
            break;
        }
        else if (menu == 0)
            print_list(list);
        else if (menu == 1 || menu == 2 || menu == 4 || menu == 5)
        {
            printf("데이터 입력 >> ");
            scanf("%d", &data);
            switch (menu)
            {
            case 1:
                insert_front(&list, data);
                break;
            case 2:
                insert_last(&list, data);
                break;
            case 4:
                printf("삭제 데이터 : %d\n", delete_(&list, data));
                break;
            case 5:
                printf("노드 번호 : %d\n", search(list, data));
                break;
            }
            print_list(list);
        }
        else if (menu == 3)
        {
            printf("삭제 데이터 : %d\n", delete_front(&list));
            print_list(list);
        }
        else
            printf("!!! 메뉴를 잘못 입력하심 !!!\n");

        printf("\n");
    }

    printf("============== 6.2 ==============\n");
    while (1)
    {
        printf("리스트로 구현한 스택\n");
        printf("1.push \n2.pop \n-1.exit \n");
        printf("어떤 기능을 수행할까요? >> ");
        scanf("%d", &menu);

        if (menu == -1)
        {
            printf("~~~~~종료~~~~~\n\n");
            break;
        }
        else if (menu == 1)
        {
            printf("push item 입력 >> ");
            scanf("%d", &data);
            insert_front(&stack, data);
            print_list(stack);
        }
        else if (menu == 2)
        {
            printf("pop item : %d\n", delete_front(&stack));
            print_list(stack);
        }
        else
            printf("!!! 메뉴를 잘못 입력하심 !!!\n");

        printf("\n");
    }

    printf("============== 6.3 ==============\n");
    while (1)
    {
        printf("리스트로 구현한 큐\n");
        printf("1.addQ \n2.deleteQ \n-1.exit \n");
        printf("어떤 기능을 수행할까요? >> ");
        scanf("%d", &menu);

        if (menu == -1)
        {
            printf("~~~~~ 종료 ~~~~~\n\n");
            break;
        }
        else if (menu == 1)
        {
            printf("addQ item 입력 >> ");
            scanf("%d", &data);
            insert_last(&queue, data);
            print_list(queue);
        }
        else if (menu == 2)
        {
            printf("pop item : %d\n", delete_front(&queue));
            print_list(queue);
        }
        else
            printf("!!! 메뉴를 잘못 입력하심 !!!\n");

        printf("\n");
    }

    // free

    return 0;
}