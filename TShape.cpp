#include "TShape.h"

TShape::TShape()
{

}

TShape::TShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    setColor();
    iniShapes();
}

TShape::TShape(const TShape& otherShape)
        :Tetromino(otherShape.row, otherShape.col, otherShape.angle)
{
    setColor();
    iniShapes();
}

void TShape::iniShapes()
{
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

void TShape::setColor()
{
    color[0] = 156;
    color[1] = 39;
    color[2] = 176;
}

TShape* TShape::clone()
{
    return new TShape(*this);
}
