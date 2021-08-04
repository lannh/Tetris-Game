#include "TShape.h"

TShape::TShape()
{

}

TShape::TShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    color[0] = 156;
    color[1] = 39;
    color[2] = 176;
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
