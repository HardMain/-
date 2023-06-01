#pragma once

#include "Libraries.h"

class Graph
{
    int numVertices;
    int size;

    vector<vector<int>> matrix;
    vector<int> existVertex;
    vector<int> visited;
    map<int, int> way;

    vector<Vector2f> button_coords;
public:
    Graph(int vertices);

    void addEdge(int FV, int SV, int weight);
    void addVertex();

    void delEdge(int FV, int SV);
    void delVertex(int vertex);

    void BFS(int vertex);
    void DFS(int vertex);

    int getWeight(int FV, int SV);
    int getSize() { return size; }
    vector<Vector2f> getButtonCoords() { return button_coords; }

    void DKR(int vertex);
    void Salesman(int &sum, vector<vector<int>> temp, String &wayS);

    void printGraph();

    void visualGraph(RenderWindow& w);
    void EventMouseButtonPressed(Vector2f, RenderWindow& w);
};