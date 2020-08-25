#include "Position.h"


bool Pos::operator==(const Pos& other) const { // overloading operator ==
    if(this->x == other.getX() && this->y == other.getY()) {
        return true;
    }
    return false;
}

bool Pos::operator!=(const Pos& other) const {
    if(this->x != other.getX() || this->y != other.getY()) {
        return true;
    }
    return false;
}

Pos& Pos::operator=(const Pos& other) { // overloading operator =
    this->x = other.x;
    this->y = other.y;
    return *this;
}

bool Pos::validPos(int size) const {
    if(this->x < 1 || this->y < 1 || this->x > size || this->y > size) {
        return false;
    }
    return true;
}

void Pos::print() const {
    cout << this->x << ", " << this->y;
}