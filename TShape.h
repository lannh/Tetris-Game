#ifndef TSHAPE_H
#define TSHAPE_H
#include "Tetromino.h"

class TShape : public Tetromino
{
public:
    TShape();
    TShape(int, int, int iniAngle = 0);
    TShape(const TShape&);

    void iniShapes();
    void setColor();
    TShape* clone();
};

#endif // TSHAPE_H
