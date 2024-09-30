#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WIDTH 520
#define HEIGHT 460
#define ERROR 1
#define SUCCESS 2
#define INFO 3
#define FORM "FORM"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QTextBlock>
#include <QIcon>
#include <QFileDialog>
#include <QLineEdit>
#include <QAxObject>
#include <QProgressBar>
#include <QThread>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QScreen>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QCursor>
#include <QSettings>
#include "infobox.h"
#include "btnhover.h"
#include "excelworker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        QSettings* config;
        QWidget* mainWidget;
        QGridLayout* mainGrid;
        QLabel* pathToFileL;
        QLabel* leftBorderYearPickerL;
        QLabel* rightBorderYearPickerL;
        QLabel* progressReadingFromDB;
        QLabel* progressWritingToExcel;
        QPushButton* okayBtn;
        QComboBox* yearPickerBegin;
        QComboBox* yearPickerEnd;
        QLineEdit* pathToFileTE;
        QStringList yearsList;
        QString DBDir;
        QPushButton* submitBtn;
        QTextEdit* log;
        QProgressBar* progressBarExcel;
        QProgressBar* progressBarDB;
        QProgressBar* progressBarExcelWriting;
        QIcon* dirIcon;
        QIcon* submitIcon;
        QMenu* menuSettings;
        QMenu* menuReference;
        QAction* DBEditAction;
        QAction* yearsEditAction;
        QAction* yearsDeleteAction;
        QAction* referenceAction;
        excelWorker* worker;
        myBtn* openFD;
        infoBox* infoWindow;
        QList<conRecord> conList;
        bool isLastExcelFileExists;
        bool excelIsReaded;

        MainWindow(QWidget *parent = nullptr);

        void buildGUI();
        void createMenu();
        void initializeApp();
        void parseExcelFile(QString excelDir);
        bool checkBorders();
        bool isConDuplicated(QString con);
        QStringList getDataBasesRanges();
        void makeQueries(QString dbName);
        ~MainWindow();

    public slots:
        void activateHover();
        void deactivateHover();
        void readExcelFile();
        void deactivateLoading();
        void activateLoading();
        void appendLog(QString msg);
        void startWork();
        void showReference();
        void saveConList(QList<conRecord> preparedData);
        void jobHasFinished();
        void updateProgressBar(int porgress);

    signals:
        void updateConList(QList<conRecord> updatedList);

    private:
        QThread* excelThread;
};

#endif // MAINWINDOW_H
