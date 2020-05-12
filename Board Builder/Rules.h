//
// Created by aluis on 06/05/2020.
//

#ifndef UNTITLED10_RULES_H
#define UNTITLED10_RULES_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Rules {
    bool flag, flag_intersection, flag_limits, flag_sides, intersection_char;
    bool intersection;
    bool the_end;
    bool play_again;

    string random_dic;
    string word;

    char b_word;

    int lines, columns;
    int counter = 0;

    vector<vector<char>> actual_board;

public:
    Rules();
    Rules(int line, int columns);

    bool verifyIntersection(char board_word, char ch_word);
    bool verifySide(int index_l, int index_c, int index, char direction);
    bool verifyLimits(int index_l, int index_c);
    bool forceIntersection();

    bool verifyRules();
    bool  verifyWords();
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
