#include "OShape.h"

OShape::OShape()
{

}

OShape::OShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    color[0] = 255;
    color[1] = 235;
    color[2] = 59;
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
