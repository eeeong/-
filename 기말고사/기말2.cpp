#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

void clearVisit(int *visit, int n)
{
    for (int i = 0; i < n; i++)
        visit[i] = 0;
}

void DFS(int **graph, int v, int *visit, int n)
{
    visit[v] = TRUE;
    printf("%2d ", v);
    for (int i = 0; i < n; i++)
    {
        if (graph[v][i] == 1 && visit[i] == 0)
            DFS(graph, i, visit, n);
    }
}

void spanning_DFS(int **graph, int v, int *visit, int n)
{
    visit[v] = TRUE;
    for (int i = 0; i < n; i++)
    {
        if (graph[v][i] == 1 && visit[i] == 0)
        {
            printf("(%d, %d) ", v, i);
            spanning_DFS(graph, i, visit, n);
        }
    }
}

int main(void)
{
    int **graph, n, v1, v2, start_v;
    int *visit;

    printf("인접 행렬 무방향성 그래프 생성 \n");
    printf("노드 개수 >> ");
    scanf("%d", &n);
    graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        *(graph + i) = (int *)calloc(n, sizeof(int));
    visit = (int *)calloc(n, sizeof(int));
    while (1)
    {
        printf("에지 정보(vi, vj) >> ");
        scanf("%d %d", &v1, &v2);
        if (v1 == -1 || v2 == -1)
            break;
        graph[v1][v2] = 1;
        graph[v2][v1] = 1;
    }

    printf("완성된 인접행렬 : \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    printf("Start Vertex # >> ");
    scanf("%d", &start_v);
    printf("DFS : ");
    clearVisit(visit, n);
    DFS(graph, start_v, visit, n);
    printf("\n");

    printf("spanning Tree by DFS : ");
    clearVisit(visit, n);
    spanning_DFS(graph, start_v, visit, n);
    printf("\n");

    return 0;
}