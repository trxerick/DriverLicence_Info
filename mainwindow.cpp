#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainGrid = new QGridLayout(this);
    menuReference = new QMenu(this);
    menuSettings = new QMenu(this);
    mainWidget = new QWidget(this);
    pathToFileL = new QLabel(this);
    pathToFileTE = new QLineEdit(this);
    openFD = new myBtn();
    yearPickerBegin = new QComboBox(this);
    yearPickerEnd = new QComboBox(this);
    leftBorderYearPickerL = new QLabel(this);
    rightBorderYearPickerL = new QLabel(this);
    progressBarExcel = new QProgressBar(this);
    progressBarDB = new QProgressBar(this);
    progressBarExcelWriting = new QProgressBar(this);
    progressReadingFromDB = new QLabel(this);
    progressWritingToExcel = new QLabel(this);
    log = new QTextEdit(this);
    submitBtn = new myBtn();
    dirIcon = new QIcon("icons/openFolder.png");
    submitIcon = new QIcon("icons/submit.png");
    config = new QSettings("config.ini", QSettings::IniFormat);
    isLastExcelFileExists = false;
    excelIsReaded = false;

    connect(openFD, SIGNAL(hoverOn()), this, SLOT(activateHover()));
    connect(openFD, SIGNAL(hoverOff()), this, SLOT(deactivateHover()));
    connect(submitBtn, SIGNAL(hoverOn()), this, SLOT(activateHover()));
    connect(submitBtn, SIGNAL(hoverOff()), this, SLOT(deactivateHover()));
    connect(submitBtn, SIGNAL(clicked()), this, SLOT(startWork()));
    connect(openFD, SIGNAL(clicked()), this, SLOT(readExcelFile()));

    buildGUI();
}

void MainWindow::buildGUI()
{
    createMenu();
    initializeApp();

    setCentralWidget(mainWidget);
    mainWidget->setLayout(mainGrid);
    openFD->setIcon(*dirIcon);
    openFD->setIconSize(QSize(30, 30));
    openFD->setFixedSize(32, 32);
    openFD->setStyleSheet("padding-top: 2px;");

    submitBtn->setCursor(Qt::PointingHandCursor);
    openFD->setCursor(Qt::PointingHandCursor);
    yearPickerBegin->setCursor(Qt::PointingHandCursor);
    yearPickerEnd->setCursor(Qt::PointingHandCursor);

    mainWidget->setStyleSheet("background-color: #FAFAFA");

    pathToFileL->setText("Укажите путь до Excel-файла:");
    pathToFileTE->setReadOnly(true);
    pathToFileTE->setFixedSize(453, 23);
    progressBarExcel->setFixedSize(488, 20);
    progressBarDB->setAlignment(Qt::AlignCenter);
    progressBarExcelWriting->setAlignment(Qt::AlignCenter);

    submitBtn->setIcon(*submitIcon);
    submitBtn->setIconSize(QSize(30, 30));
    submitBtn->setFixedSize(32, 32);
    submitBtn->setStyleSheet("padding-top: 2px;");
    progressBarExcel->setVisible(false);

    leftBorderYearPickerL->setText("Выберите год:");
    leftBorderYearPickerL->setText("Выберите начало диапазона призыва:");
    rightBorderYearPickerL->setText("Выберите конец диапазона призыва:");
    progressReadingFromDB->setText("Процесс получения данных из БД:");
    progressWritingToExcel->setText("Процесс записи в Excel-файл:");

    log->setReadOnly(true);
    log->setStyleSheet("margin-top:15px;");
    yearPickerBegin->setFixedSize(215, 22);
    yearPickerEnd->setFixedSize(215, 22);

    mainGrid->addWidget(pathToFileL, 0, 0, 1, 1, Qt::AlignTop);
    mainGrid->addWidget(pathToFileTE, 1, 0, 1, 1, Qt::AlignLeft);
    mainGrid->addWidget(openFD, 1, 1, 1, 9, Qt::AlignRight);
    mainGrid->addWidget(progressBarExcel, 2, 0, 1, 3, Qt::AlignBottom);
    mainGrid->addWidget(leftBorderYearPickerL, 2, 0, 1, 1, Qt::AlignTop);
    mainGrid->addWidget(rightBorderYearPickerL, 2, 1, 1, 1, Qt::AlignTop);
    mainGrid->addWidget(submitBtn, 3, 2, 1, 8, Qt::AlignRight);
    mainGrid->addWidget(yearPickerBegin, 3, 0, 1, 4, Qt::AlignLeft);
    mainGrid->addWidget(yearPickerEnd, 3, 1, 1, 1, Qt::AlignRight);
    mainGrid->addWidget(log, 4, 0, 1, 8, Qt::AlignTop);
    mainGrid->addWidget(progressReadingFromDB, 5, 0, 1, 1, Qt::AlignBottom);
    mainGrid->addWidget(progressBarDB, 6, 0, 1, 8, Qt::AlignBottom);
    mainGrid->addWidget(progressWritingToExcel, 7, 0, 1, 1, Qt::AlignBottom);
    mainGrid->addWidget(progressBarExcelWriting, 8, 0, 1, 8, Qt::AlignBottom);
}

void MainWindow::createMenu()
{
    menuReference = menuBar()->addMenu(tr("&Справка"));
    referenceAction = menuReference->addAction(tr("Содержание"));
    connect(referenceAction, SIGNAL(triggered()), this, SLOT(showReference()));
}

void MainWindow::initializeApp()
{
    pathToFileTE->setText(config->value("EXCEL/lastExcelPath", "").toString());
    DBDir = config->value("DB/dir").toString();
    yearsList.append(config->value("Conscriptions/cons", "").toString().split(" "));

    yearPickerBegin->addItems(yearsList);
    yearPickerEnd->addItems(yearsList);

    if(pathToFileTE->text() != ""){
        isLastExcelFileExists = true;
    }
}

bool MainWindow::checkBorders()
{
    QStringList leftBorder, rightBorder;
    qint8 leftBorderY, leftBorderN, rightBorderY, rightBorderN;

    leftBorder = yearPickerBegin->currentText().split("-");
    rightBorder = yearPickerEnd->currentText().split("-");

    leftBorderY = leftBorder[0].toInt(); leftBorderN = leftBorder[1].toInt();
    rightBorderY = rightBorder[0].toInt(); rightBorderN = rightBorder[1].toInt();

    if(leftBorderY < rightBorderY || (leftBorderY == rightBorderY &&
      (leftBorderN == rightBorderN || leftBorderN < rightBorderN)))
        return true;
    else return false;
}

void MainWindow::activateHover()
{
    QPushButton* send = qobject_cast<QPushButton*>(sender());

    if(send) send->setIconSize(QSize(send->geometry().width() + 2, send->geometry().height() + 2));
}

void MainWindow::deactivateHover()
{
    QPushButton* send = qobject_cast<QPushButton*>(sender());

    if(send) send->setIconSize(QSize(send->geometry().width() - 2, send->geometry().height() - 2));
}

void MainWindow::readExcelFile()
{
    if(!isLastExcelFileExists){
        QString excelDir = QFileDialog::getOpenFileName(this, "Укажите путь до EXCEL-файла",
                                                        QDir::homePath(), "*.xls *.xlsx");
        if(excelDir != "") {
            pathToFileTE->setText(excelDir);
            parseExcelFile(excelDir);
        }
    } else {
        QString excelDir = QFileDialog::getOpenFileName(this, "Укажите путь до EXCEL-файла",
                                                        pathToFileTE->text(), "*.xls *.xlsx");
        if(excelDir != "") {
            pathToFileTE->setText(excelDir);
            parseExcelFile(excelDir);
        }
    }

    progressBarDB->setValue(0);
    progressBarExcelWriting->setValue(0);
}

void MainWindow::saveConList(QList<conRecord> preparedData) { conList = preparedData; excelIsReaded = true;}

void MainWindow::jobHasFinished()
{
    infoWindow = new infoBox(this, SUCCESS, "Успех", "Запись в Excel-Файл успешно закончена!");
    infoWindow->exec();
}

void MainWindow::parseExcelFile(QString excelDir)
{
    excelThread = new QThread;
    worker = new excelWorker(excelDir, config->value("Excel/startrrow").toInt(), config->value("Excel/startrcol").toInt(),
                             config->value("Excel/startwrow").toInt(), config->value("Excel/startwcol").toInt());

    worker->moveToThread(excelThread);

    connect(excelThread, SIGNAL(started()), this, SLOT(activateLoading()));
    connect(excelThread, SIGNAL(started()), worker, SLOT(excelJob()));
    connect(worker, SIGNAL(finishedReading()), this, SLOT(deactivateLoading()));
    connect(worker, SIGNAL(updateLog(QString)), this, SLOT(appendLog(QString)));
    connect(worker, SIGNAL(finishedWriting()), this, SLOT(jobHasFinished()));
    connect(excelThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(excelThread, SIGNAL(finished()), excelThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(excelReaded(QList<conRecord>)), this, SLOT(saveConList(QList<conRecord>)));
    connect(this, SIGNAL(updateConList(QList<conRecord>)), worker, SLOT(writeExcelFile(QList<conRecord>)));
    connect(worker, SIGNAL(makeProgress(int)), this, SLOT(updateProgressBar(int)));

    excelThread->start();
}

void MainWindow::updateProgressBar(int progress){
    progressBarExcelWriting->setValue(progressBarExcelWriting->value() + progress);}

void MainWindow::showReference()
{
    infoWindow = new infoBox(this, INFO, "Справка", "");
    infoWindow->setModal(true);
    infoWindow->exec();
}

void MainWindow::appendLog(QString msg) {log->append(msg);}

QStringList MainWindow::getDataBasesRanges()
{
   QStringList result;
   QString startRange = yearPickerBegin->currentText();
   QString endRange = yearPickerEnd->currentText();

   int yearBegin = startRange.split("-")[0].toInt();
   int seasonBegin = startRange.split("-")[1].toInt();
   int yearEnd = endRange.split("-")[0].toInt();

   int seasonEnd = endRange.split("-")[1].toInt();

   for(int year = yearBegin; year <= yearEnd; year++){
      result.append(FORM + QString::number(year) + "-1.GDB");
      result.append(FORM + QString::number(year) + "-2.GDB");
    }

   if(seasonBegin == 2) result.removeOne(FORM + QString::number(yearBegin) + "-1.GDB");
   if(seasonEnd == 1) result.removeOne(FORM + QString::number(yearEnd) + "-2.GDB");

   return result;
}

void MainWindow::makeQueries(QString dbName)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE", "FB");
        db.setHostName(config->value("DB/hostname").toString());
        db.setUserName(config->value("DB/login").toString());
        db.setPassword(config->value("DB/password").toString());
        db.setDatabaseName(DBDir + "\\" + dbName);
        if(db.open()){
            log->append("[Успех] Успешно подключился к БД - " + dbName);
        } else {
            infoWindow = new infoBox(this, ERROR, "Ошибка", "Произошла ошибка при подключении к БД - " + dbName);
            infoWindow->exec();
            return;
        }
        log->append("[Инфо] В данный момент идет поиск по БД - " + dbName);

        QSqlQuery queryDL(db), queryDEP(db);
        queryDL.prepare("SomeQuery");

        for(int i = 0; i < conList.count(); i++){
            queryDL.bindValue(":lastName", conList[i].getLastName());
            queryDL.bindValue(":firstName", conList[i].getFirstName());
            queryDL.bindValue(":middleName", conList[i].getMiddleName());
            queryDL.setForwardOnly(true);
            queryDL.exec();
            if(queryDL.next()) {
                 QString nCom = queryDL.value(2).toString();
                 conList[i].setDriverLicense(queryDL.value(0).toString() + " " + queryDL.value(1).toString());

                 queryDEP.prepare("SomeQuery");
                 queryDEP.bindValue(":nCom", nCom);
                 queryDEP.exec();

                 if(queryDEP.next()){
                     conList[i].setDepartureTime(QDate::fromString(queryDEP.value(0).toString(), "yyyy-MM-dd").toString("dd-MM-yyyy"));
                     conList[i].setCommandNumber(queryDEP.value(1).toString());
                     conList[i].setKindOfMil(queryDEP.value(2).toString());
                     conList[i].setArmyUnit(queryDEP.value(3).toString());
                     conList[i].setSpec(queryDEP.value(4).toString());
                 }
            }
        }
        db.close();
    }
    QSqlDatabase::removeDatabase("FB");
}

void MainWindow::startWork()
{
    QStringList basesList;

    if(excelIsReaded){
        if(checkBorders()){
            basesList = getDataBasesRanges();

            progressBarDB->setValue(0);
            progressBarDB->setMaximum(basesList.size());
            progressBarExcelWriting->setValue(0);

            for(int i = 0; i < basesList.size(); i++){
                makeQueries(basesList[i]);
                progressBarDB->setValue(progressBarDB->value() + 1);
            }
            progressBarDB->setValue(progressBarDB->value() + 1);
            emit updateConList(conList);
        } else {
           infoWindow = new infoBox(this, ERROR, "Ошибка", "Ошибка при старте работы: убедитесь, что начало диапазона "
                                                            "призыва меньше или совпадает с датой конца диапазона призыва.");
           infoWindow->exec();
       }
    } else {
        infoWindow = new infoBox(this, ERROR, "Ошибка", "Ошибка при старте работы: убедитесь, что Excel-файл считан (была нажата синяя "
                                                        "кнопка считать Excel-файл).");
        infoWindow->exec();
    }
}

void MainWindow::deactivateLoading()
{
    setFixedSize(520, 460);
    progressBarExcel->setVisible(false);
    leftBorderYearPickerL->setVisible(true);
    yearPickerBegin->setVisible(true);
    yearPickerEnd->setVisible(true);
    log->setVisible(true);
    submitBtn->setVisible(true);
    rightBorderYearPickerL->setVisible(true);
    progressReadingFromDB->setVisible(true);
    progressBarDB->setVisible(true);
    progressWritingToExcel->setVisible(true);
    progressBarExcelWriting->setVisible(true);
}

void MainWindow::activateLoading()
{
    setFixedSize(520, 150);
    progressBarExcel->setVisible(true);
    progressBarExcel->setMaximum(0);
    progressBarExcel->setMinimum(0);
    leftBorderYearPickerL->setVisible(false);
    yearPickerBegin->setVisible(false);
    rightBorderYearPickerL->setVisible(false);
    yearPickerEnd->setVisible(false);
    log->setVisible(false);
    submitBtn->setVisible(false);
    progressReadingFromDB->setVisible(false);
    progressBarDB->setVisible(false);
    progressWritingToExcel->setVisible(false);
    progressBarExcelWriting->setVisible(false);
}

MainWindow::~MainWindow()
{
    config->setValue("EXCEL/lastExcelPath", pathToFileTE->text());
    delete menuReference;
    delete menuSettings;
    delete mainGrid;
    delete pathToFileL;
    delete pathToFileTE;
    delete openFD;
    delete yearPickerBegin;
    delete yearPickerEnd;
    delete leftBorderYearPickerL;
    delete rightBorderYearPickerL;
    delete dirIcon;
    delete submitBtn;
    delete progressBarExcel;
    delete config;
}

