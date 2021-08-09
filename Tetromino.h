#ifndef TETROMINO_H
#define TETROMINO_H
#include <string>
#include <vector>


class Tetromino
{
public:
    Tetromino();
    Tetromino(int, int,int iniAngle = 0);

    void move(std::string); //moving left, right
    void fall(); //moving down
    void rotate();

    std::vector<std::vector<int>> getShape() const;
    int getWidth() const;
    int getHeight() const;
    int getRow() const { return row; };
    int getCol() const { return col; };

    void setRow(int newRow){ row = newRow;};
    void setCol(int newCol){col = newCol;};
    void setAngle(int newAngle) {angle = newAngle;};

    virtual void iniShapes() = 0;
    virtual void setColor() = 0;
    virtual Tetromino* clone() = 0;

    virtual ~ Tetromino() {};

protected:
    int row, col;
    int angle;
    int color[3];
    char nameOfShape;
    std::vector<std::vector<std::vector<int>>> shapes;

};

#endif // TETROMINO_H
