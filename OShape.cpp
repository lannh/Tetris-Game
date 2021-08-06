#include "OShape.h"

OShape::OShape()
{

}

OShape::OShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    setColor();
    iniShapes();
}

OShape::OShape(const OShape& otherShape)
        :Tetromino(otherShape.row, otherShape.col, otherShape.angle)
{
    setColor();
    iniShapes();
}

void OShape::iniShapes()
{
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

void OShape::setColor()
{
    color[0] = 255;
    color[1] = 235;
    color[2] = 59;
}

OShape* OShape::clone()
{
    return new OShape(*this);
}
