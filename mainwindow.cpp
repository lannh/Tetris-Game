#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(420,600);
    setWindowTitle("Tetris Game");

    installEventFilter(this);
    setFocusPolicy(Qt::StrongFocus);

    T = new TetrisGame(this);

    graphicsView = new QGraphicsView(this);
    graphicsView->setGeometry(QRect(0, 0, 420, 600));
    graphicsView->setFocusPolicy(Qt::NoFocus);

    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->show();

    QBrush colorBrush(Qt::black);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    T->setDrawingTools(scene,colorBrush,outlinePen);

    scoreLabel = new QLabel("Score: ",this);
    scoreLabel->setFont(QFont("Times", 10, QFont::Bold));
    scoreLabel->move(300,10);

    nextTetroLabel = new QLabel("Next Tetromino:",this);
    nextTetroLabel->setFont(QFont("Times", 10, QFont::Bold));
    nextTetroLabel->move(300,100);

    pauseButton = new QPushButton(this);
    pauseButton->setObjectName("pauseButton");
    pauseButton->setStyleSheet(
        "   QPushButton#pauseButton {"
        "     border-image:url(E:/personal code projects/untitledtest/button.png); "
        "     color: #eeff93; "
        " }"
        " QPushButton#pauseButton:hover {"
        "     border-image:url(E:/personal code projects/untitledtest/button.png); "
        "     color: #ff9898; "
        " }"
        );
    pauseButton->setMinimumSize(110,50);
    pauseButton->setMaximumSize(110,50);
    pauseButton->setFont(QFont("Times", 10, QFont::Bold));
    pauseButton->setText("Pause Game");
    pauseButton->move(300,340);
    pauseButton->setVisible(true);
    pauseButton->setFocusPolicy(Qt::NoFocus);
    connect(pauseButton, SIGNAL (clicked()), this, SLOT (pauseGame()));

    resumeButton = new QPushButton(this);
    resumeButton->setObjectName("resumeButton");
    resumeButton->setStyleSheet(
        "   QPushButton#resumeButton {"
        "     border-image:url(E:/personal code projects/untitledtest/button.png); "
        "     color: #eeff93; "
        " }"
        " QPushButton#resumeButton:hover {"
        "     border-image:url(E:/personal code projects/untitledtest/button.png); "
        "     color: #ff9898; "
        " }"
        );
    resumeButton->setMinimumSize(110,50);
    resumeButton->setMaximumSize(110,50);
    resumeButton->setFont(QFont("Times", 10, QFont::Bold));
    resumeButton->setText("Resume Game");
    resumeButton->move(300,340);
    resumeButton->setFocusPolicy(Qt::NoFocus);
    resumeButton->setVisible(false);
    connect(resumeButton, SIGNAL (clicked()), this, SLOT (resumeGame()));

    newGameButton = new QPushButton(this);
    newGameButton->setObjectName("newGameButton");
    newGameButton->setStyleSheet(
        "   QPushButton#newGameButton {"
        "     border-image:url(E:/personal code projects/untitledtest/button.png); "
        "     color: #eeff93; "
        " }"
        " QPushButton#newGameButton:hover {"
        "     border-image:url(E:/personal code projects/untitledtest/button.png); "
        "     color: #ff9898; "
        " }"
        );
    newGameButton->setMinimumSize(110,50);
    newGameButton->setMaximumSize(110,50);
    newGameButton->setFont(QFont("Times", 10, QFont::Bold));
    newGameButton->setText("New Game");
    newGameButton->move(300,440);
    newGameButton->setFocusPolicy(Qt::NoFocus);
    connect(newGameButton, SIGNAL (clicked()), this, SLOT (newGame()));

    iniState = true;
    onPlaying = false;
}

bool MainWindow::eventFilter(QObject *target, QEvent * event)
{
    if(event->type()==QEvent::KeyPress && onPlaying)
    {
        QKeyEvent *kEvent = static_cast<QKeyEvent*>(event);

        if(kEvent->key()==Qt::Key_Left)
            T->tryMoveLeft();
        else if(kEvent->key()==Qt::Key_Right)
            T->tryMoveRight();
        else if(kEvent->key()==Qt::Key_Up)
            T->tryRotating();
        else if(kEvent->key()==Qt::Key_Down)
            T->tryMoveDown();

        return QObject::eventFilter(target, event);
    }

    return QObject::eventFilter(target, event);
}

void MainWindow::pauseGame()
{
    if(!iniState)
    {
        onPlaying = false;
        resumeButton->setVisible(true);
        pauseButton->setVisible(false);
        T->pauseGame();
    }
}

void MainWindow::resumeGame()
{
    onPlaying = true;
    resumeButton->setVisible(false);
    pauseButton->setVisible(true);
    T->resumeGame();
}

void MainWindow::newGame()
{
    resumeButton->setVisible(false);
    pauseButton->setVisible(true);
    onPlaying = true;

    if(iniState)
    {
        T->play();
        iniState = false;
    }
    else
    {
        T->stopTheClock();
        T->resetGame();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
    delete graphicsView;
    graphicsView = nullptr;
    delete scene;
    scene = nullptr;
    delete T;
    T = nullptr;
    delete scoreLabel;
    scoreLabel = nullptr;
    delete nextTetroLabel;
    nextTetroLabel = nullptr;
    delete pauseButton;
    pauseButton = nullptr;
    delete resumeButton;
    resumeButton = nullptr;
    delete newGameButton;
    newGameButton = nullptr;
}
