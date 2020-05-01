#include "Word.h"

Word:: Word(string word, char line, char column, char direction){
    this -> line = line;
    this -> column = column;
    this -> word = word;
    this -> direction = direction;
};
