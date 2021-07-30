#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include "TetrisGame.h"
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TetrisGame *T;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QPushButton *pauseButton, *resumeButton, *newGameButton;
    QLabel *scoreLabel, *nextTetroLabel;
    bool iniState;
    bool onPlaying;

    bool eventFilter(QObject*, QEvent*);

private slots:
    void pauseGame();
    void resumeGame();
    void newGame();


};
#endif // MAINWINDOW_H
