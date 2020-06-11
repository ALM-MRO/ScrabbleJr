#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include<vector>
#include<stdlib.h>
#include "Words.h"
#include "Board.h"
#include "Clear.h"
#include "Rules.h"
#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    clock_t start = clock();
    srand(clock());
    string file;

    cout << "WELCOME TO SCRABBLE JUNIOR BODY BUILDER" << endl ;

    Board board = Board();

    while( !board.getValidation().finishBoard() ) {

        board.listOfWords();

        while( !board.getValidation().verifyRules() ){
            board.choosingIndex();
            if ( board.getValidation().finishBoard() ) break;
            board.choosingInfo();
            board.changeBoard();
        }

        if( !board.getValidation().finishBoard() )
            board.printBoard();

        if ( board.getValidation().playAgain() ){
            board.getValidation().flagEnd(false);
            board.boardSize();
            board.printBoard();
        }
    }
    return 0;
}
