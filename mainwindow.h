#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>

#include "log.h"
#include "eca_parser.h"
#include "measure_list.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    Log *log;
    QTimer *logTimer;
    EcaParser *eca;
    MeasureList *measureList;
    QString savePath;

    int convertMeasureListToCSV(QString &s);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotAddLogMsg(QString log);
    void slotSaveCSV();

    void on_butSetTgPath_clicked();
    void on_butSetRrPath_clicked();

    void on_butParse_clicked();

    void on_leDate_textChanged(const QString &arg1);

    void on_leCn_textChanged(const QString &arg1);

    void on_leTgPath_textChanged(const QString &arg1);

    void on_leRrPath_textChanged(const QString &arg1);

    void on_butSetSavePath_clicked();

    void on_leSavePath_textChanged(const QString &arg1);

    void on_leDateFrom_textChanged(const QString &arg1);

    void on_leDateTo_textChanged(const QString &arg1);

    void on_butTestDates_clicked();


};

#endif // MAINWINDOW_H
