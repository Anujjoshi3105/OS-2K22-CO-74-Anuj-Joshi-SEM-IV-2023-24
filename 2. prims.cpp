#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

int parent[MAXN], rank_arr[MAXN];

int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void union_sets(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rank_arr[x] < rank_arr[y])
    {
        int temp = x;
        x = y;
        y = temp;
    }
    parent[y] = x;
    if (rank_arr[x] == rank_arr[y])
        rank_arr[x]++;
}

typedef struct
{
    int u, v, w;
} Edge;

int compare(const void *a, const void *b)
{
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main()
{
    int n, m;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);
    int i;
    for (i = 1; i <= n; i++)
    {
        parent[i] = i;
        rank_arr[i] = 1;
    }

    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    printf("Enter edges in the format 'u v w' (source, destination, weight):\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    int mst_weight = 0;
    for (i = 0; i < m; i++)
    {
        Edge edge = edges[i];
        if (find(edge.u) != find(edge.v))
        {
            mst_weight += edge.w;
            union_sets(edge.u, edge.v);
            printf("Edge: %d - %d Weight: %d\n", edge.u, edge.v, edge.w);
        }
    }

    printf("Total MST Weight: %d\n", mst_weight);

    free(edges);
    return 0;
}
