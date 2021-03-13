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
        for(int j = 0; j < 3; j++)
        {
            Field* field = new Field(i,j);
            fields_.push_back(field);
            layout_->addWidget(field,i,j);
        }
    }


    for(auto field : fields_)
        connect(field, &Field::fieldClicked, this, &GameBoard::handleButtonClick);


    QPushButton* restartButton = new QPushButton("restart game");
    layout_->addWidget(restartButton);
    connect(restartButton, &QPushButton::clicked, this, &GameBoard::restartGame);

    //Make buttons resize

    for(auto field : fields_)
    {
        field->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
}

void GameBoard::restartGame()
{
    state_ = GameState::Begun;
    turn_ = Turn::Player1;

    for(auto field : fields_)
        field->setText("");
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

    bool top = EqualFieldValues({0,0}, {0,1}, {0,2});
    bool mid_hoz = EqualFieldValues({1,0}, {1,1}, {1,2}); //middle horizontal
    bool bot = EqualFieldValues({2,0}, {2,1}, {2,2}); //bottom
    bool left = EqualFieldValues({0,0}, {1,0}, {2,0}); //left
    bool mid_vert = EqualFieldValues({0,1}, {1,1}, {2,1}); //middle vertical
    bool right = EqualFieldValues({0,2}, {1,2}, {2,2}); //right

    bool diag1 = EqualFieldValues({0,0}, {1,1}, {2,2}); //right
    bool diag2 = EqualFieldValues({2,0}, {1,1}, {0,2}); //right


    if(top || mid_hoz || bot || left || mid_vert || right || diag1 || diag2)
        restartGame();
}

bool GameBoard::EqualFieldValues(std::pair<int, int> e1, std::pair<int, int> e2, std::pair<int, int> e3)
{
    QGridLayout* grid = dynamic_cast<QGridLayout*>(layout());

    Field* field1 = dynamic_cast<Field*>(grid->itemAtPosition(e1.first, e1.second)->widget());
    Field* field2 = dynamic_cast<Field*>(grid->itemAtPosition(e2.first, e2.second)->widget());
    Field* field3 = dynamic_cast<Field*>(grid->itemAtPosition(e3.first, e3.second)->widget());

    bool allEqual = field1->text() == 'X' || field1->text() == 'O'; //Don't match 3 empty fields
    allEqual &= field1->text() == field2->text();
    allEqual &= field2->text() == field3->text();
    allEqual &= field1->text() == field3->text();

    return allEqual;
}



