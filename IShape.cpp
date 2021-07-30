#include "IShape.h"

IShape::IShape()
{

}

void IShape::iniShapes()
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
