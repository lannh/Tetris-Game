#ifndef SSHAPE_H
#define SSHAPE_H
#include "Tetromino.h"

class SShape : public Tetromino
{
public:
    SShape();
    SShape(int, int, int iniAngle = 0);

    void iniShapes();
};

#endif // SSHAPE_H
