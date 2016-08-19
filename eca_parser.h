#ifndef ECA_PARSER_H
#define ECA_PARSER_H

#include <QDebug>
#include <QThread>
#include <QString>
#include <QDir>

#include "log.h"
#include "measure_list.h"

#define DATE_FORMAT             "yyyyMMdd"
#define SPLIT_SIGN              ","
#define SOURCES                 "sources.txt"
#define STATIONS                "stations.txt"
#define STATIONS_OFFSET         19              /// data-line-offset
#define TG_FILE                 "TG_STAID"
#define RR_FILE                 "RR_STAID"
#define TG_OFFSET               21              /// data-line-offset
#define RR_OFFSET               21              /// data-line-offset
#define MISSING_Q               "9"
#define MISSING_VAL             "-9999"
#define STAID_LENGTH            6

class EcaParser : public QThread
{
    Q_OBJECT
private:
    enum STA {
        STA_STAID,
        STA_STANAME,
        STA_CN,
        STA_LAT,
        STA_LON,
        STA_HIGH,
        STA_NUMBER
    };

    enum TG {
        TG_STAID,
        TG_SOUID,
        TG_DATE,
        TG_TG,
        TG_Q_TG,
        TG_NUMBER
    };

    enum RR {
        RR_STAID,
        RR_SOUID,
        RR_DATE,
        RR_RR,
        RR_Q_RR,
        RR_NUMBER
    };

    QString tgPath;
    QString rrPath;
    QString dateMeasure;
    QString cn;
    QString dateFrom;
    QString dateTo;

    MeasureList *measureList;

    void run();
    void processParse();
    void processTestDates();
    int getDateString(const QDate &d, QString &s);
    int initStations(MeasureList *measureList, const QStringList &tgFileList);
    int parseTg(MeasureList *measureList, const QStringList &tgFileList, const QString &date);

    QString getStationColumnName(STA e);
    int getLatLonFromString(QString s, double &d);

public:

    enum ECA_PROCESS {
        ECA_P_PARSE,
        ECA_P_TEST_DATES,
        ECA_P_NUMBER
    };

    EcaParser();

    int setFilePaths(QStringList list);
    int process(MeasureList *measureList, ECA_PROCESS p);

    QString getTgPath() const;
    void setTgPath(const QString &value);

    QString getRrPath() const;
    void setRrPath(const QString &value);

    QString getDateMeasure() const;
    void setDateMeasure(const QString &value);

    QString getCn() const;
    void setCn(const QString &value);

    QString getDateFrom() const;
    void setDateFrom(const QString &value);

    QString getDateTo() const;
    void setDateTo(const QString &value);

private:
    ECA_PROCESS proc;

public slots:
    int slotClearStations();

signals:
    void signalStationNumber(QString);
};

#endif // ECA_PARSER_H
