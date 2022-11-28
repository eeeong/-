#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct node
{
    int vertex;
    struct node *link;
} Node;

void insert_front(struct node **A, int data)
{
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->vertex = data;
    ptr->link = *A;
    (*A) = ptr;
}

void addQ(struct node **A, int data)
{
    struct node *ptr, *tmp;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->vertex = data;
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

int deleteQ(struct node **A)
{
    struct node *tmp = *A;
    int d_value;

    if (tmp == NULL) //리스트가 비어있다
        return -999;

    d_value = tmp->vertex;
    *A = tmp->link;
    free(tmp);

    return d_value;
}

int countDegree(Node *headNode)
{
    int count = 0;
    for (Node *tmp = headNode; tmp; tmp = tmp->link)
        count++;
    return count;
}

void printAdjacencyList(Node *headNode)
{
    for (Node *tmp = headNode; tmp; tmp = tmp->link)
        printf("%d -> ", tmp->vertex);
    printf("end \n");
}

void initialIntArr(int *arr, int k)
{
    for (int i = 0; i < k; i++)
        arr[i] = 0;
}

void dfs(int v, Node **graph, int *visit)
{
    Node *w;

    visit[v] = TRUE;
    printf("%3d ", v);
    for (w = graph[v]; w; w = w->link)
    {
        if (!(visit[w->vertex])) // FALSE
            dfs(w->vertex, graph, visit);
    }
}

void bfs(int v, Node **graph, int *visit)
{
    Node *w, *queue = NULL;

    printf("%3d ", v);
    visit[v] = TRUE;
    addQ(&queue, v);
    while (queue != NULL)
    {
        v = deleteQ(&queue);
        for (w = graph[v]; w; w = w->link)
        {
            if (!(visit[w->vertex]))
            {
                printf("%3d ", w->vertex);
                addQ(&queue, w->vertex);
                visit[w->vertex] = TRUE;
            }
        }
    }
    // printf("\n");
}

void dfsSpanningTrees(int v, Node **graph, int *visit)
{
    Node *w;

    visit[v] = TRUE;
    for (w = graph[v]; w; w = w->link)
    {
        if (!(visit[w->vertex]))
        { // FALSE
            printf("(%d, %d) ", v, w->vertex);
            dfsSpanningTrees(w->vertex, graph, visit);
        }
    }
}

void bfsSpanningTrees(int v, Node **graph, int *visit)
{
    Node *w, *queue = NULL;

    visit[v] = TRUE;
    addQ(&queue, v);
    while (queue != NULL)
    {
        v = deleteQ(&queue);
        for (w = graph[v]; w; w = w->link)
        {
            if (!(visit[w->vertex]))
            {
                printf("(%d, %d) ", v, w->vertex);
                addQ(&queue, w->vertex);
                visit[w->vertex] = TRUE;
            }
        }
    }
    // printf("\n");
}

int main(void)
{
    int k = 0, n1 = 0, n2 = 0;
    int max_degree_node;

    while (1)
    {
        Node **graph;
        int *visit;

        printf("10.1. 인접 리스트 형태의 무방향성 그래프 생성 \n");
        printf("노드 개수 >> ");
        scanf("%d", &k);
        if (k == -1)
            break;
        graph = (Node **)calloc(k, sizeof(Node *));
        visit = (int *)calloc(k, sizeof(int));
        while (1)
        {
            printf("에지 정보(vi, vj) >> ");
            scanf("%d %d", &n1, &n2);
            if (n1 == -1 || n2 == -1)
                break;
            insert_front(&(graph[n1]), n2);
            insert_front(&graph[n2], n1);
        }

        printf("\n인접 리스트를 이용하여 구성한 그래프 \n");
        for (int i = 0; i < k; i++)
        {
            printf("  [%d] : ", i);
            printAdjacencyList(graph[i]);
        }

        printf("\ndegree가 가장 큰 노드와 degree값 : ");
        max_degree_node = 0;
        for (int i = 1; i < k; i++)
            if (countDegree(graph[i]) > countDegree(graph[max_degree_node]))
                max_degree_node = i;
        printf("노드 %d, degree %d \n", max_degree_node, countDegree(graph[max_degree_node]));
        printf("노드 %d와 연결된 노드들 : ", max_degree_node);
        printAdjacencyList(graph[max_degree_node]);

        printf("\n10.2. 탐색 알고리즘 (DFS, BFS) \n");
        printf("  깊이 우선 탐색 (DFS) \n");
        for (int i = 0; i < k; i += 2)
        {
            printf("  시작노드 %d : ", i);
            dfs(i, graph, visit);
            printf("\n");
            initialIntArr(visit, k);
        }

        printf("\n  너비 우선 탐색 (BFS) \n");
        for (int i = 1; i < k; i += 2)
        {
            printf("  시작노드 %d : ", i);
            bfs(i, graph, visit);
            printf("\n");
            initialIntArr(visit, k);
        }

        printf("\n10.3. 신장트리 알고리즘 (DFS, BFS 기반) \n");
        printf("  DFS 신장트리 \n");
        for (int i = 0; i < k; i += 2)
        {
            printf("  시작노드 %d : ", i);
            dfsSpanningTrees(i, graph, visit);
            printf("\n");
            initialIntArr(visit, k);
        }

        printf("\n  BFS 신장트리 \n");
        for (int i = 1; i < k; i += 2)
        {
            printf("  시작노드 %d : ", i);
            bfsSpanningTrees(i, graph, visit);
            printf("\n");
            initialIntArr(visit, k);
        }
        printf("\n");

        //메모리 해제
        for (int i = 0; i < k; i++)
            free(graph[i]);
        free(graph);
        free(visit);
    }

    return 0;
}