#include "mainwindow.h"
#include "TetrisGame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.T->updateCurrentBoard();
    w.T->drawBoard();
    //w.T->play();
    //w.T.drawBoard()
    return a.exec();

}
