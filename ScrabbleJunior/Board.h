//
// Created by marga on 05/05/2020.
//

#ifndef UNTITLED13_BOARD_H
#define UNTITLED13_BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "Word.h"
#include "Pool.h"
#include "Player.h"
#include "Letter.h"


class Board {
    std::string name;
    int lines;
    int columns;
    int players;
    int word_number;
    vector <vector <Letter>> brd_objects;
    vector <Word> words_vec;
public:
    Board(std::string name);
    Board(std::string name, int lines, int columns, int players,
            vector<vector<Letter>> brd_objects, int word_number, vector<Word> words_vec);
    void buildBoard();
    void printBoard(vector <vector<char>> players_options);
    void readBoardFile();
    void insertWord(vector <char> vec, char line, char column, char direction);


    //getters & setters


    int getWord_number();
    vector<vector<Letter>> getBrd_objects();
    void setBrd_objects(vector <vector <Letter>> new_brd);
    vector <Word> getWords_vec();

};


#endif //UNTITLED13_BOARD_H
