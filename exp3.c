#include <stdio.h>

#define INF 9999
#define MAX_NODES 5

struct Router {
    int dist[MAX_NODES];
    int next_hop[MAX_NODES];
};

void calculateShortestPaths(int costMatrix[MAX_NODES][MAX_NODES], int totalNodes, int source, struct Router *router) {
    int visited[MAX_NODES] = {0}; 
    int i, j, minDist, nextNode;

    for (i = 0; i < totalNodes; i++) 
    {
        router->dist[i] = costMatrix[source][i];
        if (costMatrix[source][i] != INF && i != source)
            router->next_hop[i] = i;
        else
            router->next_hop[i] = -1;
    }
    
    visited[source] = 1;

    for (i = 1; i < totalNodes; i++) 
    { 
        minDist = INF;
        nextNode = -1;

        for (j = 0; j < totalNodes; j++) 
        {
            if (!visited[j] && router->dist[j] < minDist) 
            {
                minDist = router->dist[j];
                nextNode = j;
            }
        }

        if (nextNode == -1) break;
        visited[nextNode] = 1;

        for (j = 0; j < totalNodes; j++) 
        {
            if (!visited[j] && router->dist[j] > router->dist[nextNode] + costMatrix[nextNode][j]) 
            {
                router->dist[j] = router->dist[nextNode] + costMatrix[nextNode][j];
                router->next_hop[j] = router->next_hop[nextNode];
            }
        }
    }
}

int main() 
{
    int totalNodes, i, j;
    int costMatrix[MAX_NODES][MAX_NODES] = {0};
    struct Router routers[MAX_NODES];

    printf("Enter the number of nodes: ");
    scanf("%d", &totalNodes);

    for (i = 0; i < totalNodes; i++) {
        for (j = 0; j < totalNodes; j++) {
            if(!costMatrix[i][j] && i != j)
            {
                printf("Enter the direct cost from node %d to node %d (9999 if indirect): ", i, j);
                scanf("%d", &costMatrix[i][j]);
                costMatrix[j][i] = costMatrix[i][j];
            }
        }
    }

    for (i = 0; i < totalNodes; i++) 
    {
        calculateShortestPaths(costMatrix, totalNodes, i, &routers[i]);
    }

    for (i = 0; i < totalNodes; i++) 
    {
        printf("\nRouting Table for Node %d:\n", i);
        printf("Destination\tCost\tNext Hop\n");
        for (j = 0; j < totalNodes; j++) 
        {
            printf("%d\t\t", j);
            if (routers[i].dist[j] == INF) 
            {
                printf("INF\t");
            } 
            else 
            {
                printf("%d\t", routers[i].dist[j]);
            }
            if (routers[i].next_hop[j] == -1) 
            {
                printf("-\n");
            } else 
            {
                printf("%d\n", routers[i].next_hop[j]);
            }
        }
    }

    return 0;
}
