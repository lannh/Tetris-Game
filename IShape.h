#ifndef ISHAPE_H
#define ISHAPE_H
#include "Tetromino.h"

class IShape : public Tetromino
{
public:
    IShape();
    IShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // ISHAPE_H
