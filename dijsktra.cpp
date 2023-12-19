#include <stdio.h>
#include <stdlib.h>

int noV = 6;
int counter = 0;
int counter2 = 0 ;
int visited[6] = {0};




struct Node
{
    int data;
    int paid;
    struct Node* next;

};
struct Graph
{
    int noV;
    struct Node** adjLists;
};
struct Graph* createGraph(int noV)
{
    //Give me a pointer to that structure
    struct Graph* newG = (struct Graph*)malloc(sizeof(struct Graph));
    //This Double Pointer is Fuckin Shit
    newG->adjLists = (struct Node**)malloc(noV * sizeof(struct Graph*));
    newG->noV = noV;

    for (int i = 0; i < noV; i++)
    {
        newG->adjLists[i] = NULL;

    }
    return newG;
};

struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
};

void addDirectedEdge(struct Graph* graph,int source, int dest, int paid)
{

    struct Node* x = createNode(dest);
    x->paid = paid;
    x->next = graph->adjLists[source];
    graph->adjLists[source] = x;
    /* UnDirected Graph implementation
    struct Node* y = createNode(source);
    y->next = graph->adjLists[dest];
    graph->adjLists[dest] = y;
     */

}
void addUnDirectedEdge(struct Graph* graph,int source, int dest, int paid)
{

    struct Node* x = createNode(dest);
    x->paid = paid;
    x->next = graph->adjLists[source];
    graph->adjLists[source] = x;
    /* UnDirected Graph implementation*/
    struct Node* y = createNode(source);
    y->paid=paid;
    y->next = graph->adjLists[dest];
    graph->adjLists[dest] = y;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->noV; v++)
    {
        struct Node* temp = graph->adjLists[v];
        printf("Vertex is %d\n: ", v);
        while (temp)
        {
            printf("Links %d\n", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
int i = -1;








void findShortestPath(struct Graph* graph, int source, int dest)
{
    int numVertices = graph->noV;
    int* distance = (int*)malloc(numVertices * sizeof(int));
    int* previous = (int*)malloc(numVertices * sizeof(int));
    int* visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        distance[i] = 10000;  // Initialize distances to infinity
        previous[i] = -1;       // Set previous node to undefined
        visited[i] = 0;         // Mark all nodes as unvisited
    }

    distance[source] = 0;  // Set distance of source node to 0

    while (1)
    {
        int minDistance = 10000;
        int current = -1;

        // Find the unvisited node with the minimum distance
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i] && distance[i] < minDistance)
            {
                minDistance = distance[i];
                current = i;
            }
        }

        if (current == -1)
        {
            break;  // All nodes have been visited
        }

        visited[current] = 1;  // Mark the current node as visited

        struct Node* node = graph->adjLists[current];

        while (node != NULL)
        {
            int neighbor = node->data;
            int weight = node->paid;

            if (!visited[neighbor])
            {
                int newDistance = distance[current] + weight;

                if (newDistance < distance[neighbor])
                {
                    distance[neighbor] = newDistance;
                    previous[neighbor] = current;
                }
            }

            node = node->next;
        }
    }

    // Shortest path length
    printf("Shortest path length: %d\n", distance[dest]);

    // Path
    printf("Path: ");
    int current = dest;
    while (current != -1)
    {
        printf("%d ", current);
        current = previous[current];
    }
    printf("\n");
    //all distances print
    for (int i = 0; i < noV; i++)
    {
        printf ("FROM THE SOURCE %d ot the Destination %d the shortest is %d\n", source, i, distance[i]);
    }
    // Free allocated memory
    free(distance);
    free(previous);
    free(visited);
}

int main()
{



    struct Graph* g = createGraph(noV);



    // addUnDirectedEdge(g, 0, 1, 5);
    // addUnDirectedEdge(g, 1,3,2);
    // addUnDirectedEdge(g, 3, 2, 6);
    // addUnDirectedEdge(g, 0, 2, 8);
    // addUnDirectedEdge(g, 1, 2, 9);
    // findShortestPath(g, 0, 3);
    /*
     addDirectedEdge(g, 0, 3, 10);  //struct Graph* graph,int source, int dest, int paid
      addDirectedEdge(g, 0, 1, 5);
     addDirectedEdge(g, 3, 1, 2);

      addDirectedEdge(g, 3, 1, 3);
     addDirectedEdge(g, 3, 4, 1);

     addDirectedEdge(g, 1 ,2, 2);
     addDirectedEdge(g, 1, 4, 9);

     addDirectedEdge(g, 2, 4, 6);
      addDirectedEdge(g, 2, 0, 7);

     addDirectedEdge(g, 4, 2, 24);

    */

    addDirectedEdge(g, 0, 4, 4);
        addDirectedEdge(g, 4, 0, 4);

    addDirectedEdge(g, 0, 3, 1);
        addDirectedEdge(g, 3, 0, 1);


    addDirectedEdge(g, 0, 1, 2);  //struct Graph* graph,int source, int dest, int paid
    addDirectedEdge(g, 1, 0, 2);  //struct Graph* graph,int source, int dest, int paid



    addDirectedEdge(g, 2, 3, 5);
        addDirectedEdge(g, 3, 2, 5);


    addDirectedEdge(g, 2, 1, 3);
        addDirectedEdge(g, 1, 2, 3);


    addDirectedEdge(g, 2, 5, 8);
        addDirectedEdge(g, 5, 2, 8);


    addDirectedEdge(g, 5, 1, 7);
    addDirectedEdge(g, 1, 5, 7);


    addDirectedEdge(g, 3, 1, 3);
    addDirectedEdge(g, 1, 3, 3);


    addDirectedEdge(g, 4,3, 9);
    addDirectedEdge(g, 3,4, 9);




    findShortestPath(g, 0, 2);  //struct Graph* graph, int source, int dest
    //note that enqueue in BFS mutate the value


    // bfsv2(g, 0);
    //int fa =  detectBiPartite(g, 0);
    // printf("Answer is %d\n", fa);
    //findStrongCKosaraju(g);


    return 0;

}
