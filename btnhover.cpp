#include "btnhover.h"

myBtn::myBtn()
{
    isHovered = false;
    setAttribute(Qt::WA_Hover);

    connect(this, SIGNAL(clicked()), this, SLOT(clickedWithParams()));
}

void myBtn::enterEvent(QEvent *e)
{
     if(!isHovered){
          isHovered = true;
          emit hoverOn();
    }
    QPushButton::enterEvent(e);
}

void myBtn::leaveEvent(QEvent *e)
{
    if(isHovered){
        isHovered = false;
        emit hoverOff();
    }
    QPushButton::leaveEvent(e);
}

void myBtn::clickedWithParams() { emit sendYearAndSeason(); }

myBtn::~myBtn()
{

}
