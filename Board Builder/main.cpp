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

using namespace std;

int main() {
    //_sleep(200000);
    srand(time(0));
    cout << "WELCOME TO SCRABBLE JUNIOR BODY BUILDER" << endl ;

    Board board = Board();

    while(!board.validation.finishBoard()) {

        board.listOfWords();
        board.validation.changeFlag(false);

        while(!board.validation.verifyRules()){
            board.choosingIndex();
            if (board.validation.finishBoard()) break;
            board.choosingInfo();
            board.changeBoard();
        }

        if(!board.validation.finishBoard())
            board.printBoard();

        if (board.validation.playAgain()){
            board.validation.flagEnd(false);
            board.file_word.createFile();
            board.boardSize();
            board.printBoard();
        }
    }
    return 0;
}
