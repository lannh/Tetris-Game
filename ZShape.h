#ifndef ZSHAPE_H
#define ZSHAPE_H
#include "Tetromino.h"

class ZShape : public Tetromino
{
public:
    ZShape();
    ZShape(int, int, int iniAngle = 0);
    ZShape(const ZShape&);

    void iniShapes();
    void setColor();
    ZShape* clone();
};

#endif // ZSHAPE_H
