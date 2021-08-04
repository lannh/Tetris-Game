#ifndef ZSHAPE_H
#define ZSHAPE_H
#include "Tetromino.h"

class ZShape : public Tetromino
{
public:
    ZShape();
    ZShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // ZSHAPE_H
