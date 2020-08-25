#ifndef HEXBOARD_H
#define HEXBOARD_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Linkage.h"
const char EMPTY = '-';
const char BLACK = 'B';
const char WHITE = 'W';
using namespace std;

class HexBoard {
public:
    HexBoard(int size);
    HexBoard& operator=(const HexBoard& other);
    //void initBoard(int num);
    void printBoard() const;
    void move(char player);
    bool validMove(char moveOne, char moveTwo) const;
    void changePlayer(char CurPlayer);
    Pos computerRandomMove(char CurPlayer); 
    int computerRandom();
    vector<vector<int>> plausibleMove(vector<vector<char>> board); // take in a board then returns next plausible moves for AI
    void addMove(Pos pos);
    int getSize() const;
    char getPlayer() const;
    vector<vector<char>> getBoard() const;
    Pos AIMove();
    int minimax(HexBoard curBoard, int depth, bool maximizingPlayer); // black->maximizing, white->minimizing
    Linkage blackLink; //black
    Linkage whiteLink; //whiÍte

private:   
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}};
    const int size;
    vector<vector<char>> board; // 1 represents this board
    char player; // 'B' or 'W'
};

#endif

