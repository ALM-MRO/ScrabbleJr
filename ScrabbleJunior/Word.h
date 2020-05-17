//
// Created by marga on 06/05/2020.
//

#ifndef UNTITLED13_WORD_H
#define UNTITLED13_WORD_H

#include <iostream>
#include <vector>
#include <string>

#include "Letter.h"

class Letter;

class Word{
    std::vector <Letter*> letters_vec;
    bool complete;
public:
    Word(std::vector<Letter*> letters_vec);
    void updateComplete();

    //setters & getters
    bool getComplete();

};



#endif //UNTITLED13_WORD_H
