#include "infobox.h"

infoBox::infoBox(){}

infoBox::infoBox(QWidget* parent, int typeOfMsg, QString title, QString msg) : QMessageBox(parent)
{
    QIcon favicon("icons/favicon.png");
    QPixmap errorIcon("icons/errorIcon.png");
    QPixmap successIcon("icons/successIcon.png");
    QPixmap infoIcon("icons/infoIcon.png");
    QPixmap scaledIcon;

    setWindowIcon(favicon);
    setWindowTitle(title);
    setText(msg);

    setStandardButtons(QMessageBox::StandardButton::Ok);
    switch(typeOfMsg)
    {
        case 1:
            setIconPixmap(errorIcon);
            break;
        case 2:
            setIconPixmap(successIcon);
            break;
        case 3:
            setIconPixmap(infoIcon);
            break;
        default:
            setIconPixmap(infoIcon);
            break;

    }
}

infoBox::~infoBox(){}
