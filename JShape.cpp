#include "JShape.h"

JShape::JShape()
{

}

void JShape::iniShapes()
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
