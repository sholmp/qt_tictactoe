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


        //Create and add gameboard to mainwindow
        GameBoard* board = new GameBoard(dialog.boardWidth(), this);
        ui->centralwidget->layout()->addWidget(board);
        connect(ui->beginNewGameButton, &QPushButton::clicked, board, &GameBoard::beginNewGame);
    }
    else // production mode
    {
        GameBoard* board = new GameBoard(3, this);
        ui->centralwidget->layout()->addWidget(board);
        connect(ui->beginNewGameButton, &QPushButton::clicked, board, &GameBoard::beginNewGame);

    }



}

MainWindow::~MainWindow()
{
    delete ui;

}
