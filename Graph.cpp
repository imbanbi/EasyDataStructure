#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  


typedef struct Node {
    int vertice;
    struct Node* next;
} Node;


typedef struct Graph {
    Node* adjList[MAX_VERTICES]; // 邻接表
    int numVertices;  
} Graph;

// 初始化图（邻接表）
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

  
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// 添加边到图（无向图）（头插）
void addEdge(Graph* graph, int src, int dest) {
    // src添加到dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertice = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // dest到src,无向图需双向存边
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertice = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// DFS
/*void DFS(Graph* graph, int vertex, int* visited) { // 此处visited为参数是在多次函数调用自身时共享节点状态
    printf("%d ", vertex);
    visited[vertex] = 1;// 标记已访问节点

    // 遍历当前节点的邻接点
    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertice;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}*/

//发现可能存在孤立节点不会被遍历，于是改进了一下
void DFS(Graph* graph, int vertex, int* visited) {
    int adjVertex;
    printf("%d ", vertex);
    visited[vertex] = 1;

    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        adjVertex = temp->vertice;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void DFSFull(Graph* graph) {
    int visited[MAX_VERTICES] = {0};  // 初始化访问数组，所有节点未访问

    // 对每个节点执行 DFS
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited);
        }
    }
}


// BFS
void BFS(Graph* graph, int startVertex, int* visited) {
    //int visited[MAX_VERTICES] = {0};  //标记节点状态
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // 标记起始节点
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];  // 从队列中取出节点
        printf("%d ", currentVertex);

        // 遍历当前节点的邻接点
        Node* temp = graph->adjList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertice;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;  // 将邻接节点加入队列
            }
            temp = temp->next;
        }
    }
}

void BFSFull(Graph* graph) {
    int visited[MAX_VERTICES] = {0};  

    // 对每个节点执行 BFS
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {  // 如果节点没有被访问过
            BFS(graph, i ,visited);   // 从该节点开始执行 BFS
        }
    }
}


// 主程序
int main() {
    int vertices, edges;
    printf("输入顶点数：");
    scanf("%d", &vertices);

    // 创建图
    Graph* graph = createGraph(vertices);

    printf("输入边数：");
    scanf("%d", &edges);

    printf("输入边的两个端点(形如:src dest)\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // DFS 遍历
    printf("DFS结果:\n");
    int visited[MAX_VERTICES] = {0};  // 初始化访问标记
    DFSFull(graph);
    printf("\n");

    // BFS 遍历
    printf("BFS结果:\n");
    BFSFull(graph);
    printf("\n");

    return 0;
}
