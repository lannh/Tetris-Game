#include <iostream>
#include <math.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <queue>
#include <QIcon>
#include "TetrisGame.h"
#include "LShape.h"
#include "Timer.h"

using namespace std;

TetrisGame::TetrisGame(QWidget *parent) :
    QWidget(parent)
{
    mainParent = parent;
    score = 0;
    boardWidth = 10;
    boardHeight = 23;

    currentBoard.resize(boardHeight);
    for(int i=0; i<boardHeight; ++i)
        currentBoard[i].resize(boardWidth);

    landedBoard.resize(boardHeight);
    for(int i=0; i<boardHeight; ++i)
        landedBoard[i].resize(boardWidth);

    currentTetromino = new Tetromino;
    nextTetromino = new Tetromino;

    timer = new QTimer(this);
    timer->setInterval(800);


}

void TetrisGame::drawBoard()
{
    int blockSize = 24, padding = 4;
    //painter.setBrush(Qt::SolidPattern);

    //scene->clear();

    QList<QGraphicsItem*> itemsList = scene->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end)
    { QGraphicsItem* item = (*iter); scene->removeItem(item); iter++; }

    //scene->addRect(100, 0, 60, 70, pen, brush);
    scene->addRect(padding, padding, blockSize*boardWidth+padding*(boardWidth+1), blockSize*(boardHeight-3)+padding*(boardHeight-3+1));

    for (int i = 3; i < boardHeight; ++i)
        for (int j = 0; j < boardWidth; j++)
            {
                recolorBrush(currentBoard[i][j]);
                scene->addRect(padding*2+j*(blockSize+padding), padding*2+(i-3)*(blockSize+padding), blockSize, blockSize,pen, colorBrush);
            }

    //scene->addText("Score:", QFont("Times", 10, QFont::Bold))->setPos(300,10);
    scene->addText(QString::number(score), QFont("Times", 25))->setPos(300,30);

    //scene->addText("Next Tetromino:", QFont("Times", 10, QFont::Bold))->setPos(300,100);
    scene->addRect(298, 130, blockSize*4+padding*3, blockSize*5+padding*3);
    if(!nextTetromino->shapes.empty())
    {
        int hNextTetro = nextTetromino->getHeight();
        int wNextTetro = nextTetromino->getWidth();
        auto shapeNextTetro = nextTetromino->getShape();
        double posx = 293 + blockSize*(4-double(wNextTetro))/2;
        double posy= 205.5 + blockSize*(5-double(hNextTetro))/2;
        for (int i = 0; i < hNextTetro; i++)
            for (int j = 0; j < wNextTetro; j++)
            {
                recolorBrush(shapeNextTetro[i][j]);
                scene->addRect(posx+ padding*2+j*(blockSize+padding), posy + padding*2+(i-3)*(blockSize+padding), blockSize, blockSize,pen, colorBrush);
            }
    }
}

void TetrisGame::makeRandomTetromino(Tetromino* current)
{
    srand((unsigned int) time (NULL)); //activates the generator
    int randNum = (rand() % 7);
    //cout<<r<<endl;
    //const int randNum = floor(r*floor(7));
    current->col = 4;
    current->angle = 0;

    switch (randNum)
    {
          case 0:
            current->nameOfShape = 'L';
            current->iniLShapes();
            current->row = 1;
            break;
          case 1:
            current->nameOfShape = 'J';
            current->iniJShapes();
            current->row = 1;
            break;
          case 2:
            current->nameOfShape = 'O';
            current->iniOShapes();
            current->row = 2;
            break;
          case 3:
            current->nameOfShape = 'T';
            current->iniTShapes();
            current->row = 2;
            break;
          case 4:
            current->nameOfShape = 'S';
            current->iniSShapes();
            current->row = 2;
            break;
          case 5:
            current->nameOfShape = 'Z';
            current->iniZShapes();
            current->row = 2;
            break;
          default:
            current->nameOfShape = 'I';
            current->iniIShapes();
            current->row = 0;
     }
}

void TetrisGame::progress()
{
    Tetromino newTetromino(currentTetromino->row + 1, currentTetromino->col, currentTetromino->nameOfShape, currentTetromino->angle);

    if (!bottomOverlapped(newTetromino) && !landedOverlapped(newTetromino))
    {
        //qDebug()<<timer->interval();
        currentTetromino->fall();

        if(checkGameOver())
            callGameOver();

    }
    else if(checkGameOver())
        callGameOver();
    else
    {
      mergeCurrentTetromino();
      updateScore();
      *currentTetromino = *nextTetromino;
      if(checkGameOver())
          callGameOver();
      else makeRandomTetromino(nextTetromino);
    }
    //currentTetromino.fall();
}

void TetrisGame::updateCurrentBoard()
{

    for (int i = 0; i < boardHeight; ++i)
        for (int j = 0; j < boardWidth; ++j)
            currentBoard[i][j] = landedBoard[i][j];

    int height = currentTetromino->getHeight();
    int width = currentTetromino->getWidth();
    auto shape = currentTetromino->getShape();

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (shape[i][j] > 0)
                currentBoard[currentTetromino->row + i][currentTetromino->col + j] = shape[i][j];
}

void TetrisGame::tryMoveDown()
{
    timer->setInterval(800);
    progress();
    updateCurrentBoard();
    drawBoard();
}

void TetrisGame::play()
{
    makeRandomTetromino(currentTetromino);
    makeRandomTetromino(nextTetromino);
    //qDebug()<<currentTetromino->row;

    connect(timer,SIGNAL(timeout()),this,SLOT(tryMoveDown()));
    timer->start(800);
    //qDebug()<<"playy";

}

void TetrisGame::setDrawingTools(QGraphicsScene * iniScene, QBrush & iniBrush, QPen & iniPen)
{
    scene = iniScene;
    colorBrush = iniBrush;
    pen = iniPen;
}

bool TetrisGame::bottomOverlapped(const Tetromino& thisTetromino)
{
    return (thisTetromino.row + thisTetromino.getHeight() > boardHeight);
}

bool TetrisGame::leftOverlapped(const Tetromino& thisTetromino)
{
    return (thisTetromino.col<0);
}

bool TetrisGame::rightOverlapped(const Tetromino& thisTetromino)
{
    return (thisTetromino.col+thisTetromino.getWidth() > boardWidth);
}

bool TetrisGame::landedOverlapped(const Tetromino& thisTetromino)
{
    int row = thisTetromino.row;
    int col = thisTetromino.col;
    int height = thisTetromino.getHeight();
    int width = thisTetromino.getWidth();
    auto currentShape = thisTetromino.getShape();

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            if (currentShape[i][j] > 0 &&
                landedBoard[row+i][col+j] > 0)
                return true;

    return false;
}
void TetrisGame::mergeCurrentTetromino()
{
    int row = currentTetromino->row;
    int col = currentTetromino->col;
    int height = currentTetromino->getHeight();
    int width = currentTetromino->getWidth();
    auto currentShape = currentTetromino->getShape();

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            if (currentShape[i][j] > 0)
                landedBoard[row + i][col + j] = currentShape[i][j];
}

void TetrisGame::tryMoveLeft()
{
    Tetromino tempTetromino(currentTetromino->row, currentTetromino->col - 1, currentTetromino->nameOfShape, currentTetromino->angle);
    if (!leftOverlapped(tempTetromino) &&
          !landedOverlapped(tempTetromino))
        {
          currentTetromino->col = currentTetromino->col-1;
          updateCurrentBoard();
          drawBoard();
        }
}

void TetrisGame::tryMoveRight()
{
    Tetromino tempTetromino(currentTetromino->row, currentTetromino->col + 1, currentTetromino->nameOfShape, currentTetromino->angle);
    if (!rightOverlapped(tempTetromino) &&
          !landedOverlapped(tempTetromino))
        {
          currentTetromino->col = currentTetromino->col+1;
          updateCurrentBoard();
          drawBoard();
        }
}

void TetrisGame::tryRotating()
{
    Tetromino tempTetromino(currentTetromino->row+1, currentTetromino->col, currentTetromino->nameOfShape, currentTetromino->angle);
    tempTetromino.rotate();

    if (!leftOverlapped(tempTetromino) &&
        !rightOverlapped(tempTetromino) &&
        !bottomOverlapped(tempTetromino) &&
        !landedOverlapped(tempTetromino))
        {
          currentTetromino->rotate();
          updateCurrentBoard();
          drawBoard();
        }
}

void TetrisGame::recolorBrush(int i)
{
    switch(i)
    {
        case 1: colorBrush.setColor(QColor(255,87,34));
                break;
        case 2: colorBrush.setColor(QColor(63,81,181));
                break;
        case 3: colorBrush.setColor(QColor(255,235,59));
                break;
        case 4: colorBrush.setColor(QColor(156,39,176));
                break;
        case 5: colorBrush.setColor(QColor(76,175,80));
                break;
        case 6: colorBrush.setColor(QColor(183,28,28));
                break;
        case 7: colorBrush.setColor(QColor(0,188,212));
                break;
        default:
            colorBrush.setColor(Qt::white);
    }
}

void TetrisGame::updateScore()
{
    int k = -1;
    for (int i = boardHeight-1; i >= 0; --i)
    {
        int j = 0;
        while(j<boardWidth && landedBoard[i][j]!=0)
            ++j;

        if(j==boardWidth)
        {
            k = i;
            break;
        }
    }

    if(k!=-1)
    {
        queue<int> q;
        int cntLine = 1;

        for(int i=k-1; i>=0; --i)
        {
            bool hasZero = false;
            bool hasNonZero = false;
            int j = 0;
            int cntZero = 0;
            while(j<boardWidth)
            {
                if(landedBoard[i][j]==0)
                {
                    hasZero = true;
                    ++cntZero;
                }
                else hasNonZero = true;

                if(hasZero && hasNonZero)
                    break;
                ++j;
            }

            if(cntZero==boardWidth)
                break;

            if(hasZero && hasNonZero)
                q.push(i);
            else ++cntLine;
        }

        score+=10*cntLine;

        int i=k;

        while(!q.empty())
        {
            landedBoard[i] = landedBoard[q.front()];
            q.pop();
            --i;
        }

        while(cntLine>0)
        {
            for(int j = 0; j<boardWidth; ++j)
                landedBoard[i][j] = 0;
            --cntLine;
            --i;
        }
    }
}

bool TetrisGame::checkGameOver() const
{
    int h = currentTetromino->getHeight();
    int w = currentTetromino->getWidth();
    int currCol = currentTetromino->col;
    int currRow = currentTetromino->row;
    auto shape = currentTetromino->getShape();

    for (int j = 0; j < w; j++)
    {
        if(shape[h-1][j]!=0 &&
           currentBoard[currRow+h-1][currCol+j]!=0 &&
           currRow<=3)
            return true;
    }
    return false;
}

void TetrisGame::resetGame()
{
    delete timer;
    timer = new QTimer(this);

    score = 0;
    remainingTime = 0;

    for (int i = 0; i < boardHeight; ++i)
        for (int j = 0; j < boardWidth; j++)
        {
            currentBoard[i][j] = 0;
            landedBoard[i][j] = 0;
        }

    play();
}

void TetrisGame::callGameOver()
{
    timer->stop();
    GameOverDialog gODialog(score);
    gODialog.setModal(true);
    gODialog.exec();

    if(!gODialog.getIsEndGame())
        resetGame();
    else
        mainParent->close();

}

void TetrisGame::pauseGame()
{
    remainingTime = timer->remainingTime();
    timer->stop();
}

void TetrisGame::resumeGame()
{
    timer->start(remainingTime);
}

void TetrisGame::stopTheClock()
{
    timer->stop();
}