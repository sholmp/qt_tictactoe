#ifndef INITGAMEDIALOG_H
#define INITGAMEDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class InitGameDialog;
}

class InitGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitGameDialog(QWidget *parent = nullptr);
    ~InitGameDialog();

    QString player1Name();
    QString player2Name();
    uint boardWidth();
signals:
    void sendPlayerNames(QString player1_name, QString player2_name);

private:
    Ui::InitGameDialog *ui;



};

#endif // INITGAMEDIALOG_H
