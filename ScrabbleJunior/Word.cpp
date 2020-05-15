//
// Created by marga on 06/05/2020.
//
#include "Word.h"
using namespace std;

Word:: Word(vector<Letter *> letters_vec, char line, char column, char direction){
    this -> line = line;
    this -> column = column;
    this -> letters_vec = letters_vec;
    this -> direction = direction;
    this -> complete;
}

void Word::changeComplete(){
    for (auto & let : letters_vec) {
        if (let -> getState() != 'F') {
            complete = false;
            break;
        }
        complete = true;
    }

}

bool Word::getComplete(){
    return complete;
}

