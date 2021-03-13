#include "gameboard.h"

#include <QGridLayout>
#include <QPushButton>
#include <QDebug>


Field::Field(int i, int j, QWidget* parent):
    QPushButton(parent), i_(i), j_(j)
{
    connect(this, &QPushButton::clicked, [this](){emit fieldClicked(i_, j_);});
}




GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{

    layout_ = new QGridLayout;
    setLayout(layout_);

    for(int i = 0; i < 3; i++)
    {
        QVector<Field*> row;
        for(int j = 0; j < 3; j++)
        {
            Field* field = new Field(i,j);
            row.push_back(field);
            layout_->addWidget(field,i,j);

            connect(field, &Field::fieldClicked, this, &GameBoard::handleButtonClick);
            connect(this, &GameBoard::setTextOnFields, field, &Field::setText);
            field->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); //Make field resize when given more space

        }
        grid_.push_back(row);
    }


    QPushButton* restartButton = new QPushButton("restart game");
    layout_->addWidget(restartButton);
    connect(restartButton, &QPushButton::clicked, this, &GameBoard::restartGame);
}

void GameBoard::restartGame()
{
    state_ = GameState::Begun;
    turn_ = Turn::Player1;

    emit setTextOnFields(""); // Clear every field
}

void GameBoard::handleButtonClick(int i, int j)
{
    Field* field = dynamic_cast<Field*>(layout_->itemAtPosition(i,j)->widget());
    if(!field)
    {
        qDebug() << "bad dynamic cast";
        return;
    }

    if(turn_ == Turn::Player1)
        field->setText("X");
    else if(turn_ == Turn::Player2)
        field->setText("O");

    turn_ = static_cast<Turn>((static_cast<int>(turn_) + 1) % 2);

    if(winConditionSatisfied())
    {
        restartGame();
    }

}


bool GameBoard::winConditionSatisfied()
{
    // Check horizontally
    int N = grid_.size(); //Our application only works with square maps
    for(int i = 0; i < N; i++)
    {
        int matches = 1; // first symbol matches itself
        QString symbol = grid_[i][0]->text(); //Check if field holds X, O or is blank
        for(int j = 1; j < N; j++)
        {
            if(grid_[i][j]->text() == symbol)
                matches++;
        }
        if(matches == N && symbol != "")
            return true;
    }

    //Check vertically
    for(int j = 0; j < N; j++)
    {
        int matches = 1; // first symbol matches itself
        QString symbol = grid_[0][j]->text(); //Check if field holds X, O or is blank
        for(int i = 1; i < N; i++)
        {
            if(grid_[i][j]->text() == symbol)
                matches++;
        }
        if(matches == N && symbol != "")
            return true;
    }

    //Check diagonally
    //First check top left to bottom right:
    QString symbol = grid_[0][0]->text();
    int matches = 1;
    for(int i = 1; i < N; i++)
    {
        if(grid_[i][i]->text() == symbol)
            matches++;
    }
    if(matches == N && symbol != "")
        return true;

    //check bottom left to top right
    matches = 1;
    symbol = grid_[N-1][0]->text();
    for(int i = N-2, j = 1; j < N; i--, j++)
    {
        if(grid_[i][j]->text() == symbol)
            matches++;
    }
    if(matches == N && symbol != "")
        return true;

    return false;
}



