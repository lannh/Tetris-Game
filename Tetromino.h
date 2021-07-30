#ifndef TETROMINO_H
#define TETROMINO_H
#include <string>
#include <vector>


class Tetromino
{
public:
    Tetromino();
    Tetromino(int, int, char,int iniAngle = 0);
    //Tetromino(const Tetromino&);

    void move(std::string);
    void fall();
    void rotate();

    std::vector<std::vector<int>> getShape() const;
    int getWidth() const;
    int getHeight() const;

    void setRow(int newRow){ row = newRow;};
    void setCol(int newCol){col = newCol;};

    Tetromino& operator=(const Tetromino&);

//private:
    int row, col;
    int angle;
    int color[3];
    char nameOfShape;
    std::vector<std::vector<std::vector<int>>> shapes;

    void iniLShapes();
    void iniJShapes();
    void iniOShapes();
    void iniTShapes();
    void iniSShapes();
    void iniZShapes();
    void iniIShapes();


};

#endif // TETROMINO_H
