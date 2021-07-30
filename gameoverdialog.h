#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(int iniScore, QWidget *parent = nullptr);
    ~GameOverDialog();

    bool getIsEndGame() const;

private slots:
    void on_newGame_clicked();

private:
    Ui::GameOverDialog *ui;
    bool isEndGame;

};

#endif // GAMEOVERDIALOG_H
