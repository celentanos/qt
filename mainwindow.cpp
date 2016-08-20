#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    measureList = new MeasureList();
    eca = new EcaParser();

    connect(eca, &EcaParser::signalStationNumber, ui->leStations, &QLineEdit::setText);
//    connect(ui->butClearMeasureList, &QPushButton::clicked, eca, &EcaParser::slotClearStations);

    ui->leSavePath->setText(QDir::currentPath() + "/");
    connect(ui->butSaveCSV, &QPushButton::clicked, this, &MainWindow::slotSaveCSV);

    ui->leDateFrom->setText("20150301");
    ui->leDateTo->setText("20150401");

    ui->leTgPath->setText("/media/90GiB/ECA_blend_tg/");
    ui->leRrPath->setText("/media/90GiB/ECA_blend_rr/");
    ui->leDate->setToolTip("Dateformat: YearMonthDay => 20081231");
    ui->leDate->setText("20160731");
    ui->leCn->setToolTip("Country-format: CN => DE");
    ui->leCn->setText("DE");

    log = Log::getInstance();
    connect(log, &Log::signalAddLog, this, &MainWindow::slotAddLogMsg);

    logTimer = new QTimer();
    logTimer->setSingleShot(true);
    connect(logTimer, &QTimer::timeout, ui->statusBar, &QStatusBar::clearMessage);
}

MainWindow::~MainWindow()
{
    if(log != 0)
        delete log;
    if(eca != 0)
        delete eca;
    delete ui;
}

void MainWindow::on_butSetTgPath_clicked()
{
    setPath(eca->getTgPathRef(), *ui->leTgPath);
}

void MainWindow::on_butSetRrPath_clicked()
{
    setPath(eca->getRrPathRef(), *ui->leRrPath);
}

void MainWindow::slotAddLogMsg(QString log)
{
    ui->statusBar->showMessage(log);
    ui->tbLog->append(log);
    logTimer->start(4000);
    //    QTimer::singleShot(4000, this, &MainWindow::slotClearStatusBar);
}

void MainWindow::on_butParse_clicked()
{
    eca->process(measureList, EcaParser::ECA_P_PARSE);
}

void MainWindow::on_leDate_textChanged(const QString &arg1)
{
    //TODO: auf Datumformat prüfen...
    eca->setDateMeasure(arg1);
}

void MainWindow::on_leCn_textChanged(const QString &arg1)
{
    //TODO: auf Datumformat prüfen...
    eca->setCn(arg1);
}

void MainWindow::on_leTgPath_textChanged(const QString &arg1)
{
    //TODO: auf Datumformat prüfen...
    eca->setTgPath(arg1);
}

void MainWindow::on_leRrPath_textChanged(const QString &arg1)
{
    //TODO: auf Datumformat prüfen...
    eca->setRrPath(arg1);
}

void MainWindow::on_butSetSavePath_clicked()
{
    setPath(savePath, *ui->leSavePath);
}

void MainWindow::on_butSetTestResultPath_clicked()
{
    setPath(eca->getTestResultPathRef(), *ui->leTestResultPath);
}

void MainWindow::on_leSavePath_textChanged(const QString &arg1)
{
    if(arg1.at(arg1.size() - 1) != '/') {
        savePath = arg1 + "/";
        return;
    }
    savePath = arg1;
}

void MainWindow::slotSaveCSV()
{
    if(savePath == "") {
        Log::getInstance()->log(Log::FAILURE, "MainWindow: slotSaveCSV: savePath is empty!");
        return;
    }

    QString s;
    if(convertMeasureListToCSV(s))
        return;

    bool time = true;
    QString fileName1 = "measure";
    QString fileName2 = measureList->getCn() + "_" + measureList->getDate().toString("yyyyMMdd");
    QString sEnding = ".csv";
    QString saveFile;
    if(time) {
        QDateTime date = QDateTime::currentDateTime();
        saveFile = savePath + fileName1 + "_" + date.toString("yyyyMMdd_HHmmss") + "_" + fileName2 + sEnding;
    } else
        saveFile = savePath + fileName1 + "_" + fileName2 + sEnding;

    QFile file(saveFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        Log::getInstance()->log(Log::ERROR, "MainWindow: slotSaveCSV: can't open file!");
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << s;
    Log::getInstance()->log(Log::INFO, ".csv saved...");
}

int MainWindow::convertMeasureListToCSV(QString &s)
{
    if(measureList->size() == 0) {
        Log::getInstance()->log(Log::ERROR, "MainWindow: convertMeasureListToCSV: measureList is empty!");
        return -1;
    }
    if(measureList->getCn() == "") {
        Log::getInstance()->log(Log::ERROR, "MainWindow: convertMeasureListToCSV: cn is empty!");
        return -1;
    }
    if(measureList->getDate().isNull()) {
        Log::getInstance()->log(Log::ERROR, "MainWindow: convertMeasureListToCSV: date is empty!");
        return -1;
    }

    s += "CN " + measureList->getCn() + "\n";
    s += "DATE " + measureList->getDate().toString("yyyyMMdd") + "\n";
    s += "\n\n\n\n\n\n\n";

    s += "STAID SOUIDTG SOUIDRR STANAME TG TGQ RR RRQ HIGH\n";
    for (int i = 0; i < measureList->size(); ++i) {
        s += measureList->at(i)->getStaId() + " " +
             measureList->at(i)->getSouIdTg() + " " +
             measureList->at(i)->getSouIdRr() + " " +
             measureList->at(i)->getStaName() + " " +
             QString::number(measureList->at(i)->getTg()) + " " +
             QString::number(measureList->at(i)->getTgq()) + " " +
             QString::number(measureList->at(i)->getRr()) + " " +
             QString::number(measureList->at(i)->getRrq()) + " " +
//             QString::number(measureList->at(i)->getLat()) + " " +
//             QString::number(measureList->at(i)->getLon()) + " " +
             QString::number(measureList->at(i)->getHigh()) + " " + "\n";
    }
    return 0;
}

void MainWindow::setPath(QString &path, QLineEdit &le)
{
    QString s = QFileDialog::getExistingDirectory(this, "Directory", "./", QFileDialog::ShowDirsOnly);
    if(s.at(s.size() - 1) != '/') {
        s += '/';
        path = s;
        le.setText(s);
        return;
    }
    path = s;
    le.setText(s);
}

void MainWindow::on_leDateFrom_textChanged(const QString &arg1)
{
    eca->setDateFrom(arg1);
}

void MainWindow::on_leDateTo_textChanged(const QString &arg1)
{
    eca->setDateTo(arg1);
}

void MainWindow::on_butTestDates_clicked()
{
    eca->process(measureList, EcaParser::ECA_P_TEST_DATES);
}


