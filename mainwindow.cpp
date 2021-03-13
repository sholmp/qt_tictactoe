#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "initgamedialog.h"
#include "gameboard.h"

#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool use_dialog = false; //production mode command to avoid having to use the dialog every time app is started
    if(use_dialog)
    {
        InitGameDialog dialog(this);
        if(dialog.exec() == QDialog::Rejected)
            return; //Rejected happens if user presses cancel

        ui->player1Label->setText(dialog.player1Name());
        ui->player2Label->setText(dialog.player2Name());
        ui->gameBoard->init(dialog.boardWidth());

        connect(ui->beginNewGameButton, &QPushButton::clicked, ui->gameBoard, &GameBoard::beginNewGame);
        connect(ui->gameBoard, &GameBoard::gameOver, this, &MainWindow::handleGameOver);
    }
    else // production mode
    {
        connect(ui->beginNewGameButton, &QPushButton::clicked, ui->gameBoard, &GameBoard::beginNewGame);
        connect(ui->gameBoard, &GameBoard::gameOver, this, &MainWindow::handleGameOver);
        ui->gameBoard->init(3);
    }

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::handleGameOver(int winner)
{
    if(winner == 1)
    {
        int current_score = ui->player1Score->text().toInt();
        ui->player1Score->setText(QString::number(current_score + 1));
    }
    else
    {
        int current_score = ui->player2Score->text().toInt();
        ui->player2Score->setText(QString::number(current_score + 1));
    }
}
