//
// Created by aluis on 01/05/2020.
//

#ifndef UNTITLED10_WORDS_H
#define UNTITLED10_WORDS_H
#include<string>
#include<iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class Words{
public:
    ofstream out_file;
    char line, column, direction;
    void createFile();
    void writeInFile(char pos_x, char pos_y, char dir, string word);
    void sizeBoardFile(int lines, int columns);
    string word;
    Words(string word, char line, char column, char direction);
    Words();


};


#endif //UNTITLED10_WORDS_H
