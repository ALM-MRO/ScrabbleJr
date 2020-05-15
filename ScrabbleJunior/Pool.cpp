//
// Created by marga on 07/05/2020.
//

#include "Pool.h"


Pool::Pool(){
};

void Pool::addLettersToPool(vector<vector<Letter>> brd_objects){
    for (int i = 0; i < brd_objects.size(); i++)
        for (int k = 0; k < brd_objects[0].size(); k++)
            if (brd_objects[i][k].getLet() != ' ')
                pl.push_back(brd_objects[i][k].getLet());
}

vector<char> Pool::shuffleLetters(){
    vector <char> letters;
    int rand_index;
    while (letters.size() < 7) {
        rand_index = rand() % pl.size();
        letters.push_back(pl[rand_index]);
        pl.erase(pl.begin() + rand_index);
    }
    return letters;
}

vector<char> Pool::getPl(){
    return pl;
}

void Pool::setPl(vector<char> v){
    pl = v;
}

char Pool::getLet(){
    char send;
    int rand_index;
    rand_index = rand() % pl.size();
    send = pl[rand_index];
    pl.erase(pl.begin() + rand_index);
    return send;
}