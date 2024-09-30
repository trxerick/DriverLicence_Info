#ifndef EXCELWORKER_H
#define EXCELWORKER_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QAxObject>
#include <QStringList>
#include <QColor>
#include "conrecord.h"
#include "infobox.h"

class excelWorker : public QObject
{
    Q_OBJECT

    public:
        QString pathToExcel;

        excelWorker();
        excelWorker(QString dir, int startrrowC, int startrcolC, int startwrowC, int startwcolC);
        ~excelWorker();

    private:
        QAxObject* excel;
        QAxObject* workbooks;
        QAxObject* workbook;
        QAxObject* sheets;
        QAxObject* currentSheet;
        infoBox* popup;
        QList<conRecord> curCon;
        void readExcelFile();
        QString getCellData(int row, int col);
        void writeConData(int row, conRecord curRecord);
        void closeExcelFile();
        void getDataFromDB();
        int startrrow;
        int startrcol;
        int startwrow;
        int startwcol;

    public slots:
        void excelJob();
        void writeExcelFile(QList<conRecord> updatedConList);

    signals:
        void finishedReading();
        void makeProgress(int progress);
        void finishedWriting();
        void updateLog(QString msg);
        void excelReaded(QList<conRecord> curCon);

};

#endif // EXCELWORKER_H
