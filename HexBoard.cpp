#include "HexBoard.h"

HexBoard::HexBoard(int size) : size{size} {
        this->board = vector<vector<char>>(size, vector <char> (size, EMPTY)); // a size * size hex board
        this->player = BLACK; //default first player
        this->blackLink.initialize(size, 1);
        this->whiteLink.initialize(size, 2);
}

HexBoard& HexBoard::operator=(const HexBoard &other) { // overloading operator =
    for(int i = 0; i < this->size; ++i) {
        for(int j = 0; j < this->size; ++j) {
            this->board.at(i).at(j) = other.board.at(i).at(j);
        }
    }
    this->player = other.player;
    this->blackLink = other.blackLink;
    this->whiteLink = other.whiteLink;
    return *this;
}

void HexBoard::printBoard() const {
    vector <char> letter; 

    //print "A, B, C, ..."
    for(int i = 0; i < size; i++) {    
        letter.push_back(static_cast<char> (i + 65));
        cout << " " << letter.at(i);
    }
    cout << endl;

    //print board
    for(int i = 0; i < this->size; ++i) {
        for(int k = 0; k < i; k++) {
            cout << " ";
        }
        cout << letter.at(i) << " ";
        for(int j = 0; j < this->size; ++j){
        cout << this->board.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

void HexBoard::move(char curPlayer) {
    char moveOne, moveTwo;
    cout << "Please enter your move..." << endl;

    while(1) {
    cin >> moveOne >> moveTwo;
    int move1 = moveOne - 'A';
    int move2 = moveTwo - 'A';
        if (validMove(moveOne, moveTwo)) {
            this->board.at(move1).at(move2) = curPlayer;
            Pos curMove(move1 + 1, move2 + 1);
            if(curPlayer == WHITE) {
                this->whiteLink.addMove(curMove);
            } else if(curPlayer == BLACK) {
                this->blackLink.addMove(curMove);
            }
            break;
        } else {
            cout << "Your move is invalid. Please enter your move again..." << endl;
            this->printBoard();
        }
    }
    
    changePlayer(curPlayer);
}

bool HexBoard::validMove(char moveOne, char moveTwo) const {
    int move1, move2;
    move1 = moveOne - 'A';
    move2 = moveTwo - 'A';

    if(move1 >= size || move2 >= size || move1 < 0 || move2 < 0) {
        return false;
    } else if(this->board.at(move1).at(move2) == EMPTY) {
        return true;
    }
    return false;
}

void HexBoard::changePlayer(char curPlayer) {
    if(curPlayer == BLACK) {
        this->player = WHITE;
    } else if(curPlayer == WHITE) {
        this->player = BLACK;
    }
}

Pos HexBoard::computerRandomMove(char curPlayer) {
    int move1, move2;
    char moveOne, moveTwo;
    int seed = 0;

    while(1) {
        
        move1 = rand() % size;
        move2 = rand() % size;
        moveOne = static_cast<char>('A' + move1);
        moveTwo = static_cast<char>('A' + move2);
        if(validMove(moveOne, moveTwo)) {
            Pos computerMove(move1 + 1, move2 + 1);
            this->board.at(move1).at(move2) = curPlayer;
            return computerMove;
            break;
        }
    }  
}

int HexBoard::computerRandom() {
    //Black goes first
    // Linkage blackStatus(this->size, 1);
    // Linkage whiteStatus(this->size, 2);
    this->player = BLACK;

    while(1) {
        Pos curMove = computerRandomMove(this->player);
        //cout << "Now " << this->player << " make this move: " << curMove.getX() << ", " << curMove.getY() << endl;
        if(this->player == BLACK) {
            this->blackLink.addMove(curMove);
        } else if(this->player == WHITE) {
            this->whiteLink.addMove(curMove);
        }

        if(this->blackLink.win(1)) {
            cout << "Congratulations! Black player has won!" << endl;
            //break;
            return 1;
        } else if(this->whiteLink.win(2)) {
            cout << "Congratulations! White player has won!" << endl;
            //break;
            return 0;
        }
        this->changePlayer(this->player);
    }
}

// void HexBoard::initBoard(int num) { // initialize checkBoard
//     if (num == 1) {
//         this->board = this->board = vector<vector<char>>(size, vector <char> (size, EMPTY));
//     } else if (num == 2) {
//         this->checkBoard = vector<vector<int>> (size, vector<int> (size, 0));
//     } else {
//         cout << "Your entered incorrect board number!" << endl;
//     }
// }

vector<vector<int>> HexBoard::plausibleMove(vector<vector<char>> board) {
    vector<vector<int>> checkBoard = vector<vector<int>> (this->size, vector<int> (this->size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board.at(i).at(j) != EMPTY) {
                for (int k = 0; k < 6; ++k) {
                    int cor1 = i + dir.at(k).at(0), cor2 = j + dir.at(k).at(1);
                    char corX = (char)cor1 + 65, corY = (char)cor2 + 65;
                    //cout << corX << ", " << corY << " " << cor1 << ", " << cor2 << endl;
                    if (this->validMove(corX, corY)) {
                        //cout << "valid move: " << corX << ", " << corY << endl;
                        checkBoard.at(cor1).at(cor2) = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (checkBoard.at(i).at(j) == 1) {
                for (int k = 0; k < 6; ++k) {
                    int cor1 = i + dir.at(k).at(0), cor2 = j + dir.at(k).at(1);
                    char corX = (char)cor1 + 65, corY = (char)cor2 + 65;
                    if (this->validMove(corX, corY) && checkBoard.at(cor1).at(cor2) != 1) {
                        checkBoard.at(cor1).at(cor2) = 2;
                    }
                }
            }
        }
    }

    return checkBoard;
}

void HexBoard::addMove(Pos pos) {
    this->board.at(pos.getX()-1).at(pos.getY()-1) = this->player;
    if(this->player == WHITE) {
        this->whiteLink.addMove(pos);
    } else if(this->player == BLACK) {
        this->blackLink.addMove(pos);
    }
    this->changePlayer(this->player);
}

int HexBoard::getSize() const {
    return this->size;
}

vector<vector<char>> HexBoard::getBoard() const {
    vector<vector<char>> returnBoard = vector<vector<char>> (this->size, vector<char> (this->size, '-'));
    for(int i = 0; i < this->size; ++i) {
        for(int j = 0; j < this->size; ++j) {
            returnBoard.at(i).at(j) = this->board.at(i).at(j);
        }
    }

    return returnBoard;
}

Pos HexBoard::AIMove() {  // there must be at one move on the board. 1->black, 2->white
    Pos bestMove(0, 0);
    int minEval = 999; // record the evaluation point the current best move
    int maxEval = -999;
    int curPoint = 0;
    vector<vector<int>> checkBoard = this->plausibleMove(this->board); // this board contains all the next possible moves

    for(int i = 0; i < this->size; ++i) {
        for(int j = 0; j < this->size; ++j) {
            if(checkBoard.at(i).at(j) != 0) { // we need to check this move
                cout << "I am checking " << i + 1 << ", " << j + 1 << endl;
                Pos nextMove(i + 1, j + 1);
                HexBoard NextMoveBoard{this->size};
                NextMoveBoard = *this;
                NextMoveBoard.addMove(nextMove);
                //cout << "AAAAAAAAAAAAAA CURRENT PLAYER IS: " << NextMoveBoard.getPlayer() << endl;
                if(NextMoveBoard.getPlayer() == WHITE) { // Black is maximizing player
                    curPoint = minimax(NextMoveBoard, 3, false);
                    // cout << "curPoint: " << curPoint << endl;
                    // cout << "maxEval: " << maxEval << endl;
                    if(maxEval < curPoint) {
                        maxEval = curPoint;
                        bestMove.setX(i + 1);
                        bestMove.setY(j + 1);
                        //cout << "Current best move is: " << bestMove.getX() << ", " << bestMove.getY() << endl;
                    }
                } else if(NextMoveBoard.getPlayer() == BLACK) { // White is minimizing player
                    curPoint = minimax(NextMoveBoard, 3, true);
                    //cout << "curPoint: " << curPoint << endl;
                    //cout << "minEval: " << minEval << endl;
                    if(minEval > curPoint) {
                        minEval = curPoint;
                        bestMove.setX(i + 1);
                        bestMove.setY(j + 1);
                        //cout << "Current best move is: " << bestMove.getX() << ", " << bestMove.getY() << endl;
                    }
                }
            }
        }
    }
    //cout << "Now i will return a move" << endl;
    return bestMove;
}

char HexBoard::getPlayer() const {
    return this->player;
}

int HexBoard::minimax(HexBoard curBoard, int depth, bool maximizingPlayer) {
    //cout << "I am at depth: " << depth << endl;
    vector <char> letter; 

    //print "A, B, C, ..."
    // for(int i = 0; i < size; i++) {    
    //     letter.push_back(static_cast<char> (i + 65));
    //     cout << " " << letter.at(i);
    // }
    // cout << endl;

    // //print board
    // for(int i = 0; i < this->size; ++i) {
    //     for(int k = 0; k < i; k++) {
    //         cout << " ";
    //     }
    //     cout << letter.at(i) << " ";
    //     for(int j = 0; j < this->size; ++j){
    //     cout << curBoard.getBoard().at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }

    curBoard.blackLink.setUnionBoard();
    curBoard.whiteLink.setUnionBoard();

    if(depth == 0 || curBoard.blackLink.win(1) || curBoard.whiteLink.win(2)) {
        // cout << "The current static evaluation of the board is: " << curBoard.blackLink.longestPath(1) + curBoard.whiteLink.longestPath(2) << endl;
        return curBoard.blackLink.longestPath(1) + curBoard.whiteLink.longestPath(2); // static evaluation of the board. BlackLength > 0, WhiteLength < 0
                                                                                      // black will choose max, and white will choose min
    }

    vector<vector<int>> checkBoard = curBoard.plausibleMove(curBoard.getBoard());
    int maxEval = -999;
    int minEval = 999;
    int eval = 0;

    for(int i = 0; i < curBoard.getSize(); ++i) {
        for(int j = 0; j < curBoard.getSize(); ++j) {
            if(checkBoard.at(i).at(j) != 0) {
                Pos nextMove(i + 1, j + 1);
                HexBoard NextMoveBoard{this->size};
                NextMoveBoard = curBoard;
                if(maximizingPlayer) { // the last player is BLACK
                    NextMoveBoard.addMove(nextMove);
                    eval = this->minimax(NextMoveBoard, depth - 1, false);
                    maxEval = max(maxEval, eval);
                } else { // WHITE
                    NextMoveBoard.addMove(nextMove);
                    eval = this->minimax(NextMoveBoard, depth - 1, true);
                    minEval = min(minEval, eval);
                }
            }
        }
    }

    if(maximizingPlayer) {
        return maxEval;
    } else {
        return minEval;
    }
}