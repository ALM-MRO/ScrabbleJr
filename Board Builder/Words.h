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
    ofstream out_file;
    string word_info;
    char line, column;
    vector <vector<string>> words_file;
    vector<string> board_info;

public:
    void createFile(string name);
    void writeInFile(char pos_x, char pos_y, char dir, string word);
    void sizeBoardFile(int lines, int columns);


    Words();
};


#endif //UNTITLED10_WORDS_H
