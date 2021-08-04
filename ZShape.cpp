#include "ZShape.h"

ZShape::ZShape()
{

}

ZShape::ZShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    color[0] = 183;
    color[1] = 28;
    color[2] = 28;
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
