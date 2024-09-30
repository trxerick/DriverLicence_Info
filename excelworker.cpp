#include "excelworker.h"

excelWorker::excelWorker(){}

excelWorker::excelWorker(QString dir, int startrrowC, int startrcolC, int startwrowC, int startwcolC) : pathToExcel(dir)
{
    startrrow = startrrowC;
    startrcol = startrcolC;
    startwrow = startwrowC;
    startwcol = startwcolC;
};

void excelWorker::excelJob()
{
    excel = new QAxObject("Excel.Application", 0);
    if(excel){
        excel->dynamicCall("SetVisible(bool)", false);
        workbooks = excel->querySubObject("Workbooks");
        workbook = workbooks->querySubObject("Open(QString)", pathToExcel);

        emit updateLog("[Успех] подключен Excel-файл: " + pathToExcel);

        sheets = workbook->querySubObject("Worksheets");

        readExcelFile();
        closeExcelFile();
    } else {
        popup = new infoBox(nullptr, 1, "Ошибка", "Ошибка при открытии Excel-файла, "
                                                  "убедитесь, что MS Excel установлен на Вашем компьютере.");
        popup->setModal(true);
        popup->exec();
    }
}


void excelWorker::readExcelFile()
{
    int rowCount = 0;
    QAxObject *cols, *rows, *range;
    QString firstName, middleName, lastName;

    currentSheet = sheets->querySubObject("Item( int )", 1);
    range = currentSheet->querySubObject("UsedRange");
    rows = range->querySubObject("Rows");
    cols = range->querySubObject("Columns");
    rowCount = rows->dynamicCall("Count()").toInt();

    for(int i = startrrow; i < rowCount; i++){
        conRecord newCon;
        firstName = getCellData(i, startrcol+1);
        middleName = getCellData(i, startrcol+2);
        lastName = getCellData(i, startrcol);

        newCon.setRecordNumber(i);
        newCon.setLastName(lastName);
        newCon.setFirstName(firstName);
        newCon.setMiddleName(middleName);

        if(firstName.count(" ") < 1 && middleName.count(" ") < 1 && lastName.count(" ") < 1 &&
           firstName != "" && middleName != "" && lastName != ""){
            curCon.append(newCon);
            emit updateLog("[Инфо] Считан призывник из Excel-файла: " + newCon.getLastName() + " " + newCon.getFirstName() + " "
                           + newCon.getMiddleName());
        }
    }

    emit updateLog("[Инфо] Всего считано призывников из Excel-файла: " + QString::number(curCon.count()));

    getDataFromDB();
}

void excelWorker::writeExcelFile(QList<conRecord> updatedConList)
{
    excel = new QAxObject("Excel.Application", 0);

    if(excel){
        excel->dynamicCall("SetVisible(bool)", false);
        workbooks = excel->querySubObject("Workbooks");
        workbook = workbooks->querySubObject("Open(const QString&)", pathToExcel);
        sheets = workbook->querySubObject("Worksheets");
        currentSheet = sheets->querySubObject("Item( int )", 1);

        for(int i = 0; i < updatedConList.count(); i++){
            writeConData(updatedConList[i].getrecordNumber(), updatedConList[i]);
        }

        emit finishedWriting();
        closeExcelFile();
    } else {
        popup = new infoBox(nullptr, 1, "Ошибка", "Ошибка при открытии Excel-файла, убедитесь, что Microsoft Excel установлен на Вашем компьютере.");
        popup->setModal(true);
        popup->exec();
    }
}

void excelWorker::writeConData(int row, conRecord conData)
{
    QAxObject* cellDriverLicense = currentSheet->querySubObject("Cells(int, int)", row, startwcol);
    QAxObject* cellDepartureInfo = currentSheet->querySubObject("Cells(int, int)", row, startwcol + 1);
    QAxObject* cellDepartureDate = currentSheet->querySubObject("Cells(int, int)", row, startwcol + 2);
    QAxObject* cellArmyUnit = currentSheet->querySubObject("Cells(int, int)", row, startwcol + 3);

    if(conData.getDriverLicense() != ""){
        cellDriverLicense->setProperty("Value", conData.getDriverLicense().trimmed() != "" ? conData.getDriverLicense().split(" ")[0] + " №" + conData.getDriverLicense().split(" ")[1] : "");
        cellDepartureInfo->setProperty("Value", "Убыл " + conData.getDepartureTime() + " в команде " +
                                                     conData.getCommandNumber() + " " + conData.getKindOfMil() + " " +
                                                     conData.getSpec());
        cellDepartureDate->setProperty("Value", conData.getDepartureTime());
        cellArmyUnit->setProperty("Value", "в/ч " + conData.getArmyUnit());
    } else {
        QAxObject* range = currentSheet->querySubObject("Range(QString, QString)", "A"+QString::number(conData.getrecordNumber()), "S"+QString::number(conData.getrecordNumber()));
        QAxObject* interior = range->querySubObject("Interior");
        interior->setProperty("ColorIndex", "6");
    }

    emit makeProgress(1);

    delete cellDriverLicense;
    delete cellDepartureInfo;
    delete cellDepartureDate;
    delete cellArmyUnit;
}

QString excelWorker::getCellData(int row, int col)
{
    QAxObject* cell = currentSheet->querySubObject("Cells(int, int)", row, col);
    QVariant res = cell->property("Value");

    delete cell;
    return res.toString().trimmed();
}

void excelWorker::closeExcelFile()
{
    excel->dynamicCall("SetVisible(bool)", false);
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    delete excel;

    emit finishedReading();
}

void excelWorker::getDataFromDB()
{
    emit updateLog("[Инфо] Начинаю ждать данные из базы данных...");
    emit excelReaded(curCon);
}

excelWorker::~excelWorker()
{
    if(workbooks) delete workbooks;
    if(workbook) delete workbook;
    if(sheets) delete sheets;
    if(currentSheet) delete currentSheet;
}
