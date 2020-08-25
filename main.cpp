#include<iostream>
#include<vector>
#include "HexBoard.h"

int main() {
    int size = 0;
    int blackwin = 0;
    int total = 0;
    cout << "What is the board size?" << endl;
    cin >> size;
    
    srand(time(0));

    // for(int i = 0; i < 10; ++i) {
    //     total++;
    //     HexBoard hex{size};
    //     if(hex.computerRandom() == 1) {
    //         blackwin++;
    //     }
    //     hex.printBoard(1);
    //     hex.blackLink.setUnionBoard();
    //     hex.whiteLink.setUnionBoard();
    //     cout << "Longest path for Black: " << hex.blackLink.longestPath(1) << endl;
    //     cout << "Longest path for White: " << hex.whiteLink.longestPath(2) << endl;
    //     cout << "Total: " << total << endl;
    //     cout << "Black win: " << blackwin << endl;
    // }

    HexBoard hex{size};
    while(!(hex.blackLink.win(1) || hex.whiteLink.win(2))) {
        hex.printBoard();
        hex.move(BLACK);
        hex.printBoard();
        Pos com1 = hex.AIMove();
        cout << "Computer's decision is: " << com1.getX() << ", " << com1.getY() << endl;
        hex.addMove(com1);
        hex.printBoard();
    }

    return 0;
}