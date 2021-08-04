#ifndef TSHAPE_H
#define TSHAPE_H
#include "Tetromino.h"

class TShape : public Tetromino
{
public:
    TShape();
    TShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // TSHAPE_H
