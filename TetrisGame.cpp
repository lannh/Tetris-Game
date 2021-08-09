#include <iostream>
#include <math.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <queue>
#include <QIcon>
#include "TetrisGame.h"
#include "IShape.h"
#include "JShape.h"
#include "LShape.h"
#include "OShape.h"
#include "SShape.h"
#include "TShape.h"
#include "ZShape.h"
#include "Timer.h"

using namespace std;

TetrisGame::TetrisGame(QWidget *parent) :
    QWidget(parent)
{
    srand((unsigned int) time (NULL)); //activates the generator
    initialState = true; //if the game is first opened
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

    //set up timer
    timer = new QTimer(this);
    timer->setInterval(800);
}

void TetrisGame::drawBoard()
{
    int blockSize = 24, padding = 4;

    QList<QGraphicsItem*> itemsList = scene->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    //delete entire current board
    while(iter != end)
    { QGraphicsItem* item = (*iter); scene->removeItem(item); iter++; }

    //redraw entire current board
    scene->addRect(padding, padding, blockSize*boardWidth+padding*(boardWidth+1), blockSize*(boardHeight-3)+padding*(boardHeight-3+1));

    for (int i = 3; i < boardHeight; ++i)
        for (int j = 0; j < boardWidth; j++)
            {
                recolorBrush(currentBoard[i][j]);
                scene->addRect(padding*2+j*(blockSize+padding), padding*2+(i-3)*(blockSize+padding), blockSize, blockSize,pen, colorBrush);
            }

    scene->addText(QString::number(score), QFont("Times", 25))->setPos(300,30);

    scene->addRect(298, 130, blockSize*4+padding*3, blockSize*5+padding*3);

    /*needed to check the initial state since
      the nextTetromino variable might have not been initialized yet*/
    if(!initialState)
    {
        //draw nextTetromino
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

Tetromino* TetrisGame::makeRandomTetromino()
{
    int randNum = (rand() % 7);

    Tetromino* current;

    switch (randNum)
    {
          case 0:
            current = new LShape(1, 4, 0);
            break;
          case 1:
            current = new JShape(1, 4, 0);
            break;
          case 2:
            current = new OShape(2, 4, 0);
            break;
          case 3:
            current = new TShape(2, 4, 0);
            break;
          case 4:
            current = new SShape(2, 4, 0);
            break;
          case 5:
            current = new ZShape(2, 4, 0);
            break;
          default:
            current = new IShape(0, 4, 0);
     }
    return current;
}

void TetrisGame::progress()
{
    Tetromino* newTetromino = currentTetromino->clone();
    newTetromino->setRow(currentTetromino->getRow()+1);
    //pretending that the current tetromino can fall into the next row of the board
    //if that fall causes no overlapped, let the current tetromino fall
    if (!bottomOverlapped(*newTetromino) && !landedOverlapped(*newTetromino))
    {
        currentTetromino->fall();
        //in the case that the board has nearly been filled up to the top
        //check if that fall cause gameover state
        if(checkGameOver())
            callGameOver();
    } //if that fall causes overlapped, check if current state is already a gameover state
    else if(checkGameOver())
        callGameOver();
    else //if that fall causes overlapped,
         //this means the current Tetromino reaches its landed state
    {
      mergeCurrentTetromino();
      //check if any row is completely filled with color blocks
      //(color blocks = landed tetrominos)
      //and update the score accordingly
      updateScore();

      delete currentTetromino;
      currentTetromino = nextTetromino;

      if(checkGameOver())
          callGameOver();
      else nextTetromino = makeRandomTetromino();
    }

    delete newTetromino;
    newTetromino = nullptr;
}

//update current board with the current state of the falling tetromino
//and the current landed board
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
                currentBoard[currentTetromino->getRow() + i][currentTetromino->getCol() + j] = shape[i][j];
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
    initialState = false;
    currentTetromino = makeRandomTetromino();
    nextTetromino = makeRandomTetromino();

    connect(timer,SIGNAL(timeout()),this,SLOT(tryMoveDown()));
    timer->start(800);
}

void TetrisGame::setDrawingTools(QGraphicsScene * iniScene, QBrush & iniBrush, QPen & iniPen)
{
    scene = iniScene;
    colorBrush = iniBrush;
    pen = iniPen;
}

//check if a tetromino reaches the bottom of the board
bool TetrisGame::bottomOverlapped(const Tetromino& thisTetromino)
{
    return (thisTetromino.getRow() + thisTetromino.getHeight() > boardHeight);
}

//check if a tetromino reaches the left edge of the board
bool TetrisGame::leftOverlapped(const Tetromino& thisTetromino)
{
    return (thisTetromino.getCol()<0);
}

//check if a tetromino reaches the right edge of the board
bool TetrisGame::rightOverlapped(const Tetromino& thisTetromino)
{
    return (thisTetromino.getCol()+thisTetromino.getWidth() > boardWidth);
}

//check if a tetromino reaches those of landed tetrominos
bool TetrisGame::landedOverlapped(const Tetromino& thisTetromino)
{
    int row = thisTetromino.getRow();
    int col = thisTetromino.getCol();
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

//in the case that the current tetromino reaches its landed state
//merge the current tetromino with the landed board
void TetrisGame::mergeCurrentTetromino()
{
    int row = currentTetromino->getRow();
    int col = currentTetromino->getCol();
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
    Tetromino *tempTetromino = currentTetromino->clone();
    tempTetromino->setCol(currentTetromino->getCol() - 1);

    //pretending that the current tetromino could move left
    //if that left movement causes no overlapped, let it move
    //else does nothing
    if (!leftOverlapped(*tempTetromino) &&
          !landedOverlapped(*tempTetromino))
        {
          currentTetromino->setCol(currentTetromino->getCol()-1);
          updateCurrentBoard();
          drawBoard();
        }

    delete tempTetromino;
    tempTetromino = nullptr;
}

void TetrisGame::tryMoveRight()
{
    Tetromino *tempTetromino = currentTetromino->clone();
    tempTetromino->setCol(currentTetromino->getCol() + 1);

    //pretending that the current tetromino could move right
    //if that right movement causes no overlapped, let it move
    //else does nothing
    if (!rightOverlapped(*tempTetromino) &&
          !landedOverlapped(*tempTetromino))
        {
          currentTetromino->setCol(currentTetromino->getCol()+1);
          updateCurrentBoard();
          drawBoard();
        }

    delete tempTetromino;
    tempTetromino = nullptr;
}

void TetrisGame::tryRotating()
{
    Tetromino *tempTetromino = currentTetromino->clone();
    tempTetromino->setRow(currentTetromino->getRow()+1);
    tempTetromino->rotate();

    //pretending that the current tetromino could move rotate
    //if that rotation causes no overlapped, let it rotate
    //else does nothing
    if (!leftOverlapped(*tempTetromino) &&
        !rightOverlapped(*tempTetromino) &&
        !bottomOverlapped(*tempTetromino) &&
        !landedOverlapped(*tempTetromino))
        {
          currentTetromino->rotate();
          updateCurrentBoard();
          drawBoard();
        }

    delete tempTetromino;
    tempTetromino = nullptr;
}

//set different color for different types of tetrominos
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
    queue<int> q;
    int cntLine = 1; //number of row that is completely filled with color blocks
    int i = 0;

    for(i=boardHeight-1; i>=0; --i)
    {
        int j = 0;
        int cntZero = 0;
        int cntNonZero = 0;
        //count number of white blocks and color blocks in a row
        while(j<boardWidth)
        {
            if(landedBoard[i][j]==0)
                ++cntZero;
            else ++cntNonZero;

            if(cntZero!=0 && cntNonZero!=0)
                break;
            ++j;
         }

         //if a row does not have any color boxes
         //this means it has reached the empty part of the board
         //therefore no need further check
         if(cntZero==boardWidth)
            break;

         //since we only need to consider and delete any row filled with color blocks
         //any row that has both white and color blocks will be pushed into the queue
         if(cntZero!=0 && cntNonZero!=0)
            q.push(i);
         else ++cntLine;
    }

    score+=10*cntLine;

    //to delete all of the rows that are completely filled with color blocks
    //we insert all of the rows (that are placed in the queue earlier) into the landed board
    //starting from the bottom
    i = boardHeight-1;
    while(!q.empty())
    {
        landedBoard[i] = landedBoard[q.front()];
        q.pop();
        --i;
    }

    //after that, we clear out all of the rows
    //above those rows we just inserted
    while(cntLine>0)
    {
        for(int j = 0; j<boardWidth; ++j)
            landedBoard[i][j] = 0;
        --cntLine;
        --i;
    }
}

bool TetrisGame::checkGameOver() const
{
    int h = currentTetromino->getHeight();
    int w = currentTetromino->getWidth();
    int currCol = currentTetromino->getCol();
    int currRow = currentTetromino->getRow();
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
