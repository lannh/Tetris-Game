#include "IShape.h"

IShape::IShape()
{

}

IShape::IShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    setColor();
    iniShapes();
}

IShape::IShape(const IShape& otherShape)
        :Tetromino(otherShape.row, otherShape.col, otherShape.angle)
{
    setColor();
    iniShapes();
}

void IShape::iniShapes()
{
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

void IShape::setColor()
{
    color[0] = 0;
    color[1] = 188;
    color[2] = 212;
}

IShape* IShape::clone()
{
    return new IShape(*this);
}
