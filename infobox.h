#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QIcon>

class infoBox : public QMessageBox
{
    public:
        infoBox();
        infoBox(QWidget* parent, int typeOfMsg, QString title, QString msg);
        ~infoBox();
};

#endif // INFOBOX_H
