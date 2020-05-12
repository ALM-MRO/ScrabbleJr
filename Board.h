//
// Created by aluis on 04/05/2020.
//


#ifndef UNTITLED10_BOARD_H
#define UNTITLED10_BOARD_H
#include <string>
#include <iostream>
#include <vector>
#include "Rules.h"
#include "Words.h"

using namespace std;

class Board {
public:
    vector <vector <char>> board;

    int lines, columns;
    int l, c;
    string chosen_word = "";
    string temporary_words[10];
    string user_word;

    int chosen_index;
    int random_number;
    int count_letter;

    void printBoard();
    void resetBoard(int lines, int columns);
    void readFile();
    void listOfWords();
    void choosingInfo();
    void choosingIndex();
    void changeBoard();
    void boardSize();
    bool findWordDic(string u_word);

    vector<string> dictionary;

    int size,  idx;
    char pos_x, pos_y, dir, last_dir;

    Rules validation ;
    Words file_word;
    Board(int lines, int columns);
    Board();
};



#endif //UNTITLED10_BOARD_H
