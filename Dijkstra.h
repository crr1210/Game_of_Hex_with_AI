#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <vector>
int INF = 999;

class dijkstra {
public:
    Dijkstra(int size, int player);
    
private:
    vector<vector<int>> board;
    int size;
    int player; // 1->Black, 2->White
}

#endif