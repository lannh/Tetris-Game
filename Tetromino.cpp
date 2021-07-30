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

Tetromino::Tetromino(int iniRow, int iniCol, char name,int iniAngle)
{
    row = iniRow;
    col = iniCol;
    nameOfShape = name;
    angle = iniAngle;

    switch(nameOfShape)
    {
        case 'L': iniLShapes();
                  color[0] = 255;
                  color[1] = 87;
                  color[2] = 34;
                  break;
        case 'J': iniJShapes();
                  color[0] = 63;
                  color[1] = 81;
                  color[2] = 181;
                  break;
        case 'O': iniOShapes();
                  color[0] = 255;
                  color[1] = 235;
                  color[2] = 59;
                  break;
        case 'T': iniTShapes();
                  color[0] = 156;
                  color[1] = 39;
                  color[2] = 176;
                  break;
        case 'S': iniSShapes();
                  color[0] = 76;
                  color[1] = 175;
                  color[2] = 80;
                  break;
        case 'Z': iniZShapes();
                  color[0] = 183;
                  color[1] = 28;
                  color[2] = 28;
                  break;
        case 'I': iniIShapes();
                  color[0] = 0;
                  color[1] = 188;
                  color[2] = 212;
                  break;
    };
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
    //qDebug()<<row;
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

void Tetromino::iniLShapes()
{
    color[0] = 255;
    color[1] = 87;
    color[2] = 34;

    shapes =
      {{{1, 0},
        {1, 0},
        {1, 1}},

       {{1, 1, 1},
        {1, 0, 0}},

       {{1, 1},
        {0, 1},
        {0, 1}},

       {{0, 0, 1},
        {1, 1, 1}}};
}

void Tetromino::iniJShapes()
{
    color[0] = 63;
    color[1] = 81;
    color[2] = 181;

    shapes =
      {{{0, 2},
        {0, 2},
        {2, 2}},

       {{2, 0, 0},
        {2, 2, 2}},

       {{2, 2},
        {2, 0},
        {2, 0}},

       {{2, 2, 2},
        {0, 0, 2}}};
}

void Tetromino::iniOShapes()
{
    color[0] = 255;
    color[1] = 235;
    color[2] = 59;

    shapes =
      {{{3, 3},
        {3, 3}},

       {{3, 3},
        {3, 3}},

       {{3, 3},
        {3, 3}},

       {{3, 3},
        {3, 3}}};
}

void Tetromino::iniTShapes()
{
    color[0] = 156;
    color[1] = 39;
    color[2] = 176;

    shapes =
      {{{0, 4, 0},
        {4, 4, 4}},

       {{4, 0},
        {4, 4},
        {4, 0}},

       {{4, 4, 4},
        {0, 4, 0}},

       {{0, 4},
        {4, 4},
        {0, 4}}};
}

void Tetromino::iniSShapes()
{
    color[0] = 76;
    color[1] = 175;
    color[2] = 80;

    shapes =
      {{{0, 5, 5},
        {5, 5, 0}},

       {{5, 0},
        {5, 5},
        {0, 5}},

       {{0, 5, 5},
        {5, 5, 0}},

       {{5, 0},
        {5, 5},
        {0, 5}}};
}

void Tetromino::iniZShapes()
{
    color[0] = 183;
    color[1] = 28;
    color[2] = 28;

    shapes =
      {{{6, 6, 0},
        {0, 6, 6}},

       {{0, 6},
        {6, 6},
        {6, 0}},

       {{6, 6, 0},
        {0, 6, 6}},

       {{0, 6},
        {6, 6},
        {6, 0}}};
}

void Tetromino::iniIShapes()
{
    color[0] = 0;
    color[1] = 188;
    color[2] = 212;

    shapes =
      {{{7},
        {7},
        {7},
        {7}},

       {{7, 7, 7, 7}},

       {{7},
        {7},
        {7},
        {7}},

       {{7, 7, 7, 7}}};
}

Tetromino& Tetromino::operator=(const Tetromino& otherTetro)
{
    if(this == & otherTetro)
        cerr<<"Assigning to self";
    else
    {
        row = otherTetro.row;
        col = otherTetro.col;
        angle = otherTetro.angle;

        if(nameOfShape != otherTetro.nameOfShape)
        {
           nameOfShape = otherTetro.nameOfShape;
           shapes.clear();
           shapes = otherTetro.shapes;
        }

        for(int i=0; i<3; ++i)
            color[i] = otherTetro.color[i];
    }
    return *this;
}
