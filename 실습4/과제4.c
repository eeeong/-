#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void sizeUpArray(int **array, int *max_size) //배열의 저장공간을 2배로 늘린다
{
    int *temp;
    temp = (int *)realloc(*array, 2 * (*max_size) * sizeof(int));

    printf("*** 배열이 꽉 찼습니다! ");
    if (temp == NULL) // realloc 실패
    {
        printf("-> 배열 realloc 실패! ***\n");
        free(temp);
        return; // array는 변화 없이 종료
    }
    printf("-> 저장공간 크기 2배 완료 ***\n");
    *array = temp;
    *max_size *= 2;
}

// stack은 이중포인터로 받는다!!!!**
void push(int **stack, int item, int *stack_top, int *max_stack_size)
{
    if (*stack_top == *max_stack_size - 1) // stack full
        sizeUpArray(stack, max_stack_size);

    (*stack)[++(*stack_top)] = item;
}

int pop(int *stack, int *stack_top)
{
    if (*stack_top == -1)
    {
        printf("스택이 비어있습니다!!\n");
        return -1;
    }
    return stack[(*stack_top)--];
}

void sortQueue(int *queue, int *queue_f, int *queue_r, int *now_queue_size, int *max_queue_size) //큐 정렬
{
    int *copy_queue = (int *)malloc(*max_queue_size * sizeof(int));
    for (int i = 0; i < *max_queue_size; i++) // copy_queue에 원래 queue를 복사
        copy_queue[i] = queue[i];

    for (int i = 0; i < *now_queue_size; i++)
    {
        *queue_f = (*queue_f + 1) % *max_queue_size;
        queue[i] = copy_queue[*queue_f];
    }
    *queue_f = -1;
    *queue_r = *now_queue_size - 1;
    printf("*** 큐 정렬 완료 ***\n");
}

void addQ(int **queue, int item, int *queue_f, int *queue_r, int *now_queue_size, int *max_queue_size)
{
    if (*queue_f == -1 && *queue_r == *max_queue_size - 1) // queue full
        sizeUpArray(queue, max_queue_size);
    else if (*queue_r == *max_queue_size - 1) //큐의 공간이 남아서 큐를 정렬해주기
        sortQueue(*queue, queue_f, queue_r, now_queue_size, max_queue_size);
    (*queue)[++(*queue_r)] = item;
    (*now_queue_size)++;
}

int deleteQ(int *queue, int *queue_f, int *queue_r, int *now_queue_size, int *max_queue_size)
{
    if (*queue_f == *queue_r) // queue enpty
    {
        printf("큐가 비어있습니다!!\n");
        return -1;
    }
    (*now_queue_size)--;
    return queue[++(*queue_f)];
}

void addCQ(int **circle_queue, int item, int *queue_f, int *queue_r, int *now_c_queue_size, int *max_c_queue_size)
{
    if (*queue_f == *queue_r && *now_c_queue_size == *max_c_queue_size) // queue full
    {
        sortQueue(*circle_queue, queue_f, queue_r, now_c_queue_size, max_c_queue_size);
        sizeUpArray(circle_queue, max_c_queue_size);
        *queue_f = *max_c_queue_size - 1;
    }
    *queue_r = (*queue_r + 1) % *max_c_queue_size;
    (*circle_queue)[*queue_r] = item;
    (*now_c_queue_size)++;
}

int deleteCQ(int *circle_queue, int *queue_f, int *queue_r, int *now_c_queue_size, int *max_c_queue_size)
{
    if (*queue_f == *queue_r && *now_c_queue_size == 0) // queue enpty
    {
        printf("큐가 비어있습니다!!\n");
        return -1;
    }
    (*now_c_queue_size)--;
    *queue_f = (*queue_f + 1) % *max_c_queue_size;
    return circle_queue[*queue_f];
}

int main(void)
{
    int *stack, *queue, *circle_queue, menu, item;
    int max_stack_size = 10, max_queue_size = 10, max_c_queue_size = 10;
    int stack_top = -1, now_queue_size = 0, now_c_queue_size = 0;
    int queue_f = -1, queue_r = -1;

    stack = (int *)malloc(max_stack_size * sizeof(int));
    queue = (int *)malloc(max_queue_size * sizeof(int));
    circle_queue = (int *)malloc(max_c_queue_size * sizeof(int));

    // ==================== 4.1 스택 ====================
    printf("4.1. 스택\n");
    while (1)
    {
        printf("스택 - (1.push / 2.pop / -1.종료) >> ");
        scanf("%d", &menu);
        if (menu == -1)
            break;
        else if (menu != 1 && menu != 2)
        {
            printf("1, 2, -1 중 입력해요!\n");
            continue;
        }

        if (menu == 1) // push
        {
            printf("push item >> ");
            scanf("%d", &item);
            // push(stack, item, &stack_top, &max_stack_size);
            push(&stack, item, &stack_top, &max_stack_size);
        }
        else // pop
            printf("pop item >> %d 삭제!\n", pop(stack, &stack_top));

        printf("%6s : %-6s\n", "index", "item");
        for (int i = 0; i <= stack_top; i++)
            printf("%6d : %-6d\n", i, stack[i]);
        printf("\n");
    }

    // ==================== 4.2 큐 ====================
    printf("4.2. 큐\n");
    while (1)
    {
        printf("큐 - (1.addQ / 2.deleteQ / -1.종료) >> ");
        scanf("%d", &menu);
        if (menu == -1)
            break;
        else if (menu != 1 && menu != 2)
        {
            printf("1, 2, -1 중 입력해요!\n");
            continue;
        }

        if (menu == 1) // add
        {
            printf("addQ item >> ");
            scanf("%d", &item);
            addQ(&queue, item, &queue_f, &queue_r, &now_queue_size, &max_queue_size);
        }
        else // delete
            printf("pop item >> %d 삭제!\n", deleteQ(queue, &queue_f, &queue_r, &now_queue_size, &max_queue_size));

        printf("%6s : %-6s\n", "index", "item");
        for (int i = queue_f + 1; i <= queue_r; i++)
            printf("%6d : %-6d\n", i, queue[i]);
        printf("\n");
    }

    // ==================== 4.3 원형 큐 ====================
    printf("4.3. 원형 큐\n");
    queue_f = 4;
    queue_r = 4;
    while (1)
    {
        printf("원형 큐 - (1.addCQ / 2.deleteCQ / -1.종료) >> ");
        scanf("%d", &menu);
        if (menu == -1)
            break;
        else if (menu != 1 && menu != 2)
        {
            printf("1, 2, -1 중 입력해요!\n");
            continue;
        }

        if (menu == 1) // add
        {
            printf("addCQ item >> ");
            scanf("%d", &item);
            addCQ(&circle_queue, item, &queue_f, &queue_r, &now_c_queue_size, &max_c_queue_size);
        }
        else // delete
            printf("pop item >> %d 삭제!\n", deleteCQ(circle_queue, &queue_f, &queue_r, &now_c_queue_size, &max_c_queue_size));

        printf("%6s : %-6s\n", "index", "item");
        for (int i = 0; i < now_c_queue_size; i++)
        {
            int idx = (queue_f + 1 + i) % max_c_queue_size;
            printf("%6d : %-6d\n", idx, circle_queue[idx]);
        }
        printf("\n");
    }

    free(stack);
    free(queue);
    free(circle_queue);

    return 0;
}