#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 99999
#define TRUE 1
#define FALSE 0

void printAdjacentGraph(int **graph, int n)
{
    printf("      ");
    for (int i = 0; i < n; i++)
        printf("   [%2d]", i);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("  [%2d]", i);
        for (int j = 0; j < n; j++)
            printf("  %5d", graph[i][j]);
        printf("\n");
    }
    printf("\n");
}

int choose(int distance[], int n, short int found[])
{
    int min = MAX_VALUE, min_pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (found[i] == FALSE && distance[i] < min)
        {
            min = distance[i];
            min_pos = i;
        }
    }
    return min_pos;
}

void shortestpath(int v, int **graph, int distance_v[], int n, short int found[])
{
    int u, w;
    for (int i = 0; i < n; i++)
    {
        distance_v[i] = graph[v][i];
        found[i] = FALSE;
    }
    found[v] = TRUE;
    for (int i = 0; i < n - 2; i++)
    {
        u = choose(distance_v, n, found);
        found[u] = TRUE;
        for (w = 0; w < n; w++)
        {
            if (found[w] == FALSE && distance_v[u] + graph[u][w] < distance_v[w])
                distance_v[w] = distance_v[u] + graph[u][w];
        }
    }
}

void allocosts(int **graph, int **distance, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            distance[i][j] = graph[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (distance[i][k] + distance[k][j] < distance[i][j])
                    distance[i][j] = distance[i][k] + distance[k][j];
}

int main(void)
{
    while (1)
    {
        int **graph, *distance_v, **distance, n;
        short int *found;

        printf("11.1. 인접 행렬 형태의 방향성 그래프 생성 \n");
        printf("  노드 수 (n) >> ");
        scanf("%d", &n);
        if (n == -1)
            break;
        //동적할당 및 초기화
        graph = (int **)malloc(n * sizeof(int *));
        distance = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++)
        {
            graph[i] = (int *)malloc(n * sizeof(int));
            distance[i] = (int *)malloc(n * sizeof(int));
        }
        distance_v = (int *)malloc(n * sizeof(int));
        found = (short int *)malloc(n * sizeof(short int));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    graph[i][j] = 0;
                else
                    graph[i][j] = MAX_VALUE;
            }
        }
        while (1)
        {
            int from, to, weight;
            printf("  에지 정보 (from to weight) >> ");
            scanf("%d %d %d", &from, &to, &weight);
            if (from == -1 || to == -1 || weight == -1)
                break;
            graph[from][to] = weight;
        }
        printf("\n  인접 행렬을 이용한 그래프의 구성 : \n");
        printAdjacentGraph(graph, n);

        printf("11.2. Dijkstra 최단 경로 (단일 출발점) \n");
        while (1)
        {
            int v;
            printf("  시작 노드 (v) >> ");
            scanf("%d", &v);
            if (v == -1)
                break;
            shortestpath(v, graph, distance_v, n, found);
            printf("  Distance : ");
            for (int i = 0; i < n; i++)
                printf("  %d", distance_v[i]);
            printf("\n");
        }

        printf("\n11.3. Allcosts 최단 경로 (모든 경로) \n");
        printf("  All Path Distance : \n");
        allocosts(graph, distance, n);
        printAdjacentGraph(distance, n);

        //동적할당 해제
        for (int i = 0; i < n; i++)
        {
            free(graph[i]);
            free(distance[i]);
        }
        free(graph);
        free(distance);
        free(distance_v);
        free(found);
    }

    return 0;
}