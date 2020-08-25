#include "Linkage.h"

//player 1 wants to link left to right
//player 2 wants to link top to bottom

Linkage& Linkage::operator=(const Linkage& other) {
    for(int i = 0; i < this->size; ++i) {
        for(int j = 0; j < this->size; ++j) {
            this->root.at(i).at(j) = other.root.at(i).at(j);
        }
    }
    return *this;
}

void Linkage::initialize(int size, int player) {
    this->size = size;
    this->player = player;
    for(int i = 0; i < size; ++i) {  // initialize the root board
        root.emplace_back(vector<Pos>());
        for(int j = 0; j < size; ++j) {
            Pos k{0, 0};
            root.at(i).emplace_back(k);
        }
    }
    this->unionBoard = vector<vector<int>> (size, vector<int> (size, 0));
}

Pos& Linkage:: findRoot(Pos &pos) const { // can't put (0, 0) in
    Pos father = this->root.at(pos.getX()-1).at(pos.getY()-1);
    if (pos == father) {
        return pos;
    } else {
        return findRoot(father);
    }
}

 bool Linkage:: win(int player) {
    Pos noPiece(0, 0);
    if(player == 1) {  // check if left to right is linked->black
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if(this->root.at(i).at(0) != noPiece && this->root.at(j).at(this->size-1) != noPiece) {  //check if there is a piece at this position
                    Pos posA(i + 1, 1), posB(j + 1, this->size);
                    Pos posC = this->findRoot(posA), posD = this->findRoot(posB);
                    if(posC == posD) { //check if they have the same root
                        return true;
                    }
                }
            }
        }
        return false;
    } else if(player == 2) {  // check if top to bottom is linked->white
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if(this->root.at(0).at(i) != noPiece && this->root.at(this->size-1).at(j) != noPiece) {
                    Pos posA(1, i + 1), posB(this->size, j + 1);
                    Pos posC = this->findRoot(posA), posD = this->findRoot(posB);
                    if(posC == posD) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Linkage::unite(Pos &posA, Pos &posB) {
    Pos fatherA = findRoot(posA);
    Pos fatherB = findRoot(posB);

    if(posA == fatherA && posB == fatherB) { // a and b are both root, then we let a be b's root
        this->root.at(fatherB.getX()-1).at(fatherB.getY()-1) = posA;
    } else if(posA == fatherA) { // find b's root and unite with a
        unite(posA, fatherB); 
    } else {
        unite(fatherA, fatherB); // unite the root of b into the root of a
    }
}

void Linkage::print(int num) const {
    if(num == 1) {
        for(auto i: this->root) {
            for(auto j: i) {
                cout << "[" << j.getX() << " ," << j.getY() << "] ";
            }
            cout << endl;
        }
    } else if(num == 2) {
        for(auto i: this->unionBoard) {
            for(auto j: i) {
                cout << "[" << j << "]";
            }
            cout << endl;
        }
    } else {
        cout << "You entered the wrong number!" << endl;
    }
}

void Linkage::addMove(Pos move) {
    Pos noPiece(0, 0);
    this->root.at(move.getX()-1).at(move.getY()-1) = move; //place the piece on linkage board. The move must be valid, since it is checked
    
    for(int i = 0; i < 6; ++i) {
        Pos neighbor(move.getX() + dir.at(i).at(0), move.getY() + dir.at(i).at(1));
        if(neighbor.validPos(this->size)) { // check if this is a valid position on board
            if(this->root.at(neighbor.getX()-1).at(neighbor.getY()-1) != noPiece) { // check if there is a piece in the neighbor
                this->unite(this->root.at(move.getX()-1).at(move.getY()-1), this->root.at(neighbor.getX()-1).at(neighbor.getY()-1));
            }
        }
    }
}

int Linkage::searchVector(vector<Pos> fathers, Pos pos) const {
    int size = fathers.size();
    for(int i = 1; i < size; ++i) {
        if(fathers.at(i) == pos) {
            return i;
        }
    }
    return 0;
}

void Linkage::setUnionBoard() {
    this->unionBoard = vector<vector<int>> (size, vector<int> (size, 0)); // initialize the board
    Pos invalidZero(0, 0);
    this->fathers.push_back(invalidZero); //fill in the 0th member

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(this->root.at(i).at(j) != invalidZero) {
                Pos cur(i + 1, j + 1);
                Pos curFather = this->findRoot(cur);
                if(this->searchVector(this->fathers, curFather) == 0) { // first occurence of the father
                    this->fathers.push_back(curFather); // add curFather to fathers
                    this->unionBoard.at(i).at(j) = this->searchVector(this->fathers, curFather); 
                } else { // curFather already exists
                    this->unionBoard.at(i).at(j) = this->searchVector(this->fathers, curFather);
                }
            }
        }
    }
}

int Linkage::longestPath(int curPlayer) const {
    int groupNum = this->fathers.size();
    int maxLen = 0;

    for (int i = 1; i < groupNum; ++i) {
        int len = 0;
        for (int k = 0; k < this->size; ++k) {
            for (int j = 0; j < this->size; ++j) {
                if (curPlayer == 1) { // black->check left to right
                    if (this->unionBoard.at(j).at(k) == i) {
                        len++;
                        break;
                    }
                } else if (curPlayer == 2) { // white->check up to bottom
                    if (this->unionBoard.at(k).at(j) == i) {
                        len--;
                        break;
                    }
                } else {
                    cout << "You entered the wrong number for longestPath()!" << endl;
                }
            }
        }
        if(curPlayer == 1) { //black
            maxLen = max(len, maxLen);
        } else { //white
            maxLen = min(len, maxLen);
        } 
    }
    return maxLen;
}



