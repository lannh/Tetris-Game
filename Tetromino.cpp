#include "Tetromino.h"
#include <string>
#include <vector>
#include <QDebug>
#include <iostream>

using namespace std;

Tetromino::Tetromino()
{
    row = col = 0;
    angle = 0;
}

Tetromino::Tetromino(int iniRow, int iniCol,int iniAngle)
{
    row = iniRow;
    col = iniCol;
    angle = iniAngle;
}

void Tetromino::move(string direction)
{
    if(direction=="left")
        --col;
    else ++col;
}

void Tetromino::fall()
{
    row+=1;
}

void Tetromino::rotate()
{
    if(angle<3)
        ++angle;
    else angle = 0;
}

vector<vector<int>> Tetromino::getShape() const
{
    return shapes[angle];
}

int Tetromino::getWidth() const
{
    return shapes[angle][0].size();
}

int Tetromino::getHeight() const
{
    return shapes[angle].size();
}



