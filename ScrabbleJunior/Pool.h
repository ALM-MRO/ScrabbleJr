//
// Created by marga on 07/05/2020.
//

#ifndef UNTITLED13_POOL_H
#define UNTITLED13_POOL_H

#include <iostream>
#include <vector>

#include "Word.h"
#include "Board.h"
#include "Letter.h"


class Pool {
    std::vector <char> pl;
public:
    Pool();
    void addLettersToPool(std::vector<std::vector<Letter>> brd);
    std::vector<char> shuffleLetters();

    //getters & setters
    std::vector<char> getPl();
    void setPl(std::vector<char> v);
    char getLet();
};


#endif //UNTITLED13_POOL_H
