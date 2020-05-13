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
#include <fstream>
#include <map>


using namespace std;

class Board {
    vector <vector <char>> board;

    int lines, columns;

    string chosen_word = "";
    string temporary_words[10];
    string user_word;
    string file_name;

    int chosen_index;
    int random_number;
    int count_letter;

    vector<string> dictionary;

    int size,  idx;
    char pos_x, pos_y, dir;

    Rules validation ;
    Words file_word;

public:
    void chooseIntersection();
    void readFile();
    void boardSize();
    void printBoard();
    void listOfWords();
    void changeBoard();
    void choosingInfo();
    void choosingIndex();

    bool findWordDic(string u_word);
    void resetBoard(int lines, int columns);

    Rules getValidation();

    Board();
};

#endif //UNTITLED10_BOARD_H
