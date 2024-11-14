/*
（1）以领接表为存储结构，按照输入数据建立加权图；
（2）从第1个顶点出发(A)，按照深度优先搜索算法输出各顶点数据；
（3）从第1个顶点出发(A)，按照广度优先搜索算法输出各顶点数据；
（4）计算并输出个顶点的度，按顶点存储顺序输出
*/
#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>

#define MAXSIZE 26

using namespace std;

typedef char VertexType;
typedef int WeightType;

struct Edge {
    VertexType v1, v2;
    WeightType weight;
};

struct Graph {
    int numVertices;
    int numEdges;
    VertexType vertices[MAXSIZE];
    WeightType edges[MAXSIZE][MAXSIZE];
};

bool visited[MAXSIZE] = {false};

void initializeGraph(Graph& graph) {
    graph.numVertices = 0;
    graph.numEdges = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        graph.vertices[i] = '\0';
        for (int j = 0; j < MAXSIZE; j++) {
            graph.edges[i][j] = INT_MAX;
        }
    }
}

void addEdge(Graph& graph, Edge edge) {
    int v1 = edge.v1 - 'A';
    int v2 = edge.v2 - 'A';
    graph.vertices[v1] = edge.v1;
    graph.vertices[v2] = edge.v2;
    graph.edges[v1][v2] = edge.weight;
    graph.edges[v2][v1] = edge.weight;
    graph.numVertices++;
}

void DFS(Graph& graph, int vertex) {
    cout << " " << char(vertex + 'A');
    visited[vertex] = true;
    for (int i = 0; i < MAXSIZE; i++) {
        if (graph.edges[vertex][i] != INT_MAX && !visited[i]) {
            DFS(graph, i);
        }
    }
}

void BFS(Graph& graph, int vertex) {
    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << " " << char(current + 'A');
        for (int i = 0; i < MAXSIZE; i++) {
            if (graph.edges[current][i] != INT_MAX && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

void printInOut(Graph& graph) {
    for (int i = 0; i < MAXSIZE; i++) {
        if (graph.vertices[i] != '\0') {
            cout << "\n" << char(i + 'A') << ":";
            int count = 0;
            for (int j = 0; j < MAXSIZE; j++) {
                if (graph.edges[i][j] != INT_MAX) {
                    count++;
                }
            }
            cout << count;
        }
    }
}

int main() {
    Graph graph;
    initializeGraph(graph);

    int numEdges;
    cin >> graph.numVertices >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        Edge edge;
        cin >> edge.v1 >> edge.v2 >> edge.weight;
        addEdge(graph, edge);
    }

    int startVertex = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        if (graph.vertices[i] != '\0') {
            startVertex = i;
            break;
        }
    }

    memset(visited, false, sizeof(visited));
    cout << "DFS:";
    DFS(graph, startVertex);
    cout << "\nBFS:";
    memset(visited, false, sizeof(visited));
    BFS(graph, startVertex);
    printInOut(graph);

    return 0;
}
