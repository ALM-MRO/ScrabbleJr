//
// Created by marga on 12/05/2020.
//

#ifndef UNTITLED13_LETTER_H
#define UNTITLED13_LETTER_H

#include <vector>
#include "Word.h"


class Letter {
    int line;
    int column;
    char let;
    char word_direction;
    char state;
    bool intersection;
public:
    Letter();
    Letter(int line, int column, char let, char word_direction, char state, bool intersection);

    // getters & setters
    char getLet();
    char getWord_direction();
    char getState();
    void setState(char s);
    bool getIntersection();
    void setIntersection(bool i);


};


#endif //UNTITLED13_LETTER_H
