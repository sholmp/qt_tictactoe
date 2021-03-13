#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startGameButton, &QPushButton::clicked, [this](){ui->player1Label->setText("Jakob");});
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::receivePlayerNames(QString player1, QString player2)
{
 ui->player1Label->setText(player1);
 ui->player2Label->setText(player2);
}
