#include "Words.h"
#include "Board.h"
#include <vector>
#include <filesystem>

#include <string>
#include <algorithm>

using namespace std;

Words::Words(){

}

void Words::createFile(){
    string file;
    cout << "Enter the name you want to give your file (example: Board):\n";
    cin >> file;
    string name = file + ".txt";
    out_file.open(name);
}

void Words::sizeBoardFile(int lines, int columns){
    out_file << lines << " x " << columns << endl;
}
void Words::writeInFile(char pos_x, char pos_y, char dir, string word){
    if (dir == 'h') dir = 'H';
    if (dir == 'v') dir = 'V';

    out_file << pos_y << pos_x <<" "<< dir << " "<< word << endl;
}
