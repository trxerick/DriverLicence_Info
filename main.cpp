#include "mainwindow.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon favicon("icons/favicon.png");
    QFile styleFile("styles/style.qss");

    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    a.setStyleSheet(style);
    styleFile.close();

    QApplication::setWindowIcon(favicon);
    QScreen* screen = a.primaryScreen();

    qRegisterMetaType<QList<conRecord>>("QList<conRecord>");

    int applicationWidth = w.frameGeometry().width();
    int applicationHeight = w.frameGeometry().height();
    int screenWidth = screen->geometry().width();
    int screenHeight = screen->geometry().height();

    w.setGeometry((screenWidth - WIDTH) / 2, (screenHeight - HEIGHT) / 2,
                  applicationWidth, applicationHeight);

    w.show();
    w.setWindowTitle("ДОСААФ ИНФО");
    w.setFixedSize(WIDTH, HEIGHT);

    return a.exec();
}
