#include "initgamedialog.h"
#include "ui_initgamedialog.h"
#include <QDialogButtonBox>

InitGameDialog::InitGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitGameDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this](){emit sendPlayerNames("foo", "bar");});

}

InitGameDialog::~InitGameDialog()
{
    delete ui;
}
