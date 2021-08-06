#ifndef OSHAPE_H
#define OSHAPE_H
#include "Tetromino.h"

class OShape : public Tetromino
{
public:
    OShape();
    OShape(int, int, int iniAngle = 0);
    OShape(const OShape&);

    void iniShapes();
    void setColor();
    OShape* clone();
};

#endif // OSHAPE_H
