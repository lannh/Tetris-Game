#include "SShape.h"

SShape::SShape()
{

}

SShape::SShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    setColor();
    iniShapes();
}

SShape::SShape(const SShape& otherShape)
        :Tetromino(otherShape.row, otherShape.col, otherShape.angle)
{
    setColor();
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

void SShape::setColor()
{
    color[0] = 76;
    color[1] = 175;
    color[2] = 80;
}

SShape* SShape::clone()
{
    return new SShape(*this);
}
