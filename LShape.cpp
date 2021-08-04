#include "LShape.h"
#include <vector>
#include <string>
using namespace  std;

LShape::LShape()
{

}

LShape::LShape(int iniRow, int iniCol, int iniAngle)
        :Tetromino(iniRow, iniCol, iniAngle)
{
    /*
    shapes.reserve(4);


    shapes[0].reserve(2);
    for(int i=0; i<2; ++i)
        shapes[0][i].reserve(3);

    shapes[1].reserve(3);
    for(int i=0; i<3; ++i)
        shapes[0][i].reserve(2);

    shapes[2].reserve(2);
    for(int i=0; i<2; ++i)
        shapes[0][i].reserve(3);

    shapes[3].reserve(2);
    for(int i=0; i<2; ++i)
        shapes[0][i].reserve(3);*/

    color[0] = 255;
    color[1] = 87;
    color[2] = 34;
    iniShapes();
}

void LShape::iniShapes()
{
    shapes =
      {{{1, 0},
        {1, 0},
        {1, 1}},

       {{1, 1, 1},
        {1, 0, 0}},

       {{1, 1},
        {0, 1},
        {0, 1}},

       {{0, 0, 1},
        {1, 1, 1}}};
}
