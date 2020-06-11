//
// Created by aluis on 06/05/2020.
//

#ifndef UNTITLED10_RULES_H
#define UNTITLED10_RULES_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Rules {
    bool flag= false, flag_intersection=false, flag_limits= false, flag_sides = false, intersection_char = false;
    bool intersection = false;
    bool the_end = false;
    bool play_again = false;
    bool no_intersect = false;

    string random_dic;

    char b_word;

    int lines, columns;
    int counter = 0;
    int keep_idx;

    vector<vector<char>> actual_board;


public:
    Rules();
    Rules(int line, int columns);
    bool verifyIntersection(char board_word, char ch_word,int idx);
    bool verifySide(int index_l, int index_c, int index, char direction, int word_size);
    bool verifyLimits(int index_l, int index_c);
    bool forceIntersection();
    bool dontIntersect(bool choose_inetrsection);
    bool verifyChosenWord( int pos_x, int pos_y, char dir, string word );
    bool verifyRules();
    bool  verifyWordsList();
    bool finishBoard();
    void flagEnd( bool e );
    bool playAgain();
    bool changeFlag(bool v_flag);
    void flagAgain(bool a);
    void changeIntersection(bool c_intersection);
    void currentBoard(vector<vector<char>> board);
    void currentDic(string dic);
};


#endif //UNTITLED10_RULES_H
