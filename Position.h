#ifndef POSITION_H
#define POSITION_H

#include<iostream>
using namespace std;

class Pos{ // represents a position on the board
    int x, y; // x > 0, y > 0

    public:
    Pos(int a, int b) : x(a), y(b) {}
    bool operator==(const Pos& other) const;
    bool operator!=(const Pos& other) const;
    Pos &operator=(const Pos &other);
    int getX() const {return this->x;}
    int getY() const {return this->y;}
    void setX(int a) {this->x = a;}
    void setY(int b) {this->y = b;}
    bool validPos(int size) const;
    void print() const;    
};

#endif
