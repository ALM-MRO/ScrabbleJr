//
// Created by marga on 06/05/2020.
//

#ifndef UNTITLED13_WORD_H
#define UNTITLED13_WORD_H

#include <iostream>
#include <vector>
#include <string>

//#include "Letter.h"


class Letter;

class Word{
    std::vector <Letter*> letters_vec;
    char line, column;
    char direction;
    bool complete;
public:
    Word(std::vector<Letter*> letters_vec, char line, char column, char direction);
    void changeComplete();

    //setters & getters
    bool getComplete();

};



#endif //UNTITLED13_WORD_H
