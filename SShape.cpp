#include "SShape.h"

SShape::SShape()
{

}

SShape::SShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    color[0] = 76;
    color[1] = 175;
    color[2] = 80;
    iniShapes();
}

void SShape::iniShapes()
{
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
