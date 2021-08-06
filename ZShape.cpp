#include "ZShape.h"

ZShape::ZShape()
{

}

ZShape::ZShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    setColor();
    iniShapes();
}

ZShape::ZShape(const ZShape& otherShape)
        :Tetromino(otherShape.row, otherShape.col, otherShape.angle)
{
    setColor();
    iniShapes();
}

void ZShape::iniShapes()
{
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

void ZShape::setColor()
{
    color[0] = 183;
    color[1] = 28;
    color[2] = 28;
}

ZShape* ZShape::clone()
{
    return new ZShape(*this);
}
