
#include "Words.h"
#include "Board.h"
#include <vector>
#include <filesystem>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

Words::Words() {

}

void Words::sizeBoardFile(int lines, int columns){
    word_info = to_string(lines) + " x "+ to_string(columns);
    board_info.push_back(word_info);
}

void Words::writeInFile(char pos_x, char pos_y, char dir, string word){
    string direction, x, y;

    direction +=dir;
    for (auto & d: direction) d = toupper(d); // dir uppercase to put in file
    x += pos_x;
    y += pos_y;

    word_info = y + x + " " + direction +" "+ word;
    board_info.push_back(word_info);
    words_file.push_back(board_info);

}

void Words::createFile(string name){
    out_file.open(name+".txt");

    int size = words_file.size();
    for (int i = 0; i < size; i++){
        out_file << board_info[i] << endl;
    }

    out_file.close();
}