#ifndef OSHAPE_H
#define OSHAPE_H
#include "Tetromino.h"

class OShape : public Tetromino
{
public:
    OShape();
    OShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // OSHAPE_H
