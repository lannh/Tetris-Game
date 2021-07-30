#include "SShape.h"

SShape::SShape()
{

}

void SShape::iniShapes()
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
