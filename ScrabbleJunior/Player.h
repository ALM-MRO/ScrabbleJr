//
// Created by marga on 06/05/2020.
//

#ifndef UNTITLED13_PLAYER_H
#define UNTITLED13_PLAYER_H
#include <vector>
#include <string>


class Player {
    std::string name;
    int score;
    std::vector <char> letters;
    int color;
public:
    Player();
    Player(std::string name, int score, std::vector<char> letters, int color);

    //getters & setters
    int getScore();
    void setScore(int s);
    std::string getName();
    std::vector <char> getLetters();
    void setLetters(std::vector <char> let);
    int getColor();
};


#endif //UNTITLED13_PLAYER_H
