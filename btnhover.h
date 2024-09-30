#ifndef BTNHOVER_H
#define BTNHOVER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QDebug>

class myBtn : public QPushButton
{
    Q_OBJECT
    public:
        myBtn();
        ~myBtn();

    protected:
        virtual void enterEvent(QEvent* e);
        virtual void leaveEvent(QEvent* e);

    private:
        bool isHovered;

    signals:
        void hoverOn();
        void hoverOff();
        void sendYearAndSeason();

    public slots:
        void clickedWithParams();
};

#endif // BTNHOVER_H
