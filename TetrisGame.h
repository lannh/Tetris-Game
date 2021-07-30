#ifndef TETRISGAME_H
#define TETRISGAME_H
#include <vector>
#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QWidget>
#include <QGraphicsItem>
#include <QTimer>
#include "Tetromino.h"
#include "gameoverdialog.h"


class TetrisGame : public QWidget
{
    Q_OBJECT

private:
    QWidget* mainParent;
    int score;
    int boardWidth;
    int boardHeight;
    std::vector<std::vector<int>>currentBoard;
    std::vector<std::vector<int>>landedBoard;
    Tetromino *currentTetromino;
    Tetromino *nextTetromino;
    QTimer *timer;
    int remainingTime;
    QGraphicsScene* scene;
    QBrush colorBrush, whiteBrush;
    QPen pen;

    void recolorBrush(int i);
    void updateScore();
    bool checkGameOver() const;
    void callGameOver();

public:
    TetrisGame(QWidget *parent = nullptr);

    void setDrawingTools(QGraphicsScene*, QBrush&, QPen&);
    void drawBoard();
    void progress();
    void updateCurrentBoard();
    void play();

    void makeRandomTetromino(Tetromino*);

    bool bottomOverlapped(const Tetromino&);
    bool leftOverlapped(const Tetromino&);
    bool rightOverlapped(const Tetromino&);
    bool landedOverlapped(const Tetromino&);
    void mergeCurrentTetromino();

    void tryMoveLeft();
    void tryMoveRight();
    void tryRotating();

    void pauseGame();
    void resumeGame();
    void resetGame();

    void stopTheClock();

    virtual ~TetrisGame()
    {
        delete currentTetromino;
        currentTetromino = nullptr;
        delete nextTetromino;
        nextTetromino = nullptr;

    };

public slots:
    void tryMoveDown();
};

#endif // TETRISGAME_H
