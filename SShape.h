#ifndef SSHAPE_H
#define SSHAPE_H
#include "Tetromino.h"

class SShape : public Tetromino
{
public:
    SShape();
    SShape(int, int, int iniAngle = 0);
    SShape(const SShape&);

    void iniShapes();
    void setColor();
    SShape* clone();
};

#endif // SSHAPE_H
