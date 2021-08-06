#include "JShape.h"

JShape::JShape()
{

}

JShape::JShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    setColor();
    iniShapes();
}

JShape::JShape(const JShape& otherShape)
        :Tetromino(otherShape.row, otherShape.col, otherShape.angle)
{
    setColor();
    iniShapes();
}

void JShape::iniShapes()
{
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

void JShape::setColor()
{
    color[0] = 255;
    color[1] = 87;
    color[2] = 34;
}

JShape* JShape::clone()
{
    return new JShape(*this);
}
