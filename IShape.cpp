#include "IShape.h"

IShape::IShape()
{

}

IShape::IShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    color[0] = 0;
    color[1] = 188;
    color[2] = 212;
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
