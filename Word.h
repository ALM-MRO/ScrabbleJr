#ifndef UNTITLED11_WORD_H
#define UNTITLED11_WORD_H
#include<string>
#include<iostream>

using namespace std;

class Word{
public:
    string word;
    char line, column;
    char direction;
    Word(string word, char line, char column, char direction);
};

#endif//UNTITLED11_WORD_H

