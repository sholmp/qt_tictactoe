#include "initgamedialog.h"
#include "ui_initgamedialog.h"
#include <QDialogButtonBox>

InitGameDialog::InitGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitGameDialog)
{
    ui->setupUi(this);
//    ui->player1Label->setBuddy()
    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this](){emit sendPlayerNames("foo", "bar");});

}

InitGameDialog::~InitGameDialog()
{
    delete ui;
}

QString InitGameDialog::player1Name()
{
    return ui->editPlayer1->text();
}

QString InitGameDialog::player2Name()
{
    return ui->editPlayer2->text();
}

uint InitGameDialog::boardWidth()
{
    return qMax(1, ui->spinBox->value());
}
