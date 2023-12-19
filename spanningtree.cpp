#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node
{
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph
{
    int numVertices;
    struct Node** adjLists;
};

struct Node* createNode(int v, int weight)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Add edge from src to dest
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (undirected graph)
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void primMST(struct Graph* graph)
{
    int numVertices = graph->numVertices;

    int* parent = (int*)malloc(numVertices * sizeof(int));
    int* key = (int*)malloc(numVertices * sizeof(int));
    int* visited = (int*)malloc(numVertices * sizeof(int));

    for (int v = 0; v < numVertices; v++)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        visited[v] = 0;
    }

    key[0] = 0;

    for (int count = 0; count < numVertices - 1; count++)
    {
        int minKey = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++)
        {
            if (visited[v] == 0 && key[v] < minKey)
            {
                minKey = key[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        visited[u] = 1;

        struct Node* temp = graph->adjLists[u];
        while (temp != NULL)
        {
            int v = temp->vertex;
            int weight = temp->weight;
            if (visited[v] == 0 && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++)
    {
        printf("%d - %d \t%d\n", parent[i], i, key[i]);
    }
}

int main()
{
    int numVertices = 6;
    struct Graph* g = createGraph(numVertices);

    addEdge(g, 0, 4, 4);
    addEdge(g, 0, 3, 1);
    addEdge(g, 0, 1, 2);  //struct Graph* graph,int source, int dest, int paid

    addEdge(g, 2, 3, 5);
    addEdge(g, 2, 1, 3);
    addEdge(g, 2, 5, 8);
    addEdge(g, 5, 1, 7);

    addEdge(g, 3, 1, 3);

    addEdge(g, 4,3, 9);


    primMST(g);

    return 0;
}
