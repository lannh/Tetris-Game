#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(int iniScore, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
    isEndGame = true;

    this->setWindowTitle("Game Over");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->printScore->setText(QString::number(iniScore));
    QObject::connect(ui->exitGame, SIGNAL(clicked()), this, SLOT(close()));
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
    ui = nullptr;
}

bool GameOverDialog::getIsEndGame() const
{
    return isEndGame;
}

void GameOverDialog::on_newGame_clicked()
{
    isEndGame = false;
    this->close();
}
