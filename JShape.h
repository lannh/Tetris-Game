#ifndef JSHAPE_H
#define JSHAPE_H
#include "Tetromino.h"

class JShape : public Tetromino
{
public:
    JShape();
    JShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // JSHAPE_H
