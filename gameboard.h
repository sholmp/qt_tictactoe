#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QPair>
#include <QGridLayout>




class Field : public QPushButton
{
    Q_OBJECT
public:
    Field(int i, int j, QWidget* parent = nullptr);

    int i_;
    int j_;

signals:
    void fieldClicked(int i, int j);

};



class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);

public slots:
    void restartGame();
    void handleButtonClick(int i, int j);

signals:
    void setTextOnFields(QString text);



private:
    QVector<Field*> fields_;
    QGridLayout* layout_;
    QVector<QVector<Field*>> grid_;

    enum class GameState
    {
        NotStarted, Begun, Ended
    };

    enum class Turn
    {
        Player1, Player2
    };


    GameState state_ = GameState::NotStarted;
    Turn turn_ = Turn::Player1;


private:
    bool winConditionSatisfied();

};

#endif // GAMEBOARD_H
