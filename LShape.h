#ifndef LSHAPE_H
#define LSHAPE_H
#include "Tetromino.h"


class LShape : public Tetromino
{
public:
    LShape();
    LShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // LSHAPE_H
