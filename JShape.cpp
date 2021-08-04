#include "JShape.h"

JShape::JShape()
{

}

JShape::JShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    color[0] = 63;
    color[1] = 81;
    color[2] = 181;
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
